# Ironic...

CXX = g++

SRCS = src/main.c                   \
       src/modules/cfg/yaml.cpp     \
       src/modules/oven.cpp         \
       src/modules/run_checks.cpp   \
       src/modules/scripts/cook.cpp \
       src/mapping/map_vars.cpp

TARGET = bin/chef

CXXFLAGS = -Wall -std=c++11

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
