# Ironic...

SRC = src/main.c                \
	src/checks.cpp              \
	src/modules/oven.cpp        \
	src/modules/verify.cpp      \
	src/functions/bake.cpp      \
	src/functions/throw_val.cpp \
	src/cfg/yaml.cpp

cxx = g++

chef: $(SRC)
	$(cxx) -o bin/chef $(SRC)

.PHONY: clean

clean:
	rm -f bin/chef
