#include "accepter.hpp"
#include "queue.hpp"
#include "list.hpp"
#include "receiver.hpp"
#include "util.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>


int main()
{
    Queue<std::string> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    // TODO launch an accepter thread.
	// need an acceptor object
	// remem overloading function create operator
	// param queue of thing/messages, list of sockets
    while(1)
    {
        std::string s = queue.pop();
        std::cout << "Main read: \"" << s << "\"\n";
        // TODO send to all in sockets. Be careful to synchronise.
    }

	system("pause");
    return 0;
}
