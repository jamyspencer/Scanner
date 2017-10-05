CC = g++
CFLAGS  = -g -Wall
TARGET = scanner

OBJECTS = parser.o scanner.o State.o Token.o StrFunctions.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm *.o

parser.o:  parser.cpp parser.h Token.o
	$(CC) $(CFLAGS) -c parser.cpp

scanner.o:  scanner.cpp State.h State.cpp
	$(CC) $(CFLAGS) -c scanner.cpp

State.o: State.h State.cpp StrFunctions.cpp
	$(CC) $(CFLAGS) -c State.cpp

Token.o: Token.h Token.cpp
	$(CC) $(CFLAGS) -c Token.cpp

StrFunctions.o: StrFunctions.h StrFunctions.cpp
	$(CC) $(CFLAGS) -c StrFunctions.cpp
clean:
	rm scanner *.o *~