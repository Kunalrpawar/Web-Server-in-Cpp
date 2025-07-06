#include "SimpleServer.hpp"

namespace HDE
{
    // Constructor: Creates a new SimpleServer instance with the specified socket parameters
    // This constructor initializes the listening socket that will accept incoming connections
    SimpleServer::SimpleServer(int domain, int service, int protocol, int port, unsigned long interface_addr, int bklg)
{
        // Create a new ListeningSocket instance with the provided parameters
        // This socket will be bound to the specified port and interface
        socket = new ListeningSocket(domain, service, protocol, port, interface_addr, bklg);
    }

    // Getter method: Returns a pointer to the listening socket
    // This allows derived classes to access the socket for accepting connections
    ListeningSocket* SimpleServer::get_socket()
{
    return socket;
    }
}