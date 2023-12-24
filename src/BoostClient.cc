// -----------------------------------------------------------------
// File:   BoostClient.cc
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
// namespace for the project ...
// -----------------------------------------------------------------
namespace dBaseRelease {
void CommunicateWithServer(SOCKET clientSocket) {
    // Hier kannst du die Logik für die Kommunikation mit dem Server implementieren
    // Beispiel: Sende und empfange Daten

//    std::string message = "Hello from client!";
    //send(clientSocket, message.c_str(), message.size(), 0);

    // ---------------------------------------
    // Empfange die Antwort vom Server
    // ---------------------------------------
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // Schließe den Socket
    //closesocket(clientSocket);
}

// -----------------------------------------------------------------
// called function at application end ...
// -----------------------------------------------------------------
void exitFunction()
{
    // ---------------------------------------
    // WinSock beenden
    // ---------------------------------------
    WSACleanup();

    std::cout << "The End."
    << std::endl;
}
}   // namespace: dBaseRelease

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

    try {
        // ------------------------------
        // init MS-Windows socket lib ...
        // ------------------------------
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::string("Fehler beim initializieren von WinSock.");

        // -----------------------
        // Erstelle einen Socket
        // -----------------------
        SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        if (clientSocket == INVALID_SOCKET)
        throw std::string("Failed to create socket");
        
        // ------------------------------
        // Konfiguriere die Serveradresse
        // ------------------------------
        sockaddr_in serverAddr;
        
        serverAddr.sin_family      = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddr.sin_port        = htons(12345);
        
        // ------------------------------
        // Verbinde mit dem Server
        // ------------------------------
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            closesocket(clientSocket);
            throw std::string("Connection failed");
        }
        
        std::cout << "Connected to server!" << std::endl;
        
        std::thread connectionThread(CommunicateWithServer, clientSocket);
        connectionThread.join();
        
    }
    catch (const exception& e) {
        std::cerr << "Exception: "
        << e.what()
        << std::endl;
        
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
