main.out:main.o hello.o wec.o thread-t.o
	g++ -lpthread -o main.out main.o hello.o wec.o thread-t.o
main.o:main.cpp 
	g++ -c -o main.o main.cpp
hello.o:hello.cpp
	g++ -c -o hello.o hello.cpp
wec.o:wec.cpp
	g++ -c -o wec.o wec.cpp 
thread-t.o:thread-t.cpp
	g++ -c -o thread-t.o thread-t.cpp
	
.PHONY:clean

clean:
	rm -r *.o *.out
