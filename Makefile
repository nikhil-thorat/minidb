CC = clang
CFLAGS = -Wall -Wextra -pedantic
SRC = src/*.c
TARGET = build/minidb

build:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf build
