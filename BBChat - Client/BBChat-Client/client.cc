#include "queue.hpp"
#include "receiver.hpp"
#include "util.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

int main()
{
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
	auto x =  sf::IpAddress::getLocalAddress(); // 127.0.0.1 is local. 	// 0x050a14ac
    auto connect = [&] { return socket->connect(sf::IpAddress::getLocalAddress(), PORT); };
    net_run(connect, "connect");
    std::cout << "Connected\n";
    Queue<std::string> queue;
    // TODO launch a receiver thread to receive messages from the server.
    std::string s = "";
    while (1)
    {
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        // TODO send messages to the server
	}

	system("pause");
    return 0;
}
