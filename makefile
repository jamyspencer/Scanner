CC = g++
CFLAGS  = -g -Wall
TARGET = scanner

OBJECTS = scannerTester.o scanner.o States.o Token.o StrFunctions.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm *.o

scannerTester.o:  scannerTester.cpp scannerTester.h Token.o
	$(CC) $(CFLAGS) -c scannerTester.cpp

scanner.o:  scanner.cpp States.h States.cpp
	$(CC) $(CFLAGS) -c scanner.cpp

States.o: States.h States.cpp StrFunctions.cpp
	$(CC) $(CFLAGS) -c States.cpp

Token.o: Token.h Token.cpp
	$(CC) $(CFLAGS) -c Token.cpp

StrFunctions.o: StrFunctions.h StrFunctions.cpp
	$(CC) $(CFLAGS) -c StrFunctions.cpp
clean:
	rm scanner *.o *~