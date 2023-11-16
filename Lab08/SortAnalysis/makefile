#Created by Don Spickler  1/28/2022

PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = SortingAlgorithms.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

SortingAlgorithms.o : SortingAlgorithms.o Sorts.h
	$(CC) $(CPPFLAGS) -c SortingAlgorithms.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
