CXX = g++
CXXFLAGS = -std=c++17

TARGET = main
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
ifeq ($(OS),Windows_NT)
	del $(TARGET).exe
else
	rm -f $(TARGET)
endif
