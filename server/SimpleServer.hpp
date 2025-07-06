#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include <stdio.h>

#include "../sockets/ListeningSocket.hpp"
#include "../Networking/hdelibc-networking.hpp"

#include <unistd.h>


namespace HDE
{
    class SimpleServer
    {
    private:
        ListeningSocket* socket;

        virtual void accepter()=0;
        virtual void handler()=0;
        virtual void responder()=0;

        public:
        SimpleServer(int domain, int service, int protocol, int port, unsigned long interface_addr, int bklg);

        virtual void launch()=0;


        ListeningSocket * get_socket();

      
    };
}


#endif