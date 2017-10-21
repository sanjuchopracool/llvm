//===- STM8RegisterInfo.td - Describe the STM8 Register Info ----*- tblgen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Declaration that describes the STM8 register file
//===----------------------------------------------------------------------===//

class STM8Reg<string n>
  : Register<n> {
  let Namespace = "STM8";
}

// Subregister indices.
let Namespace = "STM8" in
{
  def sub_lo : SubRegIndex<8>;
  def sub_hi : SubRegIndex<8, 8>;
}

class STM8RegWithSubRegs<string n, list<Register> subregs = []>
  : STM8Reg<n> {
  let SubRegs = subregs;
  let SubRegIndices = [sub_hi, sub_lo];
  let CoveredBySubRegs = 1;
}

class STM8Reg8Class<dag reglist>
  : RegisterClass<"STM8", [i8], 8, reglist> {
}

class STM8Reg16Class<dag reglist>
  : RegisterClass<"STM8", [i16], 8, reglist> {
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

// 8 bit registers

def A : STM8Reg<"A">;

def XL : STM8Reg<"XL">;
def XH : STM8Reg<"XH">;
def YL : STM8Reg<"YL">;
def YH : STM8Reg<"YH">;

def PCL : STM8Reg<"PCL">;
def PCH : STM8Reg<"PCH">;
def PCE : STM8Reg<"PCE">;

def CC : STM8Reg<"CC">;

// 16 bit registers
def X : STM8RegWithSubRegs<"X", [XH, XL]>;
def Y : STM8RegWithSubRegs<"Y", [YH, YL]>;

def SP : STM8Reg<"SP">;
def PC : STM8Reg<"PC">;

def GR8  : STM8Reg8Class<(add A, XL, YL, XH, YH)>;
def GR16 : STM8Reg16Class<(add X, Y)>;
