
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace sf;

//#ifdef SFML_STATIC
//#if _DEBUG
//#pragma comment(lib, "sfml-network-s.lib")
//#else
//#pragma comment(lib, "sfml-network-s-d.lib")
//#endif
//#else
//#if NDEBUG
//#pragma comment(lib, "sfml-network.lib")
//#else
//#pragma comment(lib, "sfml-network-d.lib")
//#endif
//#endif

// ----- The client -----
void client()
{
	// Create a socket and connect it to 192.168.1.50 on port 55001
	sf::TcpSocket socket;
	//local IP address of 127.0.0.1 (loopback address)
	//if (socket.connect("192.168.0.15", 55002) != sf::Socket::Done)
	if (socket.connect("127.0.0.1", 55002) != sf::Socket::Done)
	{
		std::cerr << "Could not connect to the server\n";
		return;
	}
	//// send a message to the connected host
	//std::string message = "Hello, I'm a client";
	//if (socket.send()(message.c_str, message.size() + 1) != sf::Socket::Done)
	//{
	//	std::cerr << "Could not connect\n";
	//	return;
	//}
	char buffer[1024];
	for (int i = 0; i < 3; i++)
	{
		//std::stringstream ss;
		//ss << i;
		//std::string s = ss.str();
		//socket.send(s.c_str(), s.size() + 1);
		buffer[0] = '0' + i;
		buffer[1] = '\0';
		socket.send(buffer, 2);
		//socket.send(s.c_str(), s.size() + 1);
		std::size_t received = 0;
		socket.receive(buffer, sizeof(buffer), received);
		std::cout << "The client received some message on: \
			" << socket.getLocalPort() <<
			" from " << socket.getRemoteAddress() <<
			":" << socket.getRemotePort() << std::endl;
		std::cout << "The server said: " << buffer << std::endl;
	}
}

// ----- The server -----
void server()
{
	// Create a listener to wait for incoming connections on port 55001
	sf::TcpListener listener;
	sf::Socket::Status status = listener.listen(55002);
	if (status != sf::Socket::Done)
	{
		std::cerr << "Could not listen on port 55002\n";
		return;
	}
	//

	for (size_t loop = 0; loop < 2; loop++)
	{
		// Wait for a connection
		sf::TcpSocket socket;
		listener.accept(socket); // Block
		// Create a thread:
		// - Create a class
		// - Instantiate it with socket
		// - launch the thread with void handleClient();
		std::cout << "New client connected: " <<
			socket.getRemoteAddress() <<
			":" << socket.getRemotePort() <<
			" on " << socket.getLocalPort() << std::endl;
		// Receive a message from the client
		char buffer[1024];
		for (int i = 0; i < 3; i++)
		{
			std::size_t received = 0;
			socket.receive(buffer, sizeof(buffer), received);
			std::cout << "The client said: " << buffer << std::endl;
			// Send an answer
			socket.send(buffer, received); // Echo
		}
	}
}

int main()
{
	std::thread Server(server);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::thread Client1(client);
	std::thread Client2(client);
	Client1.join();
	Client2.join();
	Server.join();

	system("pause");
	return 0;
}

