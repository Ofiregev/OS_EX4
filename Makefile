#!make -f

CXX=clang++-9
CXXFLAGS=-pthread -std=c++2a 
OBJECTS=server.o stack.o

all: server
	./$^

client: clientC
	./client localhost
	
clientC: client.cpp
	$(CXX) $^ -o client
	

server: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o server

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o main server ser cli a.out client original