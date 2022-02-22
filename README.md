# cs-219-pr1
This is **project part 2 for CS 219 - Computer Organization**. It is intended to emulate a program capable of interpreting and processing assembly language.

*Note:* I didn't use `using namespace std` for the sake of personal clarity. This should be the sole difference between `code_style.cpp` and my code. I also use snake_case, not camelCase.

The following files were used for testing and can be ignored:
- `tester.py`
- `interp.py`
- `requirements.txt`
- `Programming-Project-*.txt`

## Installation
Install Linux or WSL.

## Usage example
- Run `make`.
- Run `./program <path-to-instruction-file>`.

`handtests.txt` and `Programming-Project-2.txt` are included with this repository, and can be executed with `./program handtests.txt` and `./program Programming-Project-2.txt`, respectively. The first file contains no second operand for functions that do not currently use a second operand; the second file contains 100 lines for each function *with* a second operand..

*Debug only*: To generate new test files, use `interp.py`. For handwritten testing, use `handtests.py`.

This project was tested and built on WSL: Ubuntu 20.04 LTS. It should work anywhere `make` and `g++` are available. (Also tested on Kali 2021.2)

## Development setup

```sh
sudo apt-add-repository ppa:ubuntu-desktop/ubuntu-make
sudo apt-get update
sudo apt-get install ubuntu-make
```
Or use your platform's applicable package manager/steps to get `make` and `g++`.

## References
All links that were used for reference have been listed below:
- https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
- https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
- https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
- https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
- https://en.cppreference.com/w/cpp/string/basic_string/stoul