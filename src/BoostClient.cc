// -----------------------------------------------------------------
// File:   BoostClient.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <cstdlib>
# include <iostream>
# include <thread>

# include <boost/asio.hpp>
# include <boost/array.hpp>

# include <openssl/ssl.h>
# include <openssl/err.h>

using namespace boost::asio;
using namespace std;

// -----------------------------------------------------------------
// namespace for the project ...
// -----------------------------------------------------------------
namespace dBaseRelease {
SSL_CTX * ssl_context;
SSL     * ssl_connection;

void read_from_server(ip::tcp::socket& socket) {
    char buffer[1024];
    int  bytes_recieved;
    
    try {
        // ------------------------------------
        // Zugriff auf den Socket-Deskriptor
        // ------------------------------------
        ip::tcp::socket::native_handle_type socket_descriptor =
        socket.native_handle();
        
        // ------------------------------------
        // Setze die Verbindung zum Server auf
        // ------------------------------------
        SSL_set_fd(ssl_connection, socket_descriptor);
        
        if (SSL_connect(ssl_connection) != 1) {
            std::cerr << "Fehler beim Herstellen der SSL-Verbindung." << std::endl;
            ERR_print_errors_fp(stderr);
            return;
        }

        while(true) {
            bytes_recieved = SSL_read(ssl_connection, buffer, sizeof(buffer));
            
            if (bytes_recieved <= 1) {
                std::cerr
                << "Error: could not read data from server."
                << std::endl;
                break;
            }
            
            std::cout
            << "Empfangene Daten: "
            << std::string(buffer, bytes_recieved)
            << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::string error_message;
        for (int len = 0; len < strlen(e.what()); ++len) {
            if (e.what()[len] == '[') break;
            error_message.push_back(e.what()[len]);
        }
        std::cerr
        << "Exception "
        << error_message
        << std::endl;
    }
}

// -----------------------------------------------------------------
// called function at application end ...
// -----------------------------------------------------------------
void exitFunction()
{
    // Schließe die Verbindung und räume auf
    SSL_shutdown(ssl_connection);
    SSL_free    (ssl_connection);
    SSL_CTX_free(ssl_context);
}
}

// -----------------------------------------------------------------
// client entrypoint/connection member ...
// -----------------------------------------------------------------
int main() {
    using namespace dBaseRelease;
    
    // ---------------------------------------
    // register "atexit" calling function ...
    // ---------------------------------------
    if (atexit(exitFunction) != 0) {
        std::cerr << "Failed to register exit function." << std::endl;
        return EXIT_FAILURE;
    }

    // -----------------------
    // initialize OpenSSL ...
    // -----------------------
    SSL_library_init();
    SSL_load_error_strings();    
    
    // -----------------------
    // create an SSL-Context
    // -----------------------
    ssl_context = SSL_CTX_new(SSLv23_client_method());
    if (!ssl_context) {
        std::cerr << "Fehler beim Erstellen des SSL-Kontexts." << std::endl;
        return EXIT_FAILURE;
    }

    // -----------------------
    // create an SSL-Object
    // -----------------------
    ssl_connection = SSL_new(ssl_context);
    if (!ssl_connection) {
        std::cerr << "Fehler beim Erstellen des SSL-Objekts." << std::endl;
        return EXIT_FAILURE;
    }
    
    // ------------------------------------------------
    // create a end-to-end connection point ...
    // ------------------------------------------------
    io_service service;
    ip::tcp::socket socket(service);
    ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 1234);
    
    try {
        // ----------------------------------------------
        // Use a separate thread to read from the server
        // ----------------------------------------------
        socket.connect(endpoint);
        std::thread([&socket](){ read_from_server(socket); }).detach();

        // ----------------------------------------------
        // Main thread can perform other tasks
        // For simplicity, we'll just sleep for a while
        // ----------------------------------------------
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    catch (const boost::system::system_error& e) {
        std::string error_message;
        for (int len = 0; len < strlen(e.what()); ++len) {
            if (e.what()[len] == '[') break;
            error_message.push_back(e.what()[len]);
        }
        std::cerr << "Exception "
                  << error_message
                  << std::endl;
                  
        return EXIT_FAILURE;
    }
    catch (const std::exception& e) {
        std::cerr
        << "Exception: "
        << e.what()
        << std::endl;
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
