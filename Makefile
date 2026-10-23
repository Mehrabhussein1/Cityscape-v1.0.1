CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = cityscape.exe
SOURCES = main.c city.c

.PHONY: all run clean

all: run

$(TARGET): $(SOURCES) city.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	.\cityscape.exe

clean:
	del /Q $(TARGET) 2>NUL
