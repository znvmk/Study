all:c.exe s.exe

c.exe:client.cpp
	g++ -o c.exe client.cpp 
s.exe:server.cpp
	g++ -o s.exe server.cpp 

.PHONY:clean
clean:
	rm -rf *.exe
