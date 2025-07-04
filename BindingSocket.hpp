#ifndef BindingSocket_hpp
#define BindingSocket_hpp
#include <stdio.h>
#include "SimpleSocket.hpp"

namespace HDE
{
    class BindingSocket : public SimpleSocket
    {
        public:
  
        //Constructer
        BindingSocket(int domain , int service , int protocol,int port , u_long interface);

        //Virtual function from parent 
        int connect_to_network(int sock, struct sockaddr_in address);
    };
}

#endif