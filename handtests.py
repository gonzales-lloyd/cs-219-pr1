"""
Handwritten edge-case tests for interp.py

Author: Lloyd Gonzales (lgonzalesna@gmail.com)
"""

from tabulate import tabulate
import tester
import os

FILENAME = tester.FILENAME

# operation, operand1, operand2, expected_out
TESTS = [
    ["ADD", 0b1, 0b1, 0b10], # A + B = C
    ["ADD", 0xFFFFFFFF, 0b1, 0b0], # Overflow
    ["AND", 0b10101010, 0b01010101, 0b0], # Checkerboard = 0
    ["AND", 0xFFFFFFFF, 0x00000000, 0b0], # All 0s = 0
    ["AND", 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF], # All 1s = 1
    ["ASR", (1 << 31), None, (1 << 31 | 1 << 30)], # 1 in MSB -> 1100...
    ["ASR", 0x1, None, 0x0], # Should shift out
    ["ASR", (1 << 30), None, (1 << 29)], # Should keep sign bit, identical to LSR
    ["LSR", (1 << 31), None, (1 << 30)], # No sign bit
    ["LSR", 0x1, None, 0x0], # Should shift out
    ["LSL", 0x1, None, 0b10], # Shift left
    ["LSL", (1 << 31), None, 0x0], # Shift left with only bit on MSB should yield 0
    ["NOT", 0xFFFF0000, None, 0x0000FFFF],
    ["NOT", 0xFFFFFFFF, None, 0x00000000],
    ["ORR", 0xFFFFFFFF, 0x0, 0xFFFFFFFF],
    ["ORR", 0x0, 0x0, 0x0],
    ["SUB", 0b1, 0b1, 0b0], # A - A = 0
    ["SUB", 0b1, 0b10, 0xFFFFFFFF], # Underflow
    ["XOR", 0b10101010, 0b01010101, 0b11111111], # Checkerboard = 1s
    ["XOR", 0xFFFFFFFF, 0xFFFFFFFF, 0x0], # all on = 0 
    ["XOR", 0x0, 0x0, 0x0] # all on = 0 
]

if __name__ == "__main__":
    # generate 

    out_table = []  # 2D table where elements are rows
    expected_outputs = [] # outputs as hex strings

    for test in TESTS:
        row = test[0:3]
        if(test[0] in ["ASR", "LSR", "LSL", "NOT"]):
            # don't try to format None
            out_table.append([row[0], tester.as_formatted_hex(row[1]), row[2]])
        else:
            out_table.append([row[0], tester.as_formatted_hex(row[1]), tester.as_formatted_hex(row[2])])
        
        expected_value = test[3]
        expected_outputs.append(tester.as_padded_formatted_hex(expected_value))

    out_str = tabulate(out_table, tablefmt="plain", stralign="right")
    with open(FILENAME, "w") as fp:
        fp.write(out_str)

    tester.main(expected_outputs, False)