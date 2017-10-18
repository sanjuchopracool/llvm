//===-- STM8MCAsmInfo.cpp - STM8 asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the STM8MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "STM8MCAsmInfo.h"
using namespace llvm;

void STM8MCAsmInfo::anchor() { }

STM8MCAsmInfo::STM8MCAsmInfo(const Triple &TT) {
  CodePointerSize = CalleeSaveStackSlotSize = 2;

  CommentString = ";";

  AlignmentIsInBytes = false;
  UsesELFSectionDirectiveForBSS = true;
}
