//===-- STM8RegisterInfo.cpp - STM8 Register Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the STM8 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "STM8RegisterInfo.h"
#include "STM8.h"
#include "STM8TargetMachine.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "stm8-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "STM8GenRegisterInfo.inc"

// FIXME: Provide proper call frame setup / destroy opcodes.
STM8RegisterInfo::STM8RegisterInfo()
  : STM8GenRegisterInfo(STM8::PC) {}

const MCPhysReg*
STM8RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {

  static const MCPhysReg CalleeSavedRegs[] = {
    0
  };
    return CalleeSavedRegs;

}

BitVector STM8RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(STM8::PCL);
  Reserved.set(STM8::PCH);
  Reserved.set(STM8::PCE);
  Reserved.set(STM8::PC);
  Reserved.set(STM8::SP);
  Reserved.set(STM8::CC);

  return Reserved;
}

const TargetRegisterClass *
STM8RegisterInfo::getPointerRegClass(const MachineFunction &MF, unsigned Kind)
                                                                         const {
  return &STM8::GR16RegClass;
}

void
STM8RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                        int SPAdj, unsigned FIOperandNum,
                                        RegScavenger *RS) const {
}

unsigned STM8RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return STM8::SP;
}
