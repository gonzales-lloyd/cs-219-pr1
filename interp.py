"""
Python implementation of the operations defined in Interpreter.cpp.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

import ctypes
from math import floor

def add(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 + operand_2).value

def land(operand_1, operand_2):
    return ctypes.c_uint32(operand_1 & operand_2).value

def asr(operand_1, operand_2):
    # check if 32nd bit is 1 or 0
    # https://stackoverflow.com/questions/28590639/python-check-if-bit-in-sequence-is-true-or-false
    operand = ctypes.c_uint32(operand_1).value
    if(operand & (1<<31)):
        # shift over right, then OR it with a 1 on the 32nd bit
        return (operand >> 1) | (1<<31)
    else:
        # it was a 0 to begin with, and there is no need to insert a leading 0
        return operand >> 1


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
