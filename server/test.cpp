#include <stdio.h>

#include "TestServer.hpp"

// Simple test program for the TestServer class
// This file demonstrates how to create and use the basic HTTP server
int main(){
    // Create an instance of TestServer
    // This will initialize the server on port 8080 and start listening for connections
    HDE::TestServer t;
    
    // Note: The server will start listening for connections immediately upon creation
    // However, this simple test doesn't call the launch() method, so it won't actually
    // handle requests. For a working server, use the main.cpp file instead.
    
    return 0;  // Exit the program
}