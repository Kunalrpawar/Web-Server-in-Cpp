#ifndef TestServer_hpp
#define TestServer_hpp

#include <stdio.h>

#include "SimpleServer.hpp"



namespace HDE
{
    class TestServer : public SimpleServer{
        private:

        char buffer[3000]={0};
            int new_socket;
            void accepter() ;
            void handler() ;
            void responder(); 



            public:
            void launch() ;
            TestServer();
    }
}