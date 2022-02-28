in2post.x: in2post.o stack.h
	g++ -o in2post.x in2post.o -std=c++11

in2post.o: in2post.cpp stack.h
	g++ -c in2post.cpp -std=c++11

clean:
	rm *.o
