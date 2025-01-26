#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Server{
public:
Server(net::io_context& io_context, short port);
~Server();
void start();

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};