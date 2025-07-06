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
    struct ClientConnection {
        std::string ip_address;
        std::string port;
        std::string user_agent;
        std::string request_path;
        std::string timestamp;
        int response_code;
    };

    struct ServerStats {
        int total_requests = 0;
        int active_connections = 0;
        std::chrono::steady_clock::time_point start_time;
        std::vector<std::string> recent_logs;
        std::vector<ClientConnection> client_connections;
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
        std::string parse_user_agent(const std::string& request);
        std::string create_http_response(const std::string& content, const std::string& mime_type, int status_code = 200);
        std::string create_error_response(int status_code, const std::string& message);
        
        // Logging methods
        void log_request(const std::string& client_ip, const std::string& request, const std::string& user_agent, int response_code);
        void add_log(const std::string& message);
        void add_client_connection(const std::string& ip, const std::string& port, const std::string& user_agent, const std::string& path, int response_code);
        
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
        std::vector<ClientConnection> get_client_connections();
    };
}

#endif 