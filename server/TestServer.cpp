#include "TestServer.hpp"   



 HDE:: TestServer:: TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10) {
    // Constructor implementation
    launch();  // Start the server immediately upon creation
    std::cout << "TestServer initialized and launched." << std::endl;
}



void HDE::TestServer::accepter() {

    struct sockaddr_in address;
    get_socket()->get_address();
    int addrlen = sizeof(address);
    // Accept a new connection
    new_socket = accept(socket()->get_sock() , (struct sockaddr *)& address, (socklen_t*)&addrlen);



         read(new_socket, buffer, 3000);

}

void HDE::TestServer::handler() {
    // Handle the request here
    std::cout << "Received request: " << buffer << std::endl;
}

void HDE::TestServer::responder() {
    // Send a response back to the client
    char*hello= "Hello from server";

    write(new_socket, hello, strlen(hello));
    close(new_socket);  
}

void HDE::TestServer::launch() {
   while(true){
    std::cout << "Waiting for a connection..." << std::endl;
    accepter(); 
    handler();
    responder();
    std::cout << "Response sent, waiting for next connection..." << std::endl;
   }
}

