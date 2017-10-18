//===-- STM8RegisterInfo.td - STM8 Register defs -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the STM8 register file
//===----------------------------------------------------------------------===//

class STM8Reg<bits<4> num, string n> : Register<n> {
  field bits<4> Num = num;
  let Namespace = "STM8";
}

class STM8RegWithSubregs<bits<4> num, string n, list<Register> subregs> 
  : RegisterWithSubRegs<n, subregs> {
  field bits<4> Num = num;
  let Namespace = "STM8";
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

def PCB  : STM8Reg<0,  "r0">;
def SPB  : STM8Reg<1,  "r1">;
def SRB  : STM8Reg<2,  "r2">;
def CGB  : STM8Reg<3,  "r3">;
def FPB  : STM8Reg<4,  "r4">;
def R5B  : STM8Reg<5,  "r5">;
def R6B  : STM8Reg<6,  "r6">;
def R7B  : STM8Reg<7,  "r7">;
def R8B  : STM8Reg<8,  "r8">;
def R9B  : STM8Reg<9,  "r9">;
def R10B : STM8Reg<10, "r10">;
def R11B : STM8Reg<11, "r11">;
def R12B : STM8Reg<12, "r12">;
def R13B : STM8Reg<13, "r13">;
def R14B : STM8Reg<14, "r14">;
def R15B : STM8Reg<15, "r15">;

def subreg_8bit : SubRegIndex<8> { let Namespace = "STM8"; }

let SubRegIndices = [subreg_8bit] in {
def PC  : STM8RegWithSubregs<0,  "r0",  [PCB]>;
def SP  : STM8RegWithSubregs<1,  "r1",  [SPB]>;
def SR  : STM8RegWithSubregs<2,  "r2",  [SRB]>;
def CG  : STM8RegWithSubregs<3,  "r3",  [CGB]>;
def FP  : STM8RegWithSubregs<4,  "r4",  [FPB]>;
def R5  : STM8RegWithSubregs<5,  "r5",  [R5B]>;
def R6  : STM8RegWithSubregs<6,  "r6",  [R6B]>;
def R7  : STM8RegWithSubregs<7,  "r7",  [R7B]>;
def R8  : STM8RegWithSubregs<8,  "r8",  [R8B]>;
def R9  : STM8RegWithSubregs<9,  "r9",  [R9B]>;
def R10 : STM8RegWithSubregs<10, "r10", [R10B]>;
def R11 : STM8RegWithSubregs<11, "r11", [R11B]>;
def R12 : STM8RegWithSubregs<12, "r12", [R12B]>;
def R13 : STM8RegWithSubregs<13, "r13", [R13B]>;
def R14 : STM8RegWithSubregs<14, "r14", [R14B]>;
def R15 : STM8RegWithSubregs<15, "r15", [R15B]>;
}

def GR8 : RegisterClass<"STM8", [i8], 8,
   // Volatile registers
  (add R12B, R13B, R14B, R15B, R11B, R10B, R9B, R8B, R7B, R6B, R5B,
   // Frame pointer, sometimes allocable
   FPB,
   // Volatile, but not allocable
   PCB, SPB, SRB, CGB)>;

def GR16 : RegisterClass<"STM8", [i16], 16,
   // Volatile registers
  (add R12, R13, R14, R15, R11, R10, R9, R8, R7, R6, R5,
   // Frame pointer, sometimes allocable
   FP,
   // Volatile, but not allocable
   PC, SP, SR, CG)>;
