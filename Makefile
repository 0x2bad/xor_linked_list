xorLL: test.o
	g++ -o xorLL test.o

test.o: test.cpp xorLL.h
	g++ -c test.cpp -O2

.PHONY: clean
clean:
	rm -f *.o
