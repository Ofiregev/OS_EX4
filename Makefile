#!make -f

CXX=clang++-9
CXXFLAGS=-pthread

OBJECTS=server.cpp

all: server
	./$^

client: client.cpp
	$(CXX) $^ -o client
	

server: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o server


clean:
	rm -f *.o main server ser cli a.out client original