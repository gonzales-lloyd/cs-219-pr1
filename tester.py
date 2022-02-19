"""
Automated test case generator (and runner) for CS 219: PA2. 
No idea how to use googletest so this is the next bestish thing

Do not grade.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

from tabulate import tabulate
import random
import re
from pprint import pprint
import os

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

FILENAME = "Programming-Project-2.txt"


# functions
def as_formatted_hex(uint32):
    return "0x%X"%(uint32)

def as_padded_formatted_hex(uint32):
    return "0x"+("%X"%(uint32)).zfill(8)

def generate_row(operation):
    operand_1 = random.randint(0, 2**32)
    operand_2 = random.randint(0, 2**32)

    return [operation, operand_1, operand_2]

def generate_test_file(filepath):
    # Generate sample input/outputs
    out_table = []  # 2D table where elements are rows
    expected_outputs = [] # outputs as hex strings
    for operation in operations:
        for iteration in range(iterations):
            row = generate_row(operation)
            out_table.append([row[0], as_formatted_hex(row[1]), as_formatted_hex(row[2])])
            
            expected_value = operations[operation](row[1], row[2])
            expected_outputs.append(as_padded_formatted_hex(expected_value))
    
    # Run through tabulate, all elements right aligned with one space padding
    # Identical to PA1's format on paper
    out_str = tabulate(out_table, tablefmt="plain", stralign="right")
    with open(filepath, "w") as fp:
        fp.write(out_str)

    return expected_outputs



def main():
    # Generate input file at fixed location
    expected_out = generate_test_file(FILENAME)

    # Run program with generated input file
    output = os.popen(f"./program {FILENAME}").read()

    # Parse program output
    output_lines = output.split("\n")
    output_hexes = []

    for line in output_lines:
        if line:
            # print(line)
            output_search = re.search('-> (.*)', line, re.IGNORECASE)
            out_hex = output_search.group(1)
            output_hexes.append(out_hex)

    output_count = len(output_hexes)

    # Assert that program output is identical to expected
    if output_count != len(expected_out):
        print("failed: number of groups is not equal to number of inputs")
        print(output)
        print(output_count, expected_out)

    passing = 0
    failing = 0
    for i in range(output_count):
        if expected_out[i] == output_hexes[i]:
            passing += 1
            # print(f"{output_lines[i]} is {expected_out[i] == output_hexes[i]} ({expected_out[i]=}, {output_hexes[i]=})")
        else:
            failing += 1
            print(f"{output_lines[i]} is {expected_out[i] == output_hexes[i]} ({expected_out[i]=}, {output_hexes[i]=})")

    print(f"Summary: {passing} passing, {failing} failing")


if __name__ == "__main__":
    main()