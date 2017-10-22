//===-- STM8ISelLowering.cpp - STM8 DAG Lowering Implementation  ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the STM8TargetLowering class.
//
//===----------------------------------------------------------------------===//

#include "STM8ISelLowering.h"
#include "STM8.h"
#include "STM8MachineFunctionInfo.h"
#include "STM8Subtarget.h"
#include "STM8TargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "stm8-lower"

STM8TargetLowering::STM8TargetLowering(const TargetMachine &TM,
                                           const STM8Subtarget &STI)
    : TargetLowering(TM) {
    // Set up the register classes.
    addRegisterClass(MVT::i8,  &STM8::GR8RegClass);
    addRegisterClass(MVT::i16, &STM8::GR16RegClass);

    // Compute derived properties from the register classes
    computeRegisterProperties(STI.getRegisterInfo());

    // Provide all sorts of operation actions
    setStackPointerRegisterToSaveRestore(STM8::SP);
    setBooleanContents(ZeroOrOneBooleanContent);
    setBooleanVectorContents(ZeroOrOneBooleanContent); // FIXME: Is this correct?

    // Use the default implementation.
    setOperationAction(ISD::VACOPY, MVT::Other, Expand);
    setOperationAction(ISD::VAEND, MVT::Other, Expand);
    setOperationAction(ISD::STACKSAVE, MVT::Other, Expand);
    setOperationAction(ISD::STACKRESTORE, MVT::Other, Expand);
}

SDValue STM8TargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &dl,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
      return Chain;
}

SDValue
STM8TargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                  bool isVarArg,
                                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                                  const SmallVectorImpl<SDValue> &OutVals,
                                  const SDLoc &dl, SelectionDAG &DAG) const {
      return DAG.getNode(STM8ISD::RET_FLAG, dl, MVT::Other, Chain);
}

const char *STM8TargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch ((STM8ISD::NodeType)Opcode) {
  case STM8ISD::FIRST_NUMBER:       break;
  case STM8ISD::RET_FLAG:           return "STM8ISD::RET_FLAG";
  }
  return nullptr;
}
