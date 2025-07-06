#include "ConnectingSocket.hpp"

HDE::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface_addr)
    : SimpleSocket(domain, service, protocol, port, interface_addr)
{

    set_connection(connect_to_network(get_sock(), get_address()));
    test_connection(get_connection());

}

//Define the connect_to_network function
int HDE::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address) {
    

    return connect(sock, (struct sockaddr *)&address, sizeof(address));

}