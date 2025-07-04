#include "SimpleSocket.hpp"

namespace HDE
{
    // Constructor definition
    SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
    {
        // Fill address structure
        address.sin_family = domain;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = htonl(interface);

        // Create socket
        sock = socket(domain, service, protocol);
        test_connection(sock);

      
    }

    // Test if connection or socket was successful
    void SimpleSocket::test_connection(int item_to_test)
    {
        if (item_to_test < 0)
        {
            perror("Failed to connect...");
            exit(EXIT_FAILURE);
        }
    }

    // Getter: return address
    struct sockaddr_in SimpleSocket::get_address()
    {
        return address;
    }

    // Getter: return socket descriptor
    int SimpleSocket::get_sock()
    {
        return sock;
    }

    // Getter: return connection status
    int SimpleSocket::get_connection()
    {
        return connection;
    }
}
