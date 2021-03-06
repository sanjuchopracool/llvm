//= STM8InstPrinter.h - Convert STM8 MCInst to assembly syntax -*- C++ -*-//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints a STM8 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_STM8_INSTPRINTER_STM8INSTPRINTER_H
#define LLVM_LIB_TARGET_STM8_INSTPRINTER_STM8INSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"

namespace llvm {
  class STM8InstPrinter : public MCInstPrinter {
  public:
    STM8InstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                      const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

    void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot,
                   const MCSubtargetInfo &STI) override;

    // Autogenerated by tblgen.
    void printInstruction(const MCInst *MI, raw_ostream &O);
    static const char *getRegisterName(unsigned RegNo);

    void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O,
                      const char *Modifier = nullptr);

  };
}

#endif
