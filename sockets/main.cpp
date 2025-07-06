#include "../server/AdvancedServer.hpp"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup failed: " << result << endl;
        return 1;
    }
    
    cout << "🚀 Advanced C++ Web Server Starting..." << endl;
    cout << "Features: Static File Serving, Multi-Threading, Admin Panel" << endl;
    
    try {
        // Create and start the advanced server
        HDE::AdvancedServer server;
        server.launch();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Cleanup Winsock
    WSACleanup();
    return 0;
}