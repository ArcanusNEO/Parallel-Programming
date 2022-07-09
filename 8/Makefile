CC = gcc
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Ofast -Iinc
OBJ = constant.o
INC = 

vpath %.hh inc
vpath %.cc src

.PHONY: all
all: list

list: $(OBJ) $(INC) list_matrix.o list.cc
	$(CXX) $(CXXFLAGS) -o list $(OBJ) list_matrix.o $$(find -name 'list.cc')

list_matrix.o: list_matrix.hh list_matrix.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'list_matrix.cc')

constant.o: constant.hh constant.cc
	$(CXX) $(CXXFLAGS) -c $$(find -name 'constant.cc')

.PHONY: clean
clean: 
	rm -rf *.o