CC = g++

TARGET = bootstrapper
SRC_PATH = src
SUB_DIR = src

CFLAGS = -std=c++17 -Wall -I $(SRC_PATH)

all: $(TARGET)

lexi: src/main.cpp src/tokenizer.hpp src/utils.hpp
	$(CC) $(CFLAGS) -o lexi src/main.cpp

tests: test/main.cpp src/tokenizer.hpp src/utils.hpp
	$(CC) $(CFLAGS) -o tests test/main.cpp

clean:
	$(RM) lexi
	$(RM) tests