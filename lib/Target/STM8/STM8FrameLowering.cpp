//===-- STM8FrameLowering.cpp - STM8 Frame Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the STM8 implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "STM8FrameLowering.h"
#include "STM8InstrInfo.h"
#include "STM8MachineFunctionInfo.h"
#include "STM8Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

bool STM8FrameLowering::hasFP(const MachineFunction &MF) const {
  return false;
}

bool STM8FrameLowering::hasReservedCallFrame(const MachineFunction &MF) const {
  return false;
}

void STM8FrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {
}

void STM8FrameLowering::emitEpilogue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {
}

// FIXME: Can we eleminate these in favour of generic code?
bool
STM8FrameLowering::spillCalleeSavedRegisters(MachineBasicBlock &MBB,
                                           MachineBasicBlock::iterator MI,
                                        const std::vector<CalleeSavedInfo> &CSI,
                                        const TargetRegisterInfo *TRI) const {
    return false;
}

bool
STM8FrameLowering::restoreCalleeSavedRegisters(MachineBasicBlock &MBB,
                                                 MachineBasicBlock::iterator MI,
                                        std::vector<CalleeSavedInfo> &CSI,
                                        const TargetRegisterInfo *TRI) const {
    return true;
}

MachineBasicBlock::iterator STM8FrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &MF, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator I) const {
}

void
STM8FrameLowering::processFunctionBeforeFrameFinalized(MachineFunction &MF,
                                                         RegScavenger *) const {
}
