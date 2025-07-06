#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include <stdio.h>
#include "SimpleSocket.hpp"

namespace HDE
{
    class ConnectingSocket : public SimpleSocket
    {
    public: 
        ConnectingSocket(int domain, int service, int protocol, int port, unsigned long interface_addr);
           
        // Virtual function from parent
        int connect_to_network(int sock, struct sockaddr_in address);
        
    };
}

#endif