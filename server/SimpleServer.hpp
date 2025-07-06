#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <stdio.h>

#include "../sockets/ListeningSocket.hpp"
#include "../Networking/hdelibc-networking.hpp"

#include <unistd.h>

// SimpleServer class - Abstract base class for HTTP server implementations
// This class defines the interface that all server implementations must follow
// It provides the basic structure for accepting, handling, and responding to HTTP requests
namespace HDE
{
    class SimpleServer
    {
    private:
        // Pointer to the listening socket that accepts incoming connections
        ListeningSocket* socket;

        // Pure virtual functions that must be implemented by derived classes:
        
        // Accepts incoming client connections
        virtual void accepter()=0;
        // Handles and processes the received HTTP request
        virtual void handler()=0;
        // Sends HTTP response back to the client
        virtual void responder()=0;

        public:
        // Constructor - initializes the server with socket parameters
        // domain: Address family (AF_INET for IPv4)
        // service: Socket type (SOCK_STREAM for TCP)
        // protocol: Protocol type (0 for default)
        // port: Port number to listen on
        // interface_addr: Interface address to bind to (INADDR_ANY for all interfaces)
        // bklg: Backlog queue size for pending connections
        SimpleServer(int domain, int service, int protocol, int port, unsigned long interface_addr, int bklg);

        // Pure virtual function - starts the server and begins handling requests
        virtual void launch()=0;

        // Getter method to access the listening socket
        ListeningSocket * get_socket();
    };
}

#endif