#include "http_server.h"

int main(){
    HttpServer server(9000);
    server.start();
    return 0;
}