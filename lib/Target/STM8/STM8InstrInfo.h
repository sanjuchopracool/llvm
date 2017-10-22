//===-- STM8InstrInfo.h - STM8 Instruction Information ------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_STM8_STM8INSTRINFO_H
#define LLVM_LIB_TARGET_STM8_STM8INSTRINFO_H

#include "STM8RegisterInfo.h"
#include "llvm/Target/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "STM8GenInstrInfo.inc"

namespace llvm {

class STM8Subtarget;

class STM8InstrInfo : public STM8GenInstrInfo {
  const STM8RegisterInfo RI;
  virtual void anchor();
public:
  explicit STM8InstrInfo();

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  const TargetRegisterInfo &getRegisterInfo() const { return RI; }
};

}

#endif
