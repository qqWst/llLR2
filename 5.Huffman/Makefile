CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = main

SOURCES = main.cpp Huffman.cpp ../structs/flist.cpp ../structs/tree.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)