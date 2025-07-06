#include "SimpleSocket.hpp"

namespace HDE
{
    // Constructor: Creates a socket and initializes the address structure
    // This is the base constructor that all socket types use
    SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, unsigned long interface_addr)
    {
        // Initialize the socket address structure with the provided parameters
        address.sin_family = domain;                    // Address family (AF_INET for IPv4)
        address.sin_port = htons(port);                 // Port number (converted to network byte order)
        address.sin_addr.s_addr = htonl(interface_addr); // Interface address (converted to network byte order)

        // Create the socket with the specified parameters
        sock = socket(domain, service, protocol);
        test_connection(sock); // Verify socket creation was successful
    }

    // Tests if a socket or connection operation was successful
    // If the operation failed (returned negative value), prints error and exits
    void SimpleSocket::test_connection(int item_to_test)
    {
        if (item_to_test < 0)
        {
            perror("Failed to connect...");
            exit(EXIT_FAILURE);
        }
    }

    // Setter: Updates the connection status
    // This is used by derived classes to indicate connection success/failure
    void SimpleSocket::set_connection(int conn)
    {
        connection = conn;
    }

    // Getter: Returns the socket address structure
    // This contains the IP address and port information
    struct sockaddr_in SimpleSocket::get_address()
    {
        return address;
    }

    // Getter: Returns the socket file descriptor
    // This is used for socket operations like accept, send, recv
    int SimpleSocket::get_sock()
    {
        return sock;
    }

    // Getter: Returns the connection status
    // Indicates whether the socket is properly connected/bound
    int SimpleSocket::get_connection()
    {
        return connection;
    }
}
