#ifndef AdvancedServer_hpp
#define AdvancedServer_hpp

#include <stdio.h>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>

#include "SimpleServer.hpp"

namespace HDE
{
    struct ServerStats {
        int total_requests = 0;
        int active_connections = 0;
        std::chrono::steady_clock::time_point start_time;
        std::vector<std::string> recent_logs;
    };

    class AdvancedServer : public SimpleServer {
    private:
        char buffer[3000] = {0};
        int new_socket;
        std::string public_dir;
        std::map<std::string, std::string> mime_types;
        ServerStats stats;
        
        void accepter();
        void handler();
        void responder();
        
        // Static file serving methods
        std::string get_mime_type(const std::string& filename);
        std::string read_file(const std::string& filepath);
        std::string serve_static_file(const std::string& path);
        std::string serve_admin_panel();
        
        // HTTP parsing methods
        std::string parse_http_request(const std::string& request);
        std::string create_http_response(const std::string& content, const std::string& mime_type, int status_code = 200);
        std::string create_error_response(int status_code, const std::string& message);
        
        // Logging methods
        void log_request(const std::string& client_ip, const std::string& request);
        void add_log(const std::string& message);
        
        // Single-threaded client handler
        void handle_client(int client_socket, std::string client_ip);

    public:
        void launch();
        AdvancedServer();
        ~AdvancedServer();
        
        // Stats methods
        int get_total_requests();
        int get_active_connections();
        std::string get_uptime();
        std::vector<std::string> get_recent_logs();
    };
}

#endif 