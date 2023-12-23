// -----------------------------------------------------------------
// File:   BoostServer.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <iostream>
# include <functional>
# include <thread>

# include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

class Server {
public:
    Server(io_service& service, ip::tcp::acceptor& acceptor) : service_(service), acceptor_(acceptor) {}

    void handle_client(ip::tcp::socket socket) {
        std::string message = "Hello, Client!";
        boost::system::error_code ignored_error;
        write(socket, buffer(message), ignored_error);
    }

    void start_accept() {
        while (true) {
            ip::tcp::socket socket(service_);
            acceptor_.accept(socket);

            // Verwende eine Lambda-Funktion, um die Memberfunktion an das Objekt zu binden
            std::thread([this, socket = std::move(socket)]() mutable {
                handle_client(std::move(socket));
            }).detach();
        }
    }

private:
    io_service& service_;
    ip::tcp::acceptor& acceptor_;
};

int main() {
    io_service service;
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 1234));

    Server server(service, acceptor);
    server.start_accept();

    return 0;
}
