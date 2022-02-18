"""
Automated test case generator (and runner) for CS 219: PA2. 

Do not grade.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

import tabulate
import random
import interp

# definitions
operations = {
    "ADD": interp.add,
    "AND": interp.land,
    "ASR": interp.asr,
    "LSR": interp.lsr,
    "LSL": interp.lsl,
    "NOT": interp.lnot,
    "ORR": interp.lorr,
    "SUB": interp.sub,
    "XOR": interp.xor
}
iterations = 3


# functions
def as_formatted_hex(uint32):
    return "0x%X"%(uint32)

def generate_row(operation):
    operand_1 = random.randint(0, 2**32)
    operand_2 = random.randint(0, 2**32)

    return [operation, operand_1, operand_2]

def generate_test_file(filepath):
    # Generate sample input/outputs
    out_table = []  # 2D table where elements are rows
    expected_outputs = [] #
    for operation in operations:
        for iteration in range(iterations):
            generate_row(operation)



def main():
    # Generate input file at fixed location

    # Run program with generated input file

    # Parse program output

    # Assert that program output is identical to expected