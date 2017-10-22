//===- STM8InstrInfo.td - STM8 Instruction defs ---------------*- tblgen-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the STM8 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

class STM8Inst<dag outs, dag ins, string asmstr, list<dag> pattern> : Instruction {
  let Namespace = "STM8";

  dag OutOperandList = outs;
  dag InOperandList = ins;

  let AsmString = asmstr;
  let Pattern = pattern;
}

//===----------------------------------------------------------------------===//
// STM8 Specific Node Definitions.
//===----------------------------------------------------------------------===//

def STM8retflag : SDNode<"STM8ISD::RET_FLAG", SDTNone,
                         [SDNPHasChain, SDNPOptInGlue]>;

//===----------------------------------------------------------------------===//
// STM8 Operand Definitions.
//===----------------------------------------------------------------------===//

def shortmem : Operand<i8> {
  let PrintMethod = "printShortmemOperand";
  let MIOperandInfo = (ops GR8, i8imm);
}

def longmem : Operand<i16> {
  let PrintMethod = "printLongmemOperand";
  let MIOperandInfo = (ops GR16, i16imm);
}

//===----------------------------------------------------------------------===//
// STM8 Instructions.
//===----------------------------------------------------------------------===//

let isAsCheapAsAMove = 1 in {
def LDWri : STM8Inst<(outs GR16:$dst), (ins i16imm:$src),
                     "ldw\t$dst, #$src",
                     [(set GR16:$dst, imm:$src)]>;
}

let isReturn = 1 in {
def RET : STM8Inst<(outs), (ins),
                   "ret", [(STM8retflag)]>;
}
