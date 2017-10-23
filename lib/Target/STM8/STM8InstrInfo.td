//===-- STM8InstrInfo.td - STM8 Instruction defs -------*- tablegen -*-===//
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

include "STM8InstrFormats.td"

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
def STM8retflag  : SDNode<"STM8ISD::RET_FLAG", SDTNone,
                       [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
//  Control Flow Instructions...
//

// FIXME: Provide proper encoding!
let isReturn = 1, isTerminator = 1, isBarrier = 1 in {
  def RET  : STM8Inst<
                     (outs), (ins), "ret",  [(STM8retflag)]>;
}

//===----------------------------------------------------------------------===//
// Move Instructions

// FIXME: Provide proper encoding!
let isAsCheapAsAMove = 1 in {
def LDWri : STM8Inst<
                    (outs GR16:$dst), (ins i16imm:$src),
                    "ldw\t$dst, $src",
                    [(set GR16:$dst, imm:$src)]>;
}
