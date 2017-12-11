CC = g++
CFLAGS  = -g -Wall -std=c++11 -fno-inline-functions
TARGET = comp

OBJECTS = main.o Parser.o Scanner.o Node.o States.o token.o StrFunctions.o resolutions.o Assembler.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm *.o

main.o: Parser.cpp Parser.h Node.o
	$(CC) $(CFLAGS) -c main.cpp

Parser.o:  Parser.cpp Parser.h token.o Node.o
	$(CC) $(CFLAGS) -c Parser.cpp
	
Assembler.o:  Assembler.cpp Assembler.h token.o Node.o
	$(CC) $(CFLAGS) -c Assembler.cpp	

Node.o: Node.cpp Node.h
	$(CC) $(CFLAGS) -c Node.cpp

Scanner.o:  Scanner.cpp States.h States.cpp
	$(CC) $(CFLAGS) -c Scanner.cpp

States.o: States.h States.cpp StrFunctions.cpp
	$(CC) $(CFLAGS) -c States.cpp

token.o: token.h token.cpp
	$(CC) $(CFLAGS) -c token.cpp

resolutions.o: resolutions.cpp resolutions.h
	$(CC) $(CFLAGS) -c resolutions.cpp

StrFunctions.o: StrFunctions.h StrFunctions.cpp
	$(CC) $(CFLAGS) -c StrFunctions.cpp

clean:
	rm Scanner *.o *~
