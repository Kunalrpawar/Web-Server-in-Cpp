#include "TestServer.hpp"   

// Constructor: Initializes the TestServer on port 8080 with TCP protocol
// This creates a basic HTTP server that can accept connections and serve simple responses
HDE::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
    // Constructor implementation
    std::cout << "TestServer initialized." << std::endl;
}

// Accepts incoming client connections
// This method waits for and accepts new TCP connections from clients
void HDE::TestServer::accepter() {
    struct sockaddr_in address = get_socket()->get_address();
    int addrlen = sizeof(address);
    
    // Accept a new connection from the listening socket
    // This blocks until a client connects
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    if (new_socket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return;
    }
    
    std::cout << "Connection accepted from client" << std::endl;
}

// Handles and processes the received HTTP request
// This method reads the HTTP request data from the client socket
void HDE::TestServer::handler() {
    // Clear buffer before reading to ensure clean data
    memset(buffer, 0, sizeof(buffer));
    
    // Read data from client socket into the buffer
    // This reads the HTTP request headers and body
    int bytes_read = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null terminate the received data
        std::cout << "Received request: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to read from client" << std::endl;
    }
}

// Sends HTTP response back to the client
// This method creates and sends a proper HTTP response with headers and content
void HDE::TestServer::responder() {
    // Create a simple HTTP response with proper headers
    // This includes status line, content type, content length, and body
    const char* response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: 25\r\n"
                          "\r\n"
                          "<h1>Hello from server!</h1>";
    
    // Send the response to the client
    int bytes_sent = send(new_socket, response, strlen(response), 0);
    
    if (bytes_sent > 0) {
        std::cout << "Response sent successfully" << std::endl;
    } else {
        std::cerr << "Failed to send response" << std::endl;
    }
    
    // Close the client connection after sending response
    closesocket(new_socket);
}

// Main server loop - starts the server and handles incoming connections
// This method runs indefinitely, accepting and processing client requests
void HDE::TestServer::launch() {
    std::cout << "Server starting on port 8080..." << std::endl;
    
    // Main server loop - continuously accept and handle client connections
    while(true) {
        std::cout << "Waiting for a connection..." << std::endl;
        accepter();  // Accept new connection
        handler();   // Read and process request
        responder(); // Send response back
        std::cout << "Response sent, waiting for next connection..." << std::endl;
    }
}

