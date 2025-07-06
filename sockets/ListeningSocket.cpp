#include "ListeningSocket.hpp"

// Constructor: Creates a ListeningSocket by calling the parent constructor and starting to listen
// This constructor creates a socket, binds it to the specified port, and starts listening for connections
HDE :: ListeningSocket :: ListeningSocket(int domain, int service, int protocol, int port, unsigned long interface_addr, int bklg) :
    BindingSocket(domain, service, protocol, port, interface_addr)
{
    // Store the backlog value for pending connections
    backlog = bklg;
    // Start listening for incoming connections
    start_listening();
    // Verify that the listen operation was successful
    test_connection(listening);
}

// Starts listening for incoming connections
// This method puts the socket in a passive state where it can accept client connections
void HDE :: ListeningSocket :: start_listening()
{
    // Call the listen() system call to start accepting connections
    // The socket must be bound before calling listen()
    listening = listen(get_sock() , backlog);
}

// Getter: Returns the result of the listen() operation
// A successful listen operation returns 0, failure returns -1
int HDE:: ListeningSocket:: get_listening()
{
    return listening;
}

// Getter: Returns the backlog queue size
// This is the maximum number of pending connections that can be queued
int HDE:: ListeningSocket:: get_backlog()
{
    return backlog;
}