//==-- STM8.h - Top-level interface for STM8 representation --*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM STM8 backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_STM8_STM8_H
#define LLVM_LIB_TARGET_STM8_STM8_H

#include "MCTargetDesc/STM8MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace STM8CC {
  // STM8 specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,

    COND_INVALID = -1
  };
}

namespace llvm {
  class STM8TargetMachine;
  class FunctionPass;
  class formatted_raw_ostream;

  FunctionPass *createSTM8ISelDag(STM8TargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createSTM8BranchSelectionPass();

} // end namespace llvm;

#endif
