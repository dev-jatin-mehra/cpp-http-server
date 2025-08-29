#pragma once
#include <string>

using namespace std;

class HttpServer{
    public:
        explicit HttpServer(int port);
        void start();
    
    private:
        int port_;
        int server_fd_;
        string fetch_random_jokes();
        void handle_client(int client_socket);
        string build_http_response(const string& body);
        string build_http_response(const string& body, const string& status);
};
