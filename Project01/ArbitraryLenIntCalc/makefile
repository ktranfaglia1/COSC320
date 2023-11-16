PROG = prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o Function.o tinyfiledialogs.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

Function.o : Function.cpp Function.h
	$(CC) $(CPPFLAGS) -c Function.cpp

tinyfiledialogs.o : tinyfiledialogs.c tinyfiledialogs.h
	$(CC) $(CPPFLAGS) -c tinyfiledialogs.c

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make