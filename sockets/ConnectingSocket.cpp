#include "ConnectingSocket.hpp"

// Constructor: Creates a ConnectingSocket by calling the parent constructor and connecting to the server
// This constructor creates a socket and establishes a connection to the specified server
HDE::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface_addr)
    : SimpleSocket(domain, service, protocol, port, interface_addr)
{
    // Call the virtual function to connect the socket to the server
    // This establishes a TCP connection to the specified server address and port
    set_connection(connect_to_network(get_sock(), get_address()));
    // Verify that the connect operation was successful
    test_connection(get_connection());
}

// Implementation of the virtual connect_to_network function from parent class
// This method performs the connect() operation to establish a connection to the server
// Returns 0 on success, -1 on failure
int HDE::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address) {
    // Connect the socket to the specified server address and port
    // This initiates a TCP connection to the remote server
    return connect(sock, (struct sockaddr *)&address, sizeof(address));
}