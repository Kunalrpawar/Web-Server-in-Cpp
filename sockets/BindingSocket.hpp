#ifndef BindingSocket_hpp
#define BindingSocket_hpp
#include <stdio.h>
#include "SimpleSocket.hpp"

// BindingSocket class - Specialized socket for server applications
// This class extends SimpleSocket and implements the bind() operation
// It's used by servers to bind a socket to a specific port and interface
namespace HDE
{
    class BindingSocket : public SimpleSocket
    {
        public:
  
            // Constructor - creates a socket and binds it to the specified port and interface
            // domain: Address family (AF_INET for IPv4)
            // service: Socket type (SOCK_STREAM for TCP)
            // protocol: Protocol type (0 for default)
            // port: Port number to bind to
            // interface_addr: Interface address to bind to (INADDR_ANY for all interfaces)
            BindingSocket(int domain , int service , int protocol,int port , unsigned long interface_addr);

            // Virtual function implementation from parent class
            // This method performs the bind() operation to associate the socket with a port
            int connect_to_network(int sock, struct sockaddr_in address);
    };
}

#endif