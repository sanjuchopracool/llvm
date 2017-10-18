//===-- STM8TargetMachine.cpp - Define TargetMachine for STM8 ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Top-level implementation for the STM8 target.
//
//===----------------------------------------------------------------------===//

#include "STM8TargetMachine.h"
#include "STM8.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeSTM8Target() {
  // Register the target.
  RegisterTargetMachine<STM8TargetMachine> X(getTheSTM8Target());
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

static CodeModel::Model getEffectiveCodeModel(Optional<CodeModel::Model> CM) {
  if (CM)
    return *CM;
  return CodeModel::Small;
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  return "e-m:e-p:16:16-i32:16-i64:16-f32:16-f64:16-a:8-n8:16-S16";
}

STM8TargetMachine::STM8TargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM), OL),
      TLOF(make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

STM8TargetMachine::~STM8TargetMachine() {}

namespace {
/// STM8 Code Generator Pass Configuration Options.
class STM8PassConfig : public TargetPassConfig {
public:
  STM8PassConfig(STM8TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  STM8TargetMachine &getSTM8TargetMachine() const {
    return getTM<STM8TargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *STM8TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new STM8PassConfig(*this, PM);
}

bool STM8PassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createSTM8ISelDag(getSTM8TargetMachine(), getOptLevel()));
  return false;
}

void STM8PassConfig::addPreEmitPass() {
  // Must run branch selection immediately preceding the asm printer.
  addPass(createSTM8BranchSelectionPass(), false);
}
