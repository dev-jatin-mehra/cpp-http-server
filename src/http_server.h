#pragma once
#include <string>

class HttpServer{
    public:
        explicit HttpServer(int port);
        void start();
    
    private:
        int port_;
        int server_fd_;
        void handle_client(int client_socket);
        std::string build_http_response(const std::string& body);
};
