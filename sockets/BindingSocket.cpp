#include "BindingSocket.hpp"

// Constructor: Creates a BindingSocket by calling the parent constructor and binding the socket
// This constructor creates a socket and binds it to the specified port and interface
HDE ::BindingSocket :: BindingSocket(int domain, int service, int protocol ,int port , unsigned long interface_addr):
SimpleSocket(domain, service, protocol, port, interface_addr)
{
    // Call the virtual function to bind the socket to the address
    // This associates the socket with the specified port and interface
    set_connection(connect_to_network(get_sock() , get_address()));
    // Verify that the bind operation was successful
    test_connection(get_connection());
}

// Implementation of the virtual connect_to_network function from parent class
// This method performs the bind() operation to associate the socket with a port
// Returns 0 on success, -1 on failure
int HDE :: BindingSocket :: connect_to_network(int sock, struct sockaddr_in address){
    // Bind the socket to the specified address and port
    // This makes the socket listen on the specified interface and port
    return bind(sock , (struct sockaddr *)& address , sizeof(address));
}