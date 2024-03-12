# Ironic...

CXX = g++

SRCS = main.c                     \
       ./modules/cfg/yaml.cpp     \
       ./modules/oven.cpp         \
       ./modules/run_checks.cpp   \
       ./modules/scripts/cook.cpp \
       ./mapping/map_vars.cpp

TARGET = bin/chef

CXXFLAGS = -Wall -std=c++11

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
