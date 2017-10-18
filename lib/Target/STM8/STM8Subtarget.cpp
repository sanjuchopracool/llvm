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

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "STM8GenSubtargetInfo.inc"

void STM8Subtarget::anchor() { }

STM8Subtarget::STM8Subtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : STM8GenSubtargetInfo(TT, CPU, FS), FrameLowering(),
      InstrInfo(), TLInfo(TM, *this) {}
