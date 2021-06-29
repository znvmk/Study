all:server.out client.out 

server.out:server.o unp.o 
	g++ -lpthread -o server.out server.o unp.o 
	
client.out:client.o unp.o 
	g++ -lpthread -o client.out client.o unp.o 

server.o:server.cpp
	g++ -c -o server.o server.cpp

client.o:client.cpp
	g++ -c -o client.o client.cpp

unp.o:../unp/unp.cpp
	g++ -c -o unp.o ../unp/unp.cpp 	

	
.PHONY:clean
clean:
	rm -rf *.o *.out
