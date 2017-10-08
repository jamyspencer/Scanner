CC = g++
CFLAGS  = -g -Wall -std=c++11 -fno-inline-functions
TARGET = scanner

OBJECTS = main.o scannerTester.o Scanner.o States.o token.o StrFunctions.o resolutions.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm *.o

main.o: scannerTester.cpp scannerTester.h
	$(CC) $(CFLAGS) -c main.cpp

scannerTester.o:  scannerTester.cpp scannerTester.h token.o
	$(CC) $(CFLAGS) -c scannerTester.cpp

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
