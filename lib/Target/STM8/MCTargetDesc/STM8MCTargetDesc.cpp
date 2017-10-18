//===-- STM8MCTargetDesc.cpp - STM8 Target Descriptions ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides STM8 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "STM8MCTargetDesc.h"
#include "InstPrinter/STM8InstPrinter.h"
#include "STM8MCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "STM8GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "STM8GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "STM8GenRegisterInfo.inc"

static MCInstrInfo *createSTM8MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitSTM8MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createSTM8MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSTM8MCRegisterInfo(X, STM8::PC);
  return X;
}

static MCSubtargetInfo *
createSTM8MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createSTM8MCSubtargetInfoImpl(TT, CPU, FS);
}

static MCInstPrinter *createSTM8MCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new STM8InstPrinter(MAI, MII, MRI);
  return nullptr;
}

extern "C" void LLVMInitializeSTM8TargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<STM8MCAsmInfo> X(getTheSTM8Target());

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(getTheSTM8Target(),
                                      createSTM8MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(getTheSTM8Target(),
                                    createSTM8MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(getTheSTM8Target(),
                                          createSTM8MCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(getTheSTM8Target(),
                                        createSTM8MCInstPrinter);
}
