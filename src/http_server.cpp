#include "http_server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <curl/curl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

HttpServer::HttpServer(int port) : port_(port), server_fd_(-1){}

void HttpServer::start(){
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0); // TCP socket estab.
    if(server_fd_ == -1){
        cerr<<"Failed to create socket\n";
        return ;
    }   

    sockaddr_in addr{}; // Initializes the address struct for IPv4.
    addr.sin_family = AF_INET; // Address family (IPv4)
    addr.sin_addr.s_addr = INADDR_ANY; //  Accept connections from any IP.
    addr.sin_port = htons(port_); // Converts the port number to network byte order

     int opt = 1;
     /* setsockopt allows the server to restart quickly on the same port (avoiding “Address already in use” errors). */
     setsockopt(server_fd_,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

     if(bind(server_fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        cerr<<"Bind Failed !\n";
        close(server_fd_);
        return ;
     }

     if(listen(server_fd_, 10) < 0){
        cerr << "Listen Failed !\n";
        close(server_fd_);
        return ;
     }


     cout << "Server running on port" << port_ << endl;
     while(true){
        int client_socket = accept(server_fd_, nullptr, nullptr);
        if(client_socket < 0){
            cerr << "Accept failed !\n";
            continue;
        }
        handle_client(client_socket);
        close(client_socket);
     }
     close(server_fd_);
}

void HttpServer::handle_client(int client_socket){
    char buffer[4096] = {0};
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer)-1);
    if(bytes_read <= 0) return;

    string request(buffer);
    if(request.find("GET /joke") == 0 ){
        string joke = fetch_random_jokes();
        string response = build_http_response(joke,"200 OK");
        send(client_socket, response.c_str(), response.size(),0);
    }
    else if(request.find("GET / ") == 0 || request.find("GET /HTTP") == 0){
        string response = build_http_response("Hello, World !\n","200 OK");
        send(client_socket, response.c_str(), response.size(), 0);
    }
    else{
        string response = build_http_response("404 Not Found\n","404 Not Found");
        send(client_socket, response.c_str(), response.size(),0);
    }
}

string HttpServer::build_http_response(const string& body, const string& status){
    string http_status = status.empty() ? "200 OK" : status;
    return "HTTP/1.1 " + http_status + "\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" + body;
}

string HttpServer::build_http_response(const string& body){
    return build_http_response(body,"200 Ok");
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output){
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

string HttpServer::fetch_random_jokes(){
    CURL *curl = curl_easy_init();
    string readBuffer;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://official-joke-api.appspot.com/jokes/random");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    string setup, punchline;
    auto setupPos = readBuffer.find("\"setup\":\"");
    if(setupPos != string::npos){
        setupPos += 9;
        auto endSetup = readBuffer.find("\"",setupPos);
        setup = readBuffer.substr(setupPos, endSetup - setupPos);
    }
    auto punchlinePos = readBuffer.find("\"punchline\":\"");
    if(punchlinePos != string::npos ){
        punchlinePos += 13;
        auto endPunchline = readBuffer.find("\"",punchlinePos);
        punchline = readBuffer.substr(punchlinePos, endPunchline - punchlinePos);
    }
    return setup + "\n" + punchline;
}

