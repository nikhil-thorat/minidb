CC = clang
CFLAGS = -std=c11 -Wall -Wextra -pedantic -fsanitize=address -D_POSIX_C_SOURCE=200809L
SRC = src/*.c
TARGET = build/minidb

build:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf build
