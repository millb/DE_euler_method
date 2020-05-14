CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -fpic -g

demo: obj/demo.o obj/parser.o
	$(CXX) -o demo obj/demo.o obj/parser.o -ldl

main.so: obj/parser.o
	$(CXX) -o main.so -shared obj/parser.o -ldl

obj/demo.o: demo.cpp
	$(CXX) -c -o obj/demo.o demo.cpp $(CXXFLAGS) 

obj/parser.o: parser.cpp parser.hpp
	$(CXX) -c -o obj/parser.o parser.cpp $(CXXFLAGS) 