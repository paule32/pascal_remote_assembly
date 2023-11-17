// ------------------------------------------------------------------
// File:   Exception.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// ------------------------------------------------------------------
# include "Parser.h"

# include <boost/bind/bind.hpp>
# include <boost/shared_ptr.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/asio.hpp>

using namespace boost::asio::ip;    // for TCP/ip
using namespace std;                // For time_t, time and ctime;

std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime( &now );
}

class ApplicationTcpConnection
    : public boost::enable_shared_from_this<
      ApplicationTcpConnection >
{
public:
    typedef boost::shared_ptr< ApplicationTcpConnection > pointer;

    static pointer create(
        boost::asio::io_context& io_context) {
        return pointer(new ApplicationTcpConnection(io_context));
    }

    tcp::socket& socket() {
        return socket_;
    }

    void start()
    {
        message_ = make_daytime_string();

        boost::asio::async_write(socket_,
        boost::asio::buffer(message_),
        boost::bind(
            &ApplicationTcpConnection::handle_write,
            shared_from_this(),        
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(
        boost::asio::io_context& io_context)
        : socket_(io_context) {
    }

    void handle_write(
        const boost::system::error_code& error,
        size_t bytes_transferred) {
    }

    tcp::socket socket_;
    std::string message_;
};
