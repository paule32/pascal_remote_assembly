/**
 * @file:   BoostServer.cc
 * @author: (c) 2023 Jens Kallup - paule32
 *          All rights reserved
 *
 * \cond english
 * @brief only for education, and non-profit usage !
 * \endcond
 *
 * \cond german
 * @brief nur für Bildungszwecke, und non-profit Nutzung !
 * \endcond
 */

/**
 * \cond german
 * @mainpage BOOST Server Projekt
 *
 * Herzlich Willkommen auf der Hauptseite des BOOST Server Projektes !
 * Diese Dokumentation enthält Informationen zur Anwendung.
 *
 * @section intro Einführung
 * Der BOOST Server hat nicht direkt was mit der C++ BOOST-Bibliothek
 * zu tun. Vielmehr ist es eine Server-Anwendung, die es ermöglicht,
 * Terminal Server Anwendungen remote zu betreiben.
 * Dabei werden die Programme "entfernt" ausgeführt, und brauchen nicht
 * lokal auf dem Arbeitsplatz- oder Heimcomputer liegen.
 *
 * <b>Achtung</b>: Der aktuelle Stand ist ein Entwickler-System, was bedeutet,
 *          das keine SSL-Verschlüsselung verwendet wird, um die Verbindung
 *          zwischen Client und Server zu sichern.
 *
 * \example{example1.cc}
 * \endcond
 * \cond english
 * @mainpage BOOST Server Project
 *
 * Welcome to the landing page of the BOOST Server Project !
 * This documentation contain informations about the Server Application
 * \endcond
 */

// -----------------------------------------------------------------
// @brief The follow #define's are used by TurboVision, to automatic
//        include the neccassary headers by this FrameWork.
// -----------------------------------------------------------------
# define Uses_TKeys
# define Uses_TApplication
# define Uses_TWindow
# define Uses_TView
# define Uses_TEvent
# define Uses_TRect
# define Uses_TDialog
# define Uses_TStaticText
# define Uses_TButton
# define Uses_TMenuBar
# define Uses_TSubMenu
# define Uses_TMenuItem
# define Uses_TStatusLine
# define Uses_TStatusItem
# define Uses_TStatusDef
# define Uses_TDeskTop
# define Uses_TChDirDialog
# define Uses_TFileDialog
# define Uses_MsgBox
# define Uses_TDisplay
# define Uses_TScreen
# define Uses_TEditor
# define Uses_TEditWindow
# define Uses_TMemo
# define Uses_TStreamableClass

// -----------------------------------------------------------------
// Microsoft Windows header stuff (winsock must be before windows.h)
// -----------------------------------------------------------------
# include <winsock2.h>
# include <ws2tcpip.h>

# include <windows.h>

// -----------------------------------------------------------------
// standard C header stuff ...
// -----------------------------------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

// -----------------------------------------------------------------
// BORLAND TurboVision - Pascal like Text User Interface (TUI) ...
// -----------------------------------------------------------------
#ifdef  __FLAT__
# undef __FLAT__
#endif

# include <tvision/tv.h>
# include <tvision/help.h>

// -----------------------------------------------------------------
// standard C++ header stuff ...
// -----------------------------------------------------------------
# include <iostream>
# include <string>
# include <sstream>
# include <functional>
# include <thread>
# include <memory>
# include <vector>

// -----------------------------------------------------------------
// for query the data, and time with C++ container ...
// -----------------------------------------------------------------
# include <ctime>
# include <chrono>

using namespace std;

// -----------------------------------------------------------------
// some constant's and variable's used in this source code:
// -----------------------------------------------------------------
# define DT_DATE false  //! get date
# define DT_TIME true   //! get time

// -----------------------------------------------------------------
// @brief this are the "codes" for interactive client/server access.
// -----------------------------------------------------------------
# define CODE_ACCESS_GRANT    200
# define CODE_ACCESS_ERROR    201
# define CODE_ACCESS_PASSWORD 202

// -----------------------------------------------------------------
// @brief namespace name for Version 1.0.0 of our project ...
// -----------------------------------------------------------------
namespace dBaseRelease
{
std::string ApplicationExeName;

/**
 * \fn void handle_exception(const std::string& message)
 * \cond english
 * \brief   This member handle the exception message text that is use
 *          to "try catch" exception's during the runtime of the
 *          application.
 *
 * When an exception is throw, the catch block contain an exception type/class.
 * This type must then provide a referenced object:
 *
 * @section ExampleHeader Example
 * \code{.cpp}
int foo(void) {
    try {
    ...
    }
    catch (exception& e) {
        handle_exception( e.what() );
        
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
 * \endcode
 *
 * \param   message The exception message e.what().
 * \return  nothing
 *
 * \endcond
 * \cond german
 * \brief   Behandelt die im Parameter \a_colorYellow{message}
 *          angegebene Ausnahme-Nachricht.
 *
 * Wenn eine Ausnahme (Exception) auftritt, werden mit dieser Funktion die
 * in \a_colorYellow{message} enthaltenen Zeichen geprüft und entfernt, sofern
 * eine eckige Klammer gefunden wird.
 * Die Ausnahme-Behandlung könnte dann wie folgt aussehen:
 *
 * @section BeispielHeader Beispiel
 * \code{.cpp}
int foo(void) {
    try {
    ...
    }
    catch (exception& e) {
        handle_exception( e.what() );
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
 * \endcode
 *
 * \param   message  -  Die Ausnahme-Nachricht e.what().
 * \return  void
 * \endcond
 *
 * \since  dBaseRelease
 * \author paule32
 */
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

// -----------------------------------------------------------------
// @brief   get the date/time for local server ...
//
// @param  bool mode    -  If mode false, then return date, else time.
//                         The default mode is false.
//
// @return std::string  -  The date or time in std::string format.
//
// @since  dBaseRelease
// @author paule32
// -----------------------------------------------------------------
std::string getDateTime(bool mode = false) {
    auto now = std::chrono::system_clock::now();  // current time
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    
    // -----------------------
    // Lokale Zeit darstellen
    // -----------------------
    std::tm localTime = *std::localtime(&time);
    
    // -----------------------------------
    // Datum aus dem tm-Objekt extrahieren
    // -----------------------------------
    int year   = localTime.tm_year + 1900; // tm_year years since 1900
    int month  = localTime.tm_mon  + 1;    // tm_mon  month 0 to 11
    int day    = localTime.tm_mday;
    
    // -----------------------------------
    // Zeit aus dem tm-Objekt extrahieren
    // -----------------------------------
    int hour   = localTime.tm_hour;
    int minute = localTime.tm_min;
    int second = localTime.tm_sec;
    
    std::stringstream sd, st;
    sd  << year                                        << "-"
        << std::setw(2) << std::setfill('0') << month  << "-"
        << std::setw(2) << std::setfill('0') << day    ;
        
    st  << std::setw(2) << std::setfill('0') << hour   << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second ;
    
    if (!mode)
    return sd.str();
    return st.str();
}

// -----------------------------------------------------------------
// @brief  Each request, and response send/recieve a header + body.
//
// @param  uint32_t bcode   -  The code for the header
// @param  uint32_t btype   -  The type for the header
// @param  uint32_t length  -  The length for the body
//
// @return std::string      -  The combined header string
//
// @since  dBaseRelease
// @author paule32
// -----------------------------------------------------------------
std::string responseHeader(
    uint32_t bcode,
    uint32_t btype,
    uint32_t length) {
    std::stringstream hdr;
    hdr << "VERSION 1"          << std::endl
        << "DATE "   << getDateTime(DT_DATE) << std::endl
        << "TIME "   << getDateTime(DT_TIME) << std::endl
        << "CODE "   << bcode   << std::endl
        << "TYPE "   << btype   << std::endl
        << "LENGTH " << length  << std::endl;

    return hdr.str();
}

std::string responseBody() {
    std::stringstream body;
    body << "Dies ist ein Test." << std::endl
         << "zweite Zeile"       << std::endl;
         
    return body.str();
}

// -----------------------------------------------------------------
// @brief This class handle the user interaction with the client
//        thread.
// -----------------------------------------------------------------
class ClientHandler {
public:
    ClientHandler(SOCKET socket_):
    socket(sock_) {
    }
    // -----------------------------------------
    // send message to the Client, to check the
    // username and password ...
    // -----------------------------------------
    checkUserPassword() {
        std::string message = USERPASSWORD_CODE;
        send(clientSocket, message.c_str(), message.size(), 0);
    }
private:
    SOCKET socket;
};

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
class Server {
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
    #ifdef __WIN32__
    // WinSock beenden
    WSACleanup();
    #eendif

    std::cout << "The End."
    << std::endl;
}

// -----------------------------------------------------------------
// @brief  Starting the TUI - text user interface from command line
//         or console, we check, if this Application is used under
//         Microsoft or Linux, The Microsoft Version need WinMain,
//         under Linux there is "main".
// -----------------------------------------------------------------
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
        #ifdef __WIN32__
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::string("Fehler beim initializieren von WinSock.");
        #endif
        
        ApplicationExeName = argv[0];
        
        Server server(12345);
    }
    catch (const std::exception& e) {
        handle_exception(e.what());
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
