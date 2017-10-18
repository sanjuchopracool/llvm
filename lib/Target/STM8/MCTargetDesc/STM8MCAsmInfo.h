//===-- STM8MCAsmInfo.h - STM8 asm properties --------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the STM8MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_STM8_MCTARGETDESC_STM8MCASMINFO_H
#define LLVM_LIB_TARGET_STM8_MCTARGETDESC_STM8MCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class Triple;

class STM8MCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit STM8MCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif
