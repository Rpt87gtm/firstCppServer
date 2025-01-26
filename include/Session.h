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

class Session : public std::enable_shared_from_this<Session>{
public:

Session(tcp::socket soket);
~Session();
void start();

private:
    class Impl;
    std::shared_ptr<Impl> pimpl;

};