#include "SimpleServer.hpp"

namespace HDE
{
    SimpleServer::SimpleServer(int domain, int service, int protocol, int port, unsigned long interface_addr, int bklg)
{
        socket = new ListeningSocket(domain, service, protocol, port, interface_addr, bklg);
    }

    ListeningSocket* SimpleServer::get_socket()
{
    return socket;
    }
}