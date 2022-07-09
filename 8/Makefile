CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinc
OBJ = constant.o
INC = matrix.hh

vpath %.hh inc
vpath %.cc src

.PHONY: all
all: simple

simple: $(OBJ) $(INC) simple.cc
	$(CXX) $(CXXFLAGS) -o simple $(OBJ) $$(find -name 'simple.cc')

constant.o: constant.hh constant.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'constant.cc')

.PHONY: clean
clean: 
	rm -rf *.o