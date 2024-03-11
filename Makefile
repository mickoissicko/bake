# Ironic...

CXX = g++
BIN_DIR = bin
TARGET = $(BIN_DIR)/chef

SRCS = src/main.c		        \
	   src/funcs/bake.cpp       \
	   src/funcs/throw_val.cpp  \
	   src/modules/oven.cpp     \
	   src/modules/verify.cpp 

$(TARGET): $(SRCS)
	$(CXX) $^ -o $@

clean:
	rm -f $(TARGET)

.PHONY: clean
