//===-- STM8TargetInfo.cpp - STM8 Target Implementation ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "STM8.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheSTM8Target() {
  static Target TheSTM8Target;
  return TheSTM8Target;
}

extern "C" void LLVMInitializeSTM8TargetInfo() {
  RegisterTarget<Triple::stm8> X(getTheSTM8Target(), "stm8",
                                   "STM8 [experimental]");
}
