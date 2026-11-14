CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = main

SOURCES = main.cpp flist.cpp ../structs/hash_table.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)