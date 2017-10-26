//===-- STM8InstrFormats.td - STM8 Instruction Formats -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Describe STM8 instructions format here
//

class AddressingMode<bits<4> val>
{
    bits<4> Value = val;
}

def Inherent                        : AddressingMode<0>;
def Immediate                       : AddressingMode<1>;    // Load immediate data 8 or 16 bit
def Direct                          : AddressingMode<2>;      // access data from 16 bit address
def ShortIndexed                    : AddressingMode<3>; // offset is a byte
def LongIndexed                     : AddressingMode<4>;  // offset is 2 byte
def SPIndexed                       : AddressingMode<5>;    // offset with respect to SP is one byte
def LongPointerIndirectLong         : AddressingMode<6>; // address is 2 byte , pointer size is 2 byte
def LongPointerIndirectLongIndexed  : AddressingMode<7>;
def RelativeDirect                  : AddressingMode<8>;
def BitDirect                       : AddressingMode<9>;
def BitDirectRelative               : AddressingMode<10>;

class SizeVal<bits<3> val>
{
    bits<3> Value;
}

def Size1Byte : SizeVal<0>;
def Size2Byte : SizeVal<1>;
def Size3Byte : SizeVal<2>;
def Size4Byte : SizeVal<3>;
def Size5Byte : SizeVal<4>;
def Size6Byte : SizeVal<5>;

class STM8Inst<bits<8> opcode,
               SizeVal size,
               AddressingMode mode,
               dag outs,
               dag ins,
               string asmstr,
               list<dag> pattern>

  : Instruction {

  let Namespace = "STM8";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  SizeVal ISize = size;
  AddressingMode Mode = mode;

  let AsmString = asmstr;
  let Pattern = pattern;
}
