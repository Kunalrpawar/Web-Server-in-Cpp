#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include "BindingSocket.hpp"
#include <stdio.h>

// ListeningSocket class - Specialized socket for server applications
// This class extends BindingSocket and adds the ability to listen for incoming connections
// It's used by servers to accept client connections
namespace HDE {

    class ListeningSocket : public BindingSocket{

        private:
            // Maximum number of pending connections in the queue
            int backlog;
            // Result of the listen() operation
            int listening;

        public: 
            // Constructor - creates a socket, binds it, and starts listening
            // domain: Address family (AF_INET for IPv4)
            // service: Socket type (SOCK_STREAM for TCP)
            // protocol: Protocol type (0 for default)
            // port: Port number to listen on
            // interface_addr: Interface address to bind to
            // bklg: Backlog queue size for pending connections
            ListeningSocket(int domain, int service ,int protocol, int port , unsigned long interface_addr, int bklg);  
    
            // Starts listening for incoming connections
            // This puts the socket in a state where it can accept client connections
            void start_listening();
            
            // Getter methods:
            
            // Returns the result of the listen() operation
            int get_listening();
            // Returns the backlog queue size
            int get_backlog();
    };
}

#endif