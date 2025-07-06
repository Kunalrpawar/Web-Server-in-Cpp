#include "TestServer.hpp"   

HDE::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
    // Constructor implementation
    std::cout << "TestServer initialized." << std::endl;
}

void HDE::TestServer::accepter() {
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    
    // Accept a new connection
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    if (new_socket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return;
    }
    
    std::cout << "Connection accepted from client" << std::endl;
}

void HDE::TestServer::handler() {
    // Clear buffer before reading
    memset(buffer, 0, sizeof(buffer));
    
    // Read data from client
    int bytes_read = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null terminate
        std::cout << "Received request: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to read from client" << std::endl;
    }
}

void HDE::TestServer::responder() {
    // Send a response back to the client
    const char* response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: 25\r\n"
                          "\r\n"
                          "<h1>Hello from server!</h1>";
    
    int bytes_sent = send(new_socket, response, strlen(response), 0);
    
    if (bytes_sent > 0) {
        std::cout << "Response sent successfully" << std::endl;
    } else {
        std::cerr << "Failed to send response" << std::endl;
    }
    
    // Close the connection
    closesocket(new_socket);
}

void HDE::TestServer::launch() {
    std::cout << "Server starting on port 8080..." << std::endl;
    
    while(true) {
        std::cout << "Waiting for a connection..." << std::endl;
        accepter(); 
        handler();
        responder();
        std::cout << "Response sent, waiting for next connection..." << std::endl;
    }
}

