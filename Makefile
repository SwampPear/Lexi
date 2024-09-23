CC = g++

TARGET = lexi
SRC_PATH = src
SUB_DIR = src

CFLAGS = -std=c++17 -Wall -I $(SRC_PATH)

all: $(TARGET)

$(TARGET): src/main.cpp src/tokenizer.hpp src/utils.hpp
	$(CC) $(CFLAGS) -o $(TARGET) src/main.cpp

clean:
	$(RM) $(TARGET)