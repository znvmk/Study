all:server.out client.out

server.out:server.o unp.o 
	g++ -lpthread -o server.out server.o unp.o 
	
client.out:client.cpp
	g++ -o client.out client.cpp

server.o:server.cpp
	g++ -c -o server.o server.cpp

unp.o:../unp/unp.cpp
	g++ -lpthread -c -o unp.o ../unp/unp.cpp 	
	
.PHONY:clean
clean:
	rm -rf *.o *.out
