//===-- STM8Subtarget.cpp - STM8 Subtarget Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the STM8 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "STM8Subtarget.h"
#include "STM8.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "stm8-subtarget"

static cl::opt<STM8Subtarget::HWMultEnum>
HWMultModeOption("mhwmult", cl::Hidden,
           cl::desc("Hardware multiplier use mode for STM8"),
           cl::init(STM8Subtarget::NoHWMult),
           cl::values(
             clEnumValN(STM8Subtarget::NoHWMult, "none",
                "Do not use hardware multiplier"),
             clEnumValN(STM8Subtarget::HWMult16, "16bit",
                "Use 16-bit hardware multiplier"),
             clEnumValN(STM8Subtarget::HWMult32, "32bit",
                "Use 32-bit hardware multiplier"),
             clEnumValN(STM8Subtarget::HWMultF5, "f5series",
                "Use F5 series hardware multiplier")));

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "STM8GenSubtargetInfo.inc"

void STM8Subtarget::anchor() { }

STM8Subtarget &
STM8Subtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS) {
  ExtendedInsts = false;
  HWMultMode = NoHWMult;

  std::string CPUName = CPU;
  if (CPUName.empty())
    CPUName = "stm8";

  ParseSubtargetFeatures(CPUName, FS);

  if (HWMultModeOption != NoHWMult)
    HWMultMode = HWMultModeOption;

  return *this;
}

STM8Subtarget::STM8Subtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : STM8GenSubtargetInfo(TT, CPU, FS), FrameLowering(),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this) {}
