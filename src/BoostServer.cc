// -----------------------------------------------------------------
// File:   BoostServer.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------

# include <winsock2.h>
# include <ws2tcpip.h>

# include <windows.h>

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

# include <iostream>
# include <string>
# include <functional>
# include <thread>
# include <memory>
# include <vector>

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

void HandleClient(SOCKET clientSocket) {
    // -------------------------------
    // Nachricht an den Client senden
    // -------------------------------
    std::string message = "Hello from server!";
    send(clientSocket, message.c_str(), message.size(), 0);
    
    // -------------------------------
    // Schließe den Client-Socket
    // -------------------------------
    closesocket(clientSocket);
}

// -----------------------------------------------------------------
// @brief This class is out main ssl server class ...
// -----------------------------------------------------------------
class SSLServer {
public:
    SSLServer(uint16_t port) {
        if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        throw std::string("Failed to create socket.");
    
        // -------------------------------
        // Konfiguriere die Serveradresse
        // -------------------------------
        serverAddr.sin_family      = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port        = htons(port);
        
        // -------------------------------
        // Binde den Socket an die Adresse
        // -------------------------------
        if (bind(serverSocket, (struct sockaddr*)&serverAddr,
            sizeof(serverAddr)) == SOCKET_ERROR) {
            closesocket(serverSocket);
            throw std::string("Bind failed.");
        }
        
        // -------------------------------
        // Warte auf Verbindungen
        // -------------------------------
        if (listen(serverSocket, 5) == SOCKET_ERROR) {
            closesocket(serverSocket);
            throw std::string("Listen failed.");
        }
        
        std::cout << "Server waiting for connections..."
        << std::endl;
        
        while (true) {
            // -------------------------------
            // Akzeptiere Verbindungen
            // -------------------------------
            SOCKET clientSocket = accept(serverSocket, NULL, NULL);
            if (clientSocket == INVALID_SOCKET) {
                closesocket(serverSocket);
                throw std::string("Accept failed");
            }

            std::cout << "Client connected!" << std::endl;

            // -------------------------------
            // Starte einen Thread für die
            // Bearbeitung des Clients
            // -------------------------------
            threads.emplace_back(&HandleClient, clientSocket);
        }
        
        // --------------------------------
        // Warte auf das Ende aller Threads
        // --------------------------------
        for (auto& thread : threads) {
            thread.join();
        }
        
        // --------------------------------
        // Schließe den Server-Socket
        // --------------------------------
        closesocket(serverSocket);
    }
private:
    SOCKET      serverSocket;
    sockaddr_in serverAddr;
    
    std::vector<std::thread> threads;
};
}   // namespace: dBaseRelease

// -----------------------------------------------------------------
// called function at application end ...
// -----------------------------------------------------------------
void exitFunction(void) {
    // WinSock beenden
    WSACleanup();

    std::cout << "The End."
    << std::endl;
}

int main(int argc, char **argv) {
    using namespace dBaseRelease;

    // ---------------------------------------
    // register "atexit" calling function ...
    // ---------------------------------------
    if (atexit(exitFunction) != 0) {
        std::cerr << "Failed to register exit function."
        << std::endl;
        return EXIT_FAILURE;
    }
    
    try {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::string("Fehler beim initializieren von WinSock.");
        
        ApplicationExeName = argv[0];
        
        SSLServer server(12345);
    }
    catch (const std::exception& e) {
        handle_exception(e.what());
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
