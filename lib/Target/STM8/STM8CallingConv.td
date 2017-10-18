//==- STM8CallingConv.td - Calling Conventions for STM8 -*- tablegen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for STM8 architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// STM8 Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_STM8 : CallingConv<[
  // i8 are returned in registers R12B, R13B, R14B, R15B
  CCIfType<[i8], CCAssignToReg<[R12B, R13B, R14B, R15B]>>,

  // i16 are returned in registers R12, R13, R14, R15
  CCIfType<[i16], CCAssignToReg<[R12, R13, R14, R15]>>
]>;

//===----------------------------------------------------------------------===//
// STM8 Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_STM8_AssignStack : CallingConv<[
  // Pass by value if the byval attribute is given
  CCIfByVal<CCPassByVal<2, 2>>,

  // Promote i8 arguments to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // Integer values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;

