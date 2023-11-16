PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o CrossRef.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

CrossRef.o : CrossRef.o CrossRefListNode.h BinaryTree.h BST.h CrossRef.h
	$(CC) $(CPPFLAGS) -c CrossRef.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make