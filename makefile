CC = g++
CFLAGS  = -g -Wall
TARGET = scanner

OBJECTS = main.o State.o StrFunctions.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm *.o

main.o:  main.cpp State.h State.cpp
	$(CC) $(CFLAGS) -c main.cpp

State.o: State.h State.cpp StrFunctions.cpp
	$(CC) $(CFLAGS) -c State.cpp

StrFunctions.o: StrFunctions.h StrFunctions.cpp
	$(CC) $(CFLAGS) -c StrFunctions.cpp
clean:
	rm scanner *.o *~