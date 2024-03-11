# Ironic...

CXX = g++
BIN_DIR = bin
TARGET = $(BIN_DIR)/chef

SRCS = src/main.c \
       src/scripts/bake.cpp \
	   src/scripts/oven.cpp \
	   src/scripts/verify.cpp

$(TARGET): $(SRCS)
	$(CXX) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: clean
