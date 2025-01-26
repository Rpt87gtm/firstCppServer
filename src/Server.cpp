#include "Server.h"
#include "Session.h"

class Server::Impl
{
public:
    Impl(net::io_context &io_context, short port) : io_context_(io_context),
                                                    acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        std::cout << "Server started on port: " << port << std::endl;
    }

    void start()
    {
        do_accept();
    }

private:
    net::io_context &io_context_;
    tcp::acceptor acceptor_;

    void do_accept()
    {
        auto socket = std::make_shared<tcp::socket>(io_context_);
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec)
                               {
            if(!ec){
                std::cout << "New connection" << std::endl;
                std::make_shared<Session>(std::move(*socket))->start();
            } else{
                std::cout << "Error: " << ec.message() << std::endl;
            }

            do_accept(); });
    }
};

Server::Server(net::io_context &io_context, short port) : pimpl(std::make_unique<Impl>(io_context, port)) {};
Server::~Server() = default;

void Server::start()
{
    pimpl->start();
}