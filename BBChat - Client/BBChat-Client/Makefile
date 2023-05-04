SFML_PATH=/usr/local/Cellar/sfml/2.5.1/
CXXFLAGS= -std=c++14 -I${SFML_PATH}include/
LIBS=-lsfml-network -lsfml-system -pthread
CPPFLAGS=
LDFLAGS=-L${SFML_PATH}lib/

all: client server

server: server.o receiver.o accepter.o util.o
	g++ -o $@ $(LDFLAGS) $^ $(LIBS)

client: client.o receiver.o util.o
	g++ -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	\rm -f *.o client server

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/SFML-2.2/
