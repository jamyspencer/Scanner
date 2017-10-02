CC = g++
CFLAGS  = -g -Wall
TARGET = scanner

OBJECTS = main.o State.o MyStringFunctions.o



$(TARGET):  $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o:  main.cpp State.h State.cpp
	$(CC) $(CFLAGS) -c main.cpp

State.o: State.h State.cpp MyStringFunctions.cpp
	$(CC) $(CFLAGS) -c State.cpp

MyStringFunctions.o: MyStringFunctions.h MyStringFunctions.cpp
	$(CC) $(CFLAGS) -c MyStringFunctions.cpp
clean:
	rm scanner *.o *~