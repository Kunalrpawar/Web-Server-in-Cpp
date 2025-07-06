#include "AdvancedServer.hpp"
#include <iostream>
#include <algorithm>

namespace HDE
{
    // Constructor: Initializes the server, sets up MIME types, and starts the timer
    AdvancedServer::AdvancedServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
        public_dir = "public";
        stats.start_time = std::chrono::steady_clock::now();
        // Set up supported MIME types for static file serving
        mime_types[".html"] = "text/html";
        mime_types[".css"] = "text/css";
        mime_types[".js"] = "application/javascript";
        mime_types[".png"] = "image/png";
        mime_types[".jpg"] = "image/jpeg";
        mime_types[".jpeg"] = "image/jpeg";
        mime_types[".gif"] = "image/gif";
        mime_types[".ico"] = "image/x-icon";
        mime_types[".txt"] = "text/plain";
        mime_types[".json"] = "application/json";
        add_log("Advanced server initialized with static file serving (single-threaded)");
    }

    // Destructor: No cleanup needed for single-threaded mode
    AdvancedServer::~AdvancedServer() {
    }

    // Accepts a new client connection and handles it
    void AdvancedServer::accepter() {
        struct sockaddr_in address = get_socket()->get_address();
        int addrlen = sizeof(address);
        new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            add_log("Failed to accept connection");
            return;
        }
        int client_port = ntohs(address.sin_port);
        std::string client_info = std::string(inet_ntoa(address.sin_addr)) + ":" + std::to_string(client_port);
        add_log("Connection accepted from client: " + client_info);
        // Handle the client request in the main thread
        handle_client(new_socket, client_info);
    }

    // Handler: Not used, logic is in handle_client
    void AdvancedServer::handler() {
    }

    // Responder: Not used, logic is in handle_client
    void AdvancedServer::responder() {
    }

    // Handles a single client request, parses HTTP, serves files, and logs the request
    void AdvancedServer::handle_client(int client_socket, std::string client_ip) {
        char buffer[4096] = {0};
        int bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::string request(buffer);
            // Parse the HTTP request path and user agent
            std::string path = parse_http_request(request);
            std::string user_agent = parse_user_agent(request);
            std::string response;
            int response_code = 200;
            // Serve the requested content or admin panel
            if (path == "/admin") {
                response = serve_admin_panel();
            } else if (path == "/" || path == "/index.html") {
                response = serve_static_file("/index.html");
            } else {
                response = serve_static_file(path);
                if (response.find("404") != std::string::npos) {
                    response_code = 404;
                }
            }
            // Extract IP and port for logging
            size_t colon_pos = client_ip.find(':');
            std::string ip = client_ip.substr(0, colon_pos);
            std::string port = client_ip.substr(colon_pos + 1);
            // Log the request and add to client connections
            log_request(client_ip, path, user_agent, response_code);
            add_client_connection(ip, port, user_agent, path, response_code);
            // Send the HTTP response to the client
            send(client_socket, response.c_str(), response.length(), 0);
        }
        closesocket(client_socket);
        stats.active_connections--;
    }

    // Parses the HTTP request and extracts the requested path
    std::string AdvancedServer::parse_http_request(const std::string& request) {
        std::istringstream iss(request);
        std::string method, path, version;
        iss >> method >> path >> version;
        if (path == "/") {
            path = "/index.html";
        }
        return path;
    }

    // Extracts the User-Agent header from the HTTP request
    std::string AdvancedServer::parse_user_agent(const std::string& request) {
        std::istringstream iss(request);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.find("User-Agent:") == 0) {
                return line.substr(12); // Remove "User-Agent: " prefix
            }
        }
        return "Unknown";
    }

    // Returns the MIME type for a given filename extension
    std::string AdvancedServer::get_mime_type(const std::string& filename) {
        size_t dot_pos = filename.find_last_of('.');
        if (dot_pos != std::string::npos) {
            std::string extension = filename.substr(dot_pos);
            auto it = mime_types.find(extension);
            if (it != mime_types.end()) {
                return it->second;
            }
        }
        return "text/plain";
    }

    // Reads the contents of a file from disk
    std::string AdvancedServer::read_file(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    // Serves a static file from the public directory, returns HTTP response
    std::string AdvancedServer::serve_static_file(const std::string& path) {
        std::string filepath = public_dir + path;
        // Prevent directory traversal attacks
        if (filepath.find("..") != std::string::npos) {
            return create_error_response(403, "Forbidden");
        }
        std::string content = read_file(filepath);
        if (content.empty()) {
            return create_error_response(404, "File not found: " + path);
        }
        std::string mime_type = get_mime_type(path);
        return create_http_response(content, mime_type);
    }

    // Serves the admin panel HTML page
    std::string AdvancedServer::serve_admin_panel() {
        std::string content = read_file(public_dir + "/admin.html");
        if (content.empty()) {
            return create_error_response(404, "Admin panel not found");
        }
        return create_http_response(content, "text/html");
    }

    // Creates a full HTTP response with headers and content
    std::string AdvancedServer::create_http_response(const std::string& content, const std::string& mime_type, int status_code) {
        std::string status_text = (status_code == 200) ? "OK" : 
                                 (status_code == 404) ? "Not Found" : 
                                 (status_code == 403) ? "Forbidden" : "Internal Server Error";
        std::ostringstream response;
        response << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
        response << "Content-Type: " << mime_type << "; charset=utf-8\r\n";
        response << "Content-Length: " << content.length() << "\r\n";
        response << "Connection: close\r\n";
        response << "\r\n";
        response << content;
        return response.str();
    }

    // Creates an HTTP error response with a custom message
    std::string AdvancedServer::create_error_response(int status_code, const std::string& message) {
        std::string html = "<html><head><title>Error " + std::to_string(status_code) + "</title></head>";
        html += "<body><h1>Error " + std::to_string(status_code) + "</h1>";
        html += "<p>" + message + "</p>";
        html += "<p><a href='/'>Go back to home</a></p></body></html>";
        return create_http_response(html, "text/html", status_code);
    }

    // Logs a request and increments request counters
    void AdvancedServer::log_request(const std::string& client_ip, const std::string& request, const std::string& user_agent, int response_code) {
        stats.total_requests++;
        stats.active_connections++;
        std::string log_entry = "[" + client_ip + "] " + request + " (" + std::to_string(response_code) + ")";
        add_log(log_entry);
    }

    // Adds a client connection record for the admin panel
    void AdvancedServer::add_client_connection(const std::string& ip, const std::string& port, const std::string& user_agent, const std::string& path, int response_code) {
        ClientConnection conn;
        conn.ip_address = ip;
        conn.port = port;
        conn.user_agent = user_agent;
        conn.request_path = path;
        conn.response_code = response_code;
        // Get current timestamp for the connection
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::string timestamp = std::ctime(&time_t);
        timestamp.pop_back(); // Remove newline
        conn.timestamp = timestamp;
        stats.client_connections.push_back(conn);
        // Keep only last 100 connections
        if (stats.client_connections.size() > 100) {
            stats.client_connections.erase(stats.client_connections.begin());
        }
    }

    // Adds a log entry to the recent logs
    void AdvancedServer::add_log(const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::string timestamp = std::ctime(&time_t);
        timestamp.pop_back(); // Remove newline
        std::string log_entry = "[" + timestamp + "] " + message;
        stats.recent_logs.push_back(log_entry);
        // Keep only last 50 logs
        if (stats.recent_logs.size() > 50) {
            stats.recent_logs.erase(stats.recent_logs.begin());
        }
        std::cout << log_entry << std::endl;
    }

    // Main server loop: accepts and handles connections
    void AdvancedServer::launch() {
        add_log("Advanced server starting on port 8080 (single-threaded)");
        add_log("Static files directory: " + public_dir);
        add_log("Admin panel available at: http://localhost:8080/admin");
        while (true) {
            accepter();
        }
    }

    // Returns the total number of requests handled
    int AdvancedServer::get_total_requests() {
        return stats.total_requests;
    }

    // Returns the current number of active connections
    int AdvancedServer::get_active_connections() {
        return stats.active_connections;
    }

    // Returns the server uptime as a string
    std::string AdvancedServer::get_uptime() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - stats.start_time);
        return std::to_string(duration.count()) + "s";
    }

    // Returns the recent log entries
    std::vector<std::string> AdvancedServer::get_recent_logs() {
        return stats.recent_logs;
    }

    // Returns the recent client connection records
    std::vector<ClientConnection> AdvancedServer::get_client_connections() {
        return stats.client_connections;
    }
} 