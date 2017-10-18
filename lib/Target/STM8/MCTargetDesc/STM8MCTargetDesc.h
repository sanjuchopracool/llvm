//===-- STM8MCTargetDesc.h - STM8 Target Descriptions -------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_STM8_MCTARGETDESC_STM8MCTARGETDESC_H
#define LLVM_LIB_TARGET_STM8_MCTARGETDESC_STM8MCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;

Target &getTheSTM8Target();

} // End llvm namespace

// Defines symbolic names for STM8 registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "STM8GenRegisterInfo.inc"

// Defines symbolic names for the STM8 instructions.
#define GET_INSTRINFO_ENUM
#include "STM8GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "STM8GenSubtargetInfo.inc"

#endif
