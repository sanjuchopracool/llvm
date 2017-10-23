set(LLVM_TARGET_DEFINITIONS STM8.td)

tablegen(LLVM STM8GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM STM8GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM STM8GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM STM8GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM STM8GenCallingConv.inc -gen-callingconv)
tablegen(LLVM STM8GenSubtargetInfo.inc -gen-subtarget)
add_public_tablegen_target(STM8CommonTableGen)

add_llvm_target(STM8CodeGen
#  STM8BranchSelector.cpp
  STM8ISelDAGToDAG.cpp
  STM8ISelLowering.cpp
  STM8InstrInfo.cpp
  STM8FrameLowering.cpp
  STM8RegisterInfo.cpp
  STM8Subtarget.cpp
  STM8TargetMachine.cpp
  STM8AsmPrinter.cpp
  STM8MCInstLower.cpp
  )

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
