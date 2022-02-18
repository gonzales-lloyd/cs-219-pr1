"""
Automated test case generator (and runner) for CS 219: PA2. 

Do not grade.

Author: Lloyd Gonzales (lgonzalesna@nevada.unr.edu)
"""

import tabulate
import random

operations = ["ADD"]
iterations = 3

def generate_row(operation):
    operand_1 = random.randint(0, 2**32)
    operand_2 = random.randint(0, 2**32)

    return [operation, operand_1, operand_2]

def generate_test_file(filepath):
    out_table = []
    for operation in operations:
        for iteration in range(iterations):
            generate_row(operation)

def main():
    # Generate input file at fixed location

    # Run program with generated input file

    # Parse program output

    # Assert that program output is identical to expected