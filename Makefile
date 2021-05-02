xorLL: test.o xorLL.o
	g++ -o xorLL test.o xorLL.o

test.o: test.cpp xorLL.h
	g++ -c test.cpp

xorLL.o: xorLL.cpp xorLL.h
	g++ -c xorLL.cpp
