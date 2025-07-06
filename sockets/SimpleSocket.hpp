#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <iostream>

#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link winsock library

#include <cstdlib>

// SimpleSocket class - Base class for all socket implementations
// This class provides the fundamental socket functionality and serves as the base
// for more specialized socket types like BindingSocket and ConnectingSocket
namespace HDE
{
    class SimpleSocket
    {
    protected:
        // Socket address structure containing IP address and port information
        struct sockaddr_in address;
        // Socket file descriptor
        int sock;
        // Connection status indicator
        int connection;

    public:
        // Constructor - creates a socket with the specified parameters
        // domain: Address family (AF_INET for IPv4)
        // service: Socket type (SOCK_STREAM for TCP, SOCK_DGRAM for UDP)
        // protocol: Protocol type (0 for default)
        // port: Port number
        // interface_addr: Interface address to bind to
        SimpleSocket(int domain, int service, int protocol, int port, unsigned long interface_addr);

        // Pure virtual function - must be implemented by derived classes
        // This function handles the specific network connection logic
        // (bind for servers, connect for clients)
        virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;

        // Tests if a socket or connection operation was successful
        // If the operation failed (returned negative value), the program exits
        void test_connection(int item_to_test);

        // Setter function - sets the connection status
        void set_connection(int conn);

        // Getter functions:
        
        // Returns the socket address structure
        struct sockaddr_in get_address();
        // Returns the socket file descriptor
        int get_sock();
        // Returns the connection status
        int get_connection();
    };
}

#endif // SimpleSocket_hpp
