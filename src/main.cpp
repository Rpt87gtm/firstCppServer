#include <iostream>
#include <string>
#include "Server.h"
#include <boost/asio.hpp>


int main(int argc, char* argv[]) {
    try{
        short port;
        if(argc != 2){
            port = 8080;
        } else {
            port = std::atoi(argv[1]);
        }

        net::io_context io_context;
        Server server(io_context, port);

        server.start();
        io_context.run();


    }catch(std::exception& e){
        std::cout << "Exception: "<< e.what() << std::endl;
    }
    return 0;
}