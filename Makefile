# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g

all: benchtrie util.o

benchtrie: util.o DictionaryTrie.o DictionaryBST.o DictionaryHashtable.o 

DictionaryTrie.o: DictionaryTrie.cpp

DictionaryBST.o: DictionaryBST.hpp

DictionaryHashtable.o: DictionaryHashtable.hpp

util.o: util.hpp

benchdict.o: benchdict.cpp
	g++ -g -Wall -std=c++11 -o benchdict benchdict.cpp

checkpointTester.o: checkpointTester.cpp
	g++ -g -Wall -std=c++11 checkpointTester.cpp 

clean:
	rm -f benchtrie *.o core* *~

