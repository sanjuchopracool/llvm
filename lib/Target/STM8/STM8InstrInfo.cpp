//===-- STM8InstrInfo.cpp - STM8 Instruction Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the STM8 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "STM8InstrInfo.h"
#include "STM8.h"
#include "STM8TargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "STM8GenInstrInfo.inc"

// Pin the vtable to this file.
void STM8InstrInfo::anchor() {}

STM8InstrInfo::STM8InstrInfo()
  : STM8GenInstrInfo(),
    RI() {}
