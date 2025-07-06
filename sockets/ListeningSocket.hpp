#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include "BindingSocket.hpp"
#include <stdio.h>

namespace HDE {


    class ListeningSocket   : public BindingSocket{

        private:

        int backlog;
        int listening;

        public: 

        ListeningSocket(int domain, int service ,int protocol, int port , unsigned long interface_addr, int bklg);  
    
void start_listening();
        int get_listening();
        int get_backlog();

    };


}

#endif