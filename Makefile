# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lzip -lGraphicsMagick++ -lGraphicsMagick

# Source file
SRC = main.cpp archive.cpp adj.cpp display.cpp

# Executable name
TARGET = main.x

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)