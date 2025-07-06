#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include <stdio.h>
#include "SimpleSocket.hpp"

// ConnectingSocket class - Specialized socket for client applications
// This class extends SimpleSocket and implements the connect() operation
// It's used by clients to connect to remote servers
namespace HDE
{
    class ConnectingSocket : public SimpleSocket
    {
    public: 
        // Constructor - creates a socket and connects it to the specified server
        // domain: Address family (AF_INET for IPv4)
        // service: Socket type (SOCK_STREAM for TCP)
        // protocol: Protocol type (0 for default)
        // port: Port number of the server to connect to
        // interface_addr: Server's IP address
        ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface_addr);
           
        // Virtual function implementation from parent class
        // This method performs the connect() operation to establish a connection to the server
        int connect_to_network(int sock, struct sockaddr_in address);
        
    };
}

#endif