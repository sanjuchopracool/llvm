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
    // i8 are returned in registers A
    CCIfType<[i8], CCAssignToReg<[A]>>,
    // i16 are returned in registers X, Y
    CCIfType<[i16], CCAssignToReg<[X, Y]>>
]>;

//===----------------------------------------------------------------------===//
// STM8 Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_STM8_AssignStack : CallingConv<[
    CCIfType<[i8], CCAssignToStack<1, 1>>,
    CCIfType<[i16], CCAssignToStack<2, 1>>
]>;

