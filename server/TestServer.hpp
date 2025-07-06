#ifndef TestServer_hpp
#define TestServer_hpp

#include <stdio.h>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "SimpleServer.hpp"

// TestServer class - A simple HTTP server implementation for testing purposes
// This class extends SimpleServer and provides basic HTTP request/response functionality
namespace HDE
{
    class TestServer : public SimpleServer{
        private:
            // Buffer to store incoming HTTP requests from clients
            char buffer[3000]={0};
            // Socket descriptor for the accepted client connection
            int new_socket;
            
            // Virtual functions inherited from SimpleServer that must be implemented:
            
            // Accepts incoming client connections
            void accepter() ;
            // Handles and processes the received HTTP request
            void handler() ;
            // Sends HTTP response back to the client
            void responder(); 

        public:
            // Starts the server and begins listening for connections
            void launch() ;
            // Constructor - initializes the server on port 8080
            TestServer();
    };
}

#endif