# CC = g++ -std=c++11 -Wall -Werror -Wextra
CC = g++ -std=c++11
CFLAGS = -o
ADDITIONAL_FLAGS = -g 
INFILENAME = main.cpp
OUTFILENAME = main.exe
SRCFILES = CSCMatrix.cpp
OBJECTS = CSCMatrix.o 
HFILES = random_add.h CSCMatrix.h 

all: test-1 clear

test-1: $(OBJECTS) $(HFILES)
	$(CC) $(INFILENAME) $(OBJECTS) $(CFLAGS) $(OUTFILENAME)
	./$(OUTFILENAME)

random_add.o: random_add.h
	$(CC) -c random_add.h

CSCMatrix.o: $(SRCFILES) $(HFILES)
	$(CC) -c $(SRCFILES)

clear:
	rm *.o