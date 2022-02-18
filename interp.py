"""
Python implementation of the operations defined in Interpreter.cpp.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

import ctypes

def add(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 + operand_2).value

def land(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 | operand_2).value

def asr(operand_1, operand_2):
    return ctypes.c_uint32(operand_1).value >> 1

def lsr(operand_1, operand_2):
    operand = ctypes.c_uint32(operand_1).value 
    # https://stackoverflow.com/questions/64963170/how-to-do-arithmetic-right-shift-in-python-for-signed-and-unsigned-values/64987033#64987033
    # below is representative of 32 bits (i.e. 8 hex 0s + the leading 1 shifted in)
    return (operand % 0x100000000) >> 1

def lsl(operand_1, operand_2):
    return ctypes.c_uint32(operand_1*2).value 

def lnot(operand_1, operand_2):
    return ctypes.c_uint32(~operand_1).value

def lorr(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 | operand_2).value

def sub(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 - operand_2).value

def xor(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 ^ operand_2).value
