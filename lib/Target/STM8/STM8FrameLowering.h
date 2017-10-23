//==- STM8FrameLowering.h - Define frame lowering for STM8 --*- C++ -*--==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_STM8_STM8FRAMELOWERING_H
#define LLVM_LIB_TARGET_STM8_STM8FRAMELOWERING_H

#include "STM8.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
class STM8FrameLowering : public TargetFrameLowering {
protected:

public:
  explicit STM8FrameLowering()
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 1, -2, 2) {}

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;


  bool hasFP(const MachineFunction &MF) const override;
};

} // End llvm namespace

#endif
