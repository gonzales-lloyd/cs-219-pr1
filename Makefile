
# Output exe, can change if you want the output to change.
OUTPUT = proj1

# Build object files from all cpp files
.cpp:
	g++ -o $* $*.cpp -std=c++11

# Build from a file named main.cpp and generates objects from the main.cpp in main.o
$(OUTPUT) : main.o $(OUTPUT).o
	g++ -o $@ $@.o main.o -std=c++11

# This section is for if you have a header named header.h
%.o : %.cpp header.h
	g++ -c $< -std=c++11
