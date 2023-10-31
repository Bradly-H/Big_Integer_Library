Bradley Haire
bhaire
pa6
CSE 101 Patrick Tantalo
------------------------------------

# Arithmetic.cpp
The main file for this program. This takes 2 commandline arguments, an input file and the output file. The input file should contain 2 numbers, seperated by a line. Negative numbers should be preceded by a "-", positive numbers can be preceded by a "+" or preceded by nothing. These numbers must be integers of arbitrary size. This file will then print out a series of numbers based on specific operations done to those integers. 

# BigInteger.cpp
The implementation of the BigInteger ADT. This ADT relies on the List ADT for its functionality. 

# BigInteger.h
This is the header file for the BigInteger ADT. It is required for compilation of the program. 

# BigIntegerTest.cpp
This is a client file used for testing the BigInteger ADT and can be safely ignored. 

# List.cpp
This is the implementation of the List ADT used by the BigInteger ADT. 

# List.h
This is the header file for the List ADT and is required for compilation

# ListTest.cpp
This is a client file used for testing the List ADT and can be safely ignored

# Makefile
This is the file used to build all of the C++ code into an executable binary. It supports several different commands. 
### make
This command will call make all
### make all
This command compiles the BigIntegerTest, ListTest, and Arithmetic binaries
### make Arithmetic
This command compiles only the Arithmetic binary
### make BigIntegerTest
This command compiles only the BigIntegerTest binary
### make ListTest
This command compiles only the ListTest binary
### make clean
This command removes all .o object files, as well as the BigIntegerTest, ListTest, and Arithmetic binaries, should they exist
