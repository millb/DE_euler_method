CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

demo: obj/demo.o main.so
	$(CXX) -o demo obj/demo.o main.so

main.so: obj/parser.o
	$(CXX) -o main.so -shared -fpic obj/parser.o

obj/demo.o: demo.cpp
	$(CXX) -c -o obj/demo.o demo.cpp $(CXXFLAGS) 

obj/parser.o: parser.cpp
	$(CXX) -c -o obj/parser.o parser.cpp $(CXXFLAGS) 