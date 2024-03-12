# Ironic...

SRC = one_file/main.cpp
cxx = g++

chef: $(SRC)
	$(cxx) -o chef $(SRC)

.PHONY: clean

clean:
	rm -f chef
