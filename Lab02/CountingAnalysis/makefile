PROG = prog
CC = g++
CPPFlags = -g -wall -std=c++11
OBJS = main.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp  Sorts.h
	$(CC) $(CPPFLAGS) -c main.cpp 

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make