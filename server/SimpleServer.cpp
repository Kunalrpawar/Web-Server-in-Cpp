#include "SimpleServer.hpp"

HDE ::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int backlog)
{
    socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);

  
}


ListeningSocket * HDE::SimpleServer::get_socket()
{
    return socket;
}