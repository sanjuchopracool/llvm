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
#include "STM8MachineFunctionInfo.h"
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
  const STM8FrameLowering *TFI = getFrameLowering(*MF);
  const Function* F = MF->getFunction();
  static const MCPhysReg CalleeSavedRegs[] = {
    STM8::FP, STM8::R5, STM8::R6, STM8::R7,
    STM8::R8, STM8::R9, STM8::R10,
    0
  };
  static const MCPhysReg CalleeSavedRegsFP[] = {
    STM8::R5, STM8::R6, STM8::R7,
    STM8::R8, STM8::R9, STM8::R10,
    0
  };
  static const MCPhysReg CalleeSavedRegsIntr[] = {
    STM8::FP,  STM8::R5,  STM8::R6,  STM8::R7,
    STM8::R8,  STM8::R9,  STM8::R10, STM8::R11,
    STM8::R12, STM8::R13, STM8::R14, STM8::R15,
    0
  };
  static const MCPhysReg CalleeSavedRegsIntrFP[] = {
    STM8::R5,  STM8::R6,  STM8::R7,
    STM8::R8,  STM8::R9,  STM8::R10, STM8::R11,
    STM8::R12, STM8::R13, STM8::R14, STM8::R15,
    0
  };

  if (TFI->hasFP(*MF))
    return (F->getCallingConv() == CallingConv::STM8_INTR ?
            CalleeSavedRegsIntrFP : CalleeSavedRegsFP);
  else
    return (F->getCallingConv() == CallingConv::STM8_INTR ?
            CalleeSavedRegsIntr : CalleeSavedRegs);

}

BitVector STM8RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  const STM8FrameLowering *TFI = getFrameLowering(MF);

  // Mark 4 special registers with subregisters as reserved.
  Reserved.set(STM8::PCB);
  Reserved.set(STM8::SPB);
  Reserved.set(STM8::SRB);
  Reserved.set(STM8::CGB);
  Reserved.set(STM8::PC);
  Reserved.set(STM8::SP);
  Reserved.set(STM8::SR);
  Reserved.set(STM8::CG);

  // Mark frame pointer as reserved if needed.
  if (TFI->hasFP(MF)) {
    Reserved.set(STM8::FPB);
    Reserved.set(STM8::FP);
  }

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
  assert(SPAdj == 0 && "Unexpected");

  MachineInstr &MI = *II;
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MBB.getParent();
  const STM8FrameLowering *TFI = getFrameLowering(MF);
  DebugLoc dl = MI.getDebugLoc();
  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();

  unsigned BasePtr = (TFI->hasFP(MF) ? STM8::FP : STM8::SP);
  int Offset = MF.getFrameInfo().getObjectOffset(FrameIndex);

  // Skip the saved PC
  Offset += 2;

  if (!TFI->hasFP(MF))
    Offset += MF.getFrameInfo().getStackSize();
  else
    Offset += 2; // Skip the saved FP

  // Fold imm into offset
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (MI.getOpcode() == STM8::ADDframe) {
    // This is actually "load effective address" of the stack slot
    // instruction. We have only two-address instructions, thus we need to
    // expand it into mov + add
    const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();

    MI.setDesc(TII.get(STM8::MOV16rr));
    MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);

    if (Offset == 0)
      return;

    // We need to materialize the offset via add instruction.
    unsigned DstReg = MI.getOperand(0).getReg();
    if (Offset < 0)
      BuildMI(MBB, std::next(II), dl, TII.get(STM8::SUB16ri), DstReg)
        .addReg(DstReg).addImm(-Offset);
    else
      BuildMI(MBB, std::next(II), dl, TII.get(STM8::ADD16ri), DstReg)
        .addReg(DstReg).addImm(Offset);

    return;
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(BasePtr, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
}

unsigned STM8RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const STM8FrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? STM8::FP : STM8::SP;
}
