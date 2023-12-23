// -----------------------------------------------------------------
// File:   BoostServer.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

# include <iostream>
# include <string>
# include <functional>
# include <thread>
# include <memory>

# include <boost/asio.hpp>
# include <boost/asio/ssl.hpp>

using namespace boost::asio;
using namespace std;

// -----------------------------------------------------------------
// @brief namespace name for Version 1.0.0 of our project ...
// -----------------------------------------------------------------
namespace dBaseRelease
{
std::string ApplicationExeName;

// -----------------------------------------------------------------
// @brief This member handle the exception message text that is use
//         to "try catch" exception's during the runtime of the
//         application.
//
// @param  std::string& message  -  The e.what() message.
// @return nothing
//
// @since  dBaseRelease
// @author paule32
// -----------------------------------------------------------------
void handle_exception(const std::string& message) {
    std::string error_message;
    for (int len = 0; len < message.length(); ++len) {
        if (message[len] == '[') break;
        error_message.push_back(message[len]);
    }
    std::cerr << "Exception "
    << error_message
    << std::endl;
}

class SSLServer: public std::enable_shared_from_this<SSLServer> {
public:
    SSLServer(io_service& service, uint16_t port):
        acceptor_(service, ip::tcp::endpoint(ip::tcp::v4(), port)),
        context_ (ssl::context::tlsv12) {
        
        if (isAcceptorInitialized()
        &&  isContextInitialized ()) {
            std::cout << "acceptor ok" << std::endl;
            std::cout << "context  ok" << std::endl;
            
            start_accept();
        }   else {
            std::cout << "server init error" << std::endl;
        }
    }
private:
    void start_accept() {
        ssl_socket_ = std::make_shared<ssl::stream<ip::tcp::socket> >(acceptor_.get_executor(), context_);

        // ----------------------------------
        // Starte den asynchronen Handshake
        // ----------------------------------
        ssl_socket_->async_handshake(ssl::stream_base::server,
        [this](const boost::system::error_code& error) {
            if (!error) {
                // -----------------------------------
                // Wenn der Handshake erfolgreich ist,
                // akzeptiere die Verbindung
                // -----------------------------------
                if (ssl_socket_ && ssl_socket_->lowest_layer().is_open()) {
                    std::cout << "SSL-Handshake erfolgreich und verbunden."
                    << std::endl;
                    acceptor_.async_accept(ssl_socket_->lowest_layer(),
                    [this](const boost::system::error_code& accept_error) {
                        if (!accept_error) {
                            handle_client();
                        } else {
                            std::cerr
                            << "Accept error: "
                            << accept_error.message()
                            << std::endl;
                        }
                    });
                }   else {
                    std::cerr << "SSL-Handshake erfolgreich, aber Verbindung nicht geöffnet."
                    << std::endl;
                }
            }   else {
                std::cerr
                << "Handshake error: "
                << error.message()
                << " ("
                << error.value()
                << ")"
                << std::endl;
            }
        });
    }
    void handle_client() {
        // ------------------------------------
        // Lese/Schreibe Daten mit ssl_socket_
        // ------------------------------------
        boost::asio::async_read_until(*ssl_socket_, buffer_, '\n',
        [this](const boost::system::error_code& read_error, std::size_t bytes_transferred) {
            if (!read_error) {
                std::istream is(&buffer_);
                std::string received_data;
                std::getline(is, received_data);
                
                std::cout << "Received data from client: "
                << received_data
                << std::endl;

                // -----------------------------------------
                // Hier kannst du auf die empfangenen Daten
                // reagieren und die Antwort vorbereiten
                // -----------------------------------------
                std::string response = "Hello from the server!\n";

                // -----------------------------------------
                // Sende die Antwort an den Client
                // -----------------------------------------
                boost::asio::async_write(*ssl_socket_, boost::asio::buffer(response),
                [this](const boost::system::error_code& write_error, std::size_t) {
                    if (!write_error) {
                        // -----------------------------
                        // Schließe die Verbindung
                        // -----------------------------
                        ssl_socket_->lowest_layer().close();

                        // -----------------------------
                        // Starte die nächste Akzeptanz
                        // -----------------------------
                        start_accept();
                    } else {
                        std::cerr
                        << "Write error: "
                        << write_error.message()
                        << std::endl;
                    }
                });
            }   else {
                std::cerr
                << "Read error: "
                << read_error.message()
                << std::endl;
            }
        });
    }

    // ------------------------------------------------
    // Überprüfung, ob der Acceptor initialisiert wurde
    // ------------------------------------------------
    bool isAcceptorInitialized() const {
        return acceptor_.is_open();
    }

    // ------------------------------------------------
    // Überprüfung, ob der Context initialisiert wurde
    // ------------------------------------------------
    bool isContextInitialized() {
        try {
            // ----------------------------------
            // load certificate, and private key
            // ----------------------------------
            context_.use_certificate_chain_file("server.crt.pem");
            context_.use_private_key_file("server.key.pem", ssl::context::pem);
            return true;
        }
        catch (const boost::system::system_error& e) {
            handle_exception(e.what());
            return false;
        }
    }
private:
    ip::tcp::acceptor acceptor_;
    ssl::context context_;
    std::shared_ptr<ssl::stream<ip::tcp::socket>> ssl_socket_;
    boost::asio::streambuf buffer_;
};
}   // namespace: dBaseRelease

int main(int argc, char **argv) {
    using namespace dBaseRelease;

    try {
        ApplicationExeName = argv[0];
        io_service service;
        
        std::shared_ptr<SSLServer> server = std::make_shared<SSLServer>(service, 12345);
        service.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: "
        << e.what()
        << std::endl;
        
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
