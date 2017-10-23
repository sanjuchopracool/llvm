//===-- STM8AsmPrinter.cpp - STM8 LLVM assembly writer ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the STM8 assembly language.
//
//===----------------------------------------------------------------------===//

#include "InstPrinter/STM8InstPrinter.h"
#include "STM8.h"
#include "STM8InstrInfo.h"
#include "STM8MCInstLower.h"
#include "STM8TargetMachine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {
  class STM8AsmPrinter : public AsmPrinter {
  public:
    STM8AsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
        : AsmPrinter(TM, std::move(Streamer)) {}

    StringRef getPassName() const override { return "STM8 Assembly Printer"; }
    void EmitInstruction(const MachineInstr *MI) override;
  };
} // end of anonymous namespace

//===----------------------------------------------------------------------===//
void STM8AsmPrinter::EmitInstruction(const MachineInstr *MI) {
  STM8MCInstLower MCInstLowering(OutContext, *this);

  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

// Force static initialization.
extern "C" void LLVMInitializeSTM8AsmPrinter() {
  RegisterAsmPrinter<STM8AsmPrinter> X(getTheSTM8Target());
}
