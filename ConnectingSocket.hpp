#ifdef ConnectingSocket_cpp
#include "ConnectingSocket.h"

#include <stdio.h>


#include "SimpleSocket.hpp"

namespace HDE
{
    class ConnectingSocket : public SimpleSocket
    {
    public: 
        ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
           
        // Virtual function from parent
        int connect_to_network(int sock, struct sockaddr_in address) ;
        
    };
}

#endif