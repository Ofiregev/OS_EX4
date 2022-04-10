#!make -f

CXX=clang++-9
CXXFLAGS=-pthread -std=c++2a
OBJECTS=server.o stack.o 

all: server
	./$^

client: clientC
	./client 10.9.4.88
	
clientC: client.cpp
	$(CXX) $^ -o client

server: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -ltbb $^ -o server

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o main server ser cli a.out client original