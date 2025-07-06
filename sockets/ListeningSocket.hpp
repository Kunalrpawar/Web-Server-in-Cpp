#ifndef "ListeningSocket.hpp"
#define "ListeningSocket.hpp"

#include "BindingSocket.hpp"
#include <stdio.h>

namespace HDE {


    class ListeningSocket   : public BindingSocket{

        private:

        int backlog;
        int listening;

        public: 

        ListeningSocket(int domain, int service ,int protocol, int port , u_long interface int bklg);  
    
void start_listening();

    };


}

#endif