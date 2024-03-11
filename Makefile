# Ironic...

CXX = g++
BIN_DIR = bin
TARGET = $(BIN_DIR)/out

SRCS = src/main.cpp \
       src/bake.cpp

$(TARGET): $(SRCS)
	$(CXX) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: clean
