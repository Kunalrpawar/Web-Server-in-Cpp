#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <iostream>

#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link winsock library


#include <cstdlib>

namespace HDE
{
    class SimpleSocket
    {
    protected:
        struct sockaddr_in address;
        int sock;
        int connection;

    public:
        // Constructor
        SimpleSocket(int domain, int service, int protocol, int port, unsigned long interface_addr);

        // Pure virtual function (must be implemented by derived classes)
        virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;

        // Function to test socket and connection success
        void test_connection(int item_to_test);

        // Setter function
        void set_connection(int conn);

        // Getter functions
        struct sockaddr_in get_address();
        int get_sock();
        int get_connection();
    };
}

#endif // SimpleSocket_hpp
