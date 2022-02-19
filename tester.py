"""
Automated test case generator (and runner) for CS 219: PA2. 
No idea how to use googletest so this is the next bestish thing

Do not grade.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

import tabulate
import random
import re
from pprint import pprint

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
            out_table.append(row)
            
            expected_value = operations[operation](row[1], row[2])
            expected_outputs.append(as_formatted_hex(expected_value))
    
    # Run through tabulate, all elements right aligned with one space padding
    # Is not truly identical to PA1's format but it's one extra space
    out_str = tabulate(out_table, format="plain", stralign="left")
    with open(filepath, "w") as fp:
        fp.write(out_str)

    return expected_outputs



def main():
    # Generate input file at fixed location
    expected_out = generate_test_file(FILENAME)

    # Run program with generated input file
    output = os.popen(FILENAME).read()

    # Parse program output
    output_lines = output.split("\n")

    output_search = re.search('-> (.*)\n', line, re.IGNORECASE)
    output_count = len(output_search.groups())

    # Assert that program output is identical to expected
    if output_count != len(expected_out):
        print("failed: number of groups is not equal to number of inputs")
        pprint(output)
        print(output_count, expected_out)

    for i in range(output_count):
        print(f"{output_lines[i]} is {expected_out[i] == output_search.group(i+1)} ({expected_out=}, {output_search.group(i+1)=})")


if __name__ == "__main__":
    main()