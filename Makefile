# Ironic...

CXX = g++

SRCS = src/main.c                   \
       src/functions/modules/cfg/yaml.cpp     \
       src/functions/modules/oven.cpp         \
       src/functions/modules/run_checks.cpp   \
       src/functions/modules/scripts/cook.cpp \
       src/functions/mapping/map_vars.cpp

TARGET = bin/chef

CXXFLAGS = -Wall -std=c++11

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
