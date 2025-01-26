#include "Session.h"
#include <iostream>
#include <string>

class Session::Impl : public std::enable_shared_from_this<Impl>{
public:
    Impl(tcp::socket socket):
        socket_(std::move(socket)){}

    void start(){
        read_request();
    }
private:
    tcp::socket socket_;
    beast::flat_buffer buffer_{8192};
    http::request<http::string_body> request_;
    http::response<http::string_body> response_;
    
    void read_request(){
        auto self = shared_from_this();
        http::async_read(socket_,buffer_,request_,[this, self](beast::error_code ec, std::size_t butes_transferred){
            if(!ec){
                process_request();
            }
        });
    }

    void process_request(){
        std::string body(10*1024*1024,'a');

        response_.version(request_.version());
        response_.result(http::status::ok);
        response_.set(http::field::server, "Boost.Beast HTTP Server");
        response_.set(http::field::content_type, "text/plain");
        response_.body() = body;
        response_.prepare_payload();
        write_response();
    }

    void write_response(){
        auto self = shared_from_this();
        http::async_write(socket_,response_,[this, self](beast::error_code ec, std::size_t butes_transferred){
            if(!ec){
                socket_.shutdown(tcp::socket::shutdown_send, ec);
            }
        });
    }
};

Session::Session(tcp::socket socket) : pimpl(std::make_shared<Impl>(std::move(socket))){};
Session::~Session() = default;

void Session::start(){
    pimpl->start();
}