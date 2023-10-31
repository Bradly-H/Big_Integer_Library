#------------------------------------------------------------------------------
#  Makefile for pa6
#
#  make                makes all
#  make Arithmetic     makes Arithmetic
#  make BigIntegerTest makes BigIntegerTest
#  make ListTest       makes ListTest
#  make clean          removes binary files and object files
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17 -Wall

.PHONY: all clean

all: Arithmetic BigIntegerTest ListTest

Arithmetic: Arithmetic.o BigInteger.o List.o
	$(CC) $(CFLAGS) -o Arithmetic Arithmetic.o BigInteger.o List.o

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	$(CC) $(CFLAGS) -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

ListTest: ListTest.o List.o
	$(CC) $(CFLAGS) -o ListTest ListTest.o List.o

%.o : %.cpp
	$(CC) $(CFLAGS) -c -g $<

clean: 
	rm -f Arithmetic BigIntegerClient BigIntegerTest ListTest *.o
