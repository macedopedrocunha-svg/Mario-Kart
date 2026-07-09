CC = gcc
CFLAGS = -Wall -g
TARGET = main
OBJS = main.o function.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c function.h
	$(CC) $(CFLAGS) -c main.c

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

clean:
	rm -f *.o $(TARGET)s