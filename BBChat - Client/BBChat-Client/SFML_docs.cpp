#include <iostream>
#include <cstdlib>
#include <sstream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace sf;


// ----- The client -----
void client()
{
	// Create a socket and connect it to 192.168.1.50 on port 55001
	sf::TcpSocket socket;
	socket.connect("127.0.0.1", 55001);
	// Send a message to the connected host
	std::string message = "Hi, I am a client";
	socket.send(message.c_str(), message.size() + 1);
	// Receive an answer from the server
	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The server said: " << buffer << std::endl;
}
// ----- The server -----
void server()
{
	// Create a listener to wait for incoming connections on port 55001
	sf::TcpListener listener;
	listener.listen(55001);
	// Wait for a connection
	sf::TcpSocket socket;
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
	// Receive a message from the client
	char buffer[1024];
	std::size_t received = 0;
	socket.receive(buffer, sizeof(buffer), received);
	std::cout << "The client said: " << buffer << std::endl;
	// Send an answer
	std::string message = "Welcome, client";
	socket.send(message.c_str(), message.size() + 1);
}