#include "../server/AdvancedServer.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// Main entry point for the C++ Web Server application
// This function initializes Windows Sockets, creates the server instance, and starts the server
int main() {
    // Initialize Windows Sockets (Winsock) - required for networking on Windows
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup failed: " << result << endl;
        return 1;
    }
    
    cout << "Advanced C++ Web Server Starting..." << endl;
    cout << "Features: Static File Serving, Admin Panel, Request Logging" << endl;
    
    try {
        // Create and start the advanced server instance
        // The server will run on port 8080 and serve static files from the public/ directory
        HDE::AdvancedServer server;
        server.launch();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Cleanup Windows Sockets before exiting
    WSACleanup();
    return 0;
}