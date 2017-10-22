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
  let PrintMethod = "printSrcMemOperand";
  let MIOperandInfo = (ops GR8, i8imm);
}

def longmem : Operand<i16> {
  let PrintMethod = "printSrcMemOperand";
  let MIOperandInfo = (ops GR16, i16imm);
}

//===----------------------------------------------------------------------===//
// STM8 Complex Pattern Definitions.
//===----------------------------------------------------------------------===//

def addr : ComplexPattern<iPTR, 2, "SelectAddr", [], []>;

//===----------------------------------------------------------------------===//
// STM8 Instructions.
//===----------------------------------------------------------------------===//

let Constraints = "$srcA = $dst", Uses = [CC] in {
def ADCai : STM8Inst<(outs GR8:$dst), (ins GR8:$srcA, i8imm:$src),
                   "adc\t$srcA, #$src",
                   [(set GR8:$dst, (adde GR8:$srcA, (i8 imm:$src))),
                    (implicit CC)]>;
def ADCar : STM8Inst<(outs GR8:$dst), (ins GR8:$srcA, GR8:$src),
                   "adc\t$srcA, ($src)",
                   [(set GR8:$dst, (adde GR8:$srcA, GR8:$src)),
                    (implicit CC)]>;
}

let isAsCheapAsAMove = 1 in {
def LDWri : STM8Inst<(outs GR16:$dst), (ins i16imm:$src),
                     "ldw\t$dst, #$src",
                     [(set GR16:$dst, imm:$src)]>;
def LDWmr : STM8Inst<(outs), (ins longmem:$dst, GR16:$src),
                     "ldw\t$dst, $src",
                     [(store GR16:$src, addr:$dst)]>;
}

let hasSideEffects = 0 in
def NOP : STM8Inst<(outs), (ins),
                   "nop", []>;

let isReturn = 1 in {
def RET : STM8Inst<(outs), (ins),
                   "ret", [(STM8retflag)]>;
}

let Constraints = "$src = $dst" in
def SWAPW : STM8Inst<(outs GR16:$dst), (ins GR16:$src),
                     "swapw\t$src",
                     [(set GR16:$dst, (bswap GR16:$src))]>;
