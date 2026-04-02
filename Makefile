CC = clang
BASE_FLAGS = -std=c11 -Wall -Wextra -pedantic -D_POSIX_C_SOURCE=200809L
SRC = src/*.c
TARGET = build/minidb

debug:
	mkdir -p build
	$(CC) $(BASE_FLAGS) -g -O0 -fsanitize=address $(SRC) -o $(TARGET)_debug

build:
	mkdir -p build
	$(CC) $(BASE_FLAGS) -O3 -ffast-math -march=native -flto $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf build
