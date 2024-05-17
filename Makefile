# Ironic...

CXX = g++

SRCS = src/main.cpp         \
       src/oven.cpp         \
       src/run_checks.cpp   \
       src/cook.cpp         \
       src/map_vars.cpp

TARGET = bin/chef

CXXFLAGS = -Wall -std=c++17

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
