main.out:main.o thread-t.o hello.o
	g++ -lpthread -o main.out main.o thread-t.o hello.o
main.o:main.cpp 
	g++ -c -o main.o main.cpp
thread-t.o:thread-t.cpp
	g++ -c -o thread-t.o thread-t.cpp 
hello.o:hello.cpp
	g++ -c -o hello.o hello.cpp

.PHONY:clean
clean:
	rm -r *.o *.out
