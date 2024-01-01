/**
 * @file:   BoostServer.cc
 * @author: (c) 2023 Jens Kallup - \a_currentAuthors
 *          All rights reserved
 *
 * \cond english
 * \brief only for education, and non-profit usage !
 * \endcond
 *
 * \cond german
 * \brief nur für Bildungszwecke, und non-profit Nutzung !
 *
 * Für dieses Programm ist die kommerzielle Nutzung nicht gestattet.
 * Die Lizenzierung ist zwar mit MIT deklariert, die man bei der Nutzung des
 * github.com Services auferlegt bekommt - jedoch ist eine Eigene Lizenz für
 * dieses Produkt vorgesehen, da die MIT-Lizenz für mich als Entwickler eine
 * Art des Schneeball-Systems darstellt, welches ich nicht unterstützen will.
 * \endcond
 */

/**
 * \cond german
 * @mainpage BOOST Server Projekt
 *
 * Herzlich Willkommen auf der Hauptseite des BOOST Server Projektes !
 * Diese Dokumentation enthält Informationen zur Anwendung.
 *
 * \section intro Einführung
 * Der BOOST Server hat nicht direkt was mit der C++ BOOST-Bibliothek
 * zu tun. Vielmehr ist es eine Server-Anwendung, die es ermöglicht,
 * Terminal Server Anwendungen remote zu betreiben.
 * Dabei werden die Programme "entfernt" ausgeführt, und brauchen nicht
 * lokal auf dem Arbeitsplatz- oder Heimcomputer liegen.
 *
 * \note Der aktuelle Stand ist ein Entwickler-System, was bedeutet,
 *       das keine SSL-Verschlüsselung verwendet wird, um die Verbindung
 *       zwischen Client und Server zu sichern.
 *
 * \section license1 Lizenz
 * Bitte lesen Sie diese Lizenz gründlich durch, bevor Sie den BOOST Server
 * oder Teile dieser Software verwenden wollen. Sollten Sie nicht mit den hier
 * aufgeführten Bedingungen einverstanden sein, ist die Nutzung oder Verwendung
 * des Quellcodes zu diesen Produkt (oder auch Teile davon) nicht gestattet.
 *
 * Bei der Verwendung darf kein kommerzieller Zweck der Gewinnerzielung entstehen !
 *
 * \subsection license2 Geltungsbereich
 * \endcond
 *
 * \cond english
 * @mainpage BOOST Server Project
 *
 * Welcome to the landing page of the BOOST Server Project !
 * This documentation contain informations about the Server Application.
 *
 * @section intro Getting started
 * This BOOST Server Project has nothing to do with the C++ Boost Library
 * directly. It is a free Server Application which make it possible to
 * emulate a Terminal Application Server, to serve remote Application's
 * on local Desktop.
 * So, the Application's you need, dont need to be installed on the local
 * Desktop Computer,
 *
 * <b>Warning</b>: The current state of development provides a non-productive
 *                 System. That means, that no SSL security will be use, to
 *                 secure the Connection between Client, and Server.
 *                 So, you have to use a Terminal Application that support
 *                 encrypting the Connection to Server, and back.
 *
 * \endcond
 * \author \a_currentAuthors
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

/**
 * \cond english
 * \brief  namespace name for \a_currentVersion of this project.
 *
 * This namespace was introduce, to avoid name conflicts between other
 * namespaces and/or function, and class names.
 * \endcond
 *
 * \cond german
 * \brief  Namensraum für das Projekt \a_currentVersion.
 *
 * Dieser Namensraum wurde eingeführt, um Konflikte zwischen anderen
 * Namensräume und/oder Funktion-, und Klassen-Namen zu vermeiden.
 * \endcond
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
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
 * \param[in] message - The exception message from e.what().
 * \section ExampleHeader Example
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
 * \return  void - nothing
 * \endcond
 *
 * \cond german
 * \brief   Behandelt die im Parameter \a_colorYellow{message}
 *          angegebene Ausnahme-Nachricht.
 *
 * Wenn eine Ausnahme (Exception) auftritt, werden mit dieser Funktion die
 * in \a_colorYellow{message} enthaltenen Zeichen geprüft und entfernt, sofern
 * eine eckige Klammer gefunden wird.
 * Die Ausnahme-Behandlung könnte dann wie folgt aussehen:
 *
 * \param[in] message - Die Ausnahme (Exception) Nachricht ausgehend von e.what().
 * \section BeispielHeader Beispiel
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
 * \return  void - nichts
 * \endcond
 *
 * \since  \a_currentVersion
 * \author \a_currentAuthors
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

/**
 * \class  Date
 * \brief  Informationen für die Klasse Date, die verschiedene Funktionen
 *         zur Bearbeitung von Datums-Werte bereitstellt.
 *
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
class Date {
private:
    int year ;    // tm_year years since 1900
    int month;    // tm_mon  month 0 to 11
    int day  ;
public:
    /**
     * \cond german
     * \brief Standard C++ Konstruktor für die Klasse "Date" zur statischen
     *        ermittlung von Datums-Werten.
     *
     * Wenn die Klasse "Date" mit den Standard-Konstruktor aufgerufen wird,
     * werden die aktuellen Daten über das Jahr, Monat, und Tag nur einmal
     * ermittelt, und stehen so als statische Daten für die Verwendung zur
     * Verfügung.
     * Genauere Werte können mit den entsprechenden Funktionen ermittelt
     * werden.
     * \endcond
     *
     * \cond english
     * \brief Standard C++ Constructor for class "Date" to get the static
     *        Date-Informations.
     *
     * When you call this Standard-Constructor, all current data about the
     * year, month, and day will determined only once.
     * Current or actual values can be get by other Function's.
     * \endcond
     *
     * \see getYear()
     * \see getMonth()
     * \see getDay()
     *
     * \see getYearNow()
     * \see getMonthNow()
     * \see getDayNow()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    Date() {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        
        // -----------------------------------
        // Datum aus dem tm-Objekt extrahieren
        // -----------------------------------
        year   = localTime.tm_year + 1900;
        month  = localTime.tm_mon  + 1;
        day    = localTime.tm_mday;
    }
    
    /**
     * \cond german
     * \brief  Gibt das aktuelle Jahr zurück, das während der
     *         initializierung des Konstruktors ermittelt wurde.
     *
     * \return std::string - Das ermittelte Jahr als std::string.
     * \endcond
     *
     * \cond english
     * \brief  Return the current year, that was determined at the
     *         constructing and calling class constructor.
     * \return std::string - The current year as std::string.
     * \endcond
     *
     * \see getMonth()
     * \see getDay()
     *
     * \see getYearNow()
     * \see getMonthNow()
     * \see getDayNow()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getYear() const {
        std::stringstream sd, st;
        ss << year;
        return ss.str();
    }
    
    /**
     * \cond german
     * \brief  Gibt das aktuelle Jahrmit den aktuellen Wert, der bei
     *         aufruf der Funktion gemessen wurde.
     * \return std::string  -  Das aktuelle Jahr, gemessen im "Jetzt"
     * \endcond
     *
     * \cond english
     * \brief  Return the current year at the point from "now" by calling
     *         this Function.
     * \return std::string - The current year as std::string from "now".
     * \endcond
     *
     * \see getYear()
     * \see getMonth()
     * \see getDay()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getYearNow() const {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        year  = localTime.tm_year + 1900;
        std::stringstream ss; ss << year;

        return ss.str();
    }
    
    /**
     * \cond german
     * \brief   Gibt das aktuelle Jahr plus dem im Parameter angebenen "delta"-Jahr
     *          zurück, der beim aufrufen der Funktion gemessen wurde.
     *
     * Gibt den aktuellen Jahres-Werrt plus dem mit den Parameter angegebenen "delta" Jahres-Wert
     * als std::string zurück, der beim aufruf der Funktion gemessen wurde.
     * Es handelt sich hierbei um die lokale Server-Zeit.
     *
     * \return  std::string  -  Das aktuelle Jahr, gemessen im "Jetzt"
     * \endcond
     *
     * \cond english
     * \brief  Return the current year at the point from "now" by calling
     *         this Function.
     * \return std::string - The current year as std::string from "now".
     * \endcond
     *
     * \see getYear()
     * \see getMonth()
     * \see getDay()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getYearNow(uint16_t delta) const {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        year  = localTime.tm_year + 1900 + delta;
        std::stringstream ss; ss << year;

        return ss.str();
    }
    
    /**
     * \cond german
     * \brief  Gibt den Monat des aktuellen Jahres zurück, der während
     *         der initializierung des Konstruktors ermittelt wurde.
     *
     * \return std::string - Der ermittelte Monat als std::string.
     * \endcond
     *
     * \cond english
     * \brief  Return the month of the current year, that was determined
     *         at the constructing and calling class constructor.
     *
     * \return std::string - The current month as std::string.
     * \endcond
     *
     * \see getYear()
     * \see getDayNow()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getMonth() const {
        std::stringstream sd, st;
        ss  << std::setw(2)
            << std::setfill('0')
            << month;
        return ss.str();
    }
    
    /**
     * \cond german
     * \brief  Gibt den Tag des aktuellen Monats zurück, der während
     *         der initializierung des Konstruktors ermittelt wurde.
     *
     * \return std::string - Der ermittelte Tag des Monats als std::string.
     * \endcond
     *
     * \cond english
     * \brief  Return the current day of month, that was determined
     *         at the constructing and calling class constructor.
     *
     * \return std::string - The current year as std::string.
     * \endcond
     *
     * \see getYearNow()
     * \see getMonthNow()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getDay() const {
        std::stringstream sd, st;
        ss  << std::setw(2)
            << std::setfill('0')
            << day;
        return ss.str();
    }
    
    /**
     * \cond german
     * \brief  Gibt den aktuellen Tag der bei aufruf der Funktion gemessen wurde.
     *
     * \return std::string  -  Das aktuelle Jahr, gemessen im "Jetzt"
     * \endcond
     *
     * \cond english
     * \brief  Return the current day at the point from "now" by calling
     *         this Function.
     * \return std::string - The current day as std::string from "now".
     * \endcond
     *
     * \see getYear()
     * \see getMonth()
     * \see getDay()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getDayNow() const {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        day   = localTime.tm_mday;
        std::stringstream ss; ss << day;

        return ss.str();
    }
    
    /**
     * \cond german
     * \brief   Gibt den aktuellen Tag plus den im Parameter angebenen "delta"-Tag
     *          zurück, der beim aufrufen der Funktion gemessen wurde.
     *
     * Gibt den aktuellen Tages-Wert plus dem mit den im Parameter angegebenen "delta" Tages-Wert
     * als std::string zurück, der bei aufruf der Funktion gemessen wurde.
     * Es handelt sich hierbei um die lokale Server-Zeit.
     *
     * \return  std::string  -  Der aktuelle Tag + delta, gemessen im "Jetzt"
     * \endcond
     *
     * \cond english
     * \brief  Return the current day at the point from "now" by calling
     *         this Function.
     * \return std::string - The current day as std::string from "now".
     * \endcond
     *
     * \see getYear()
     * \see getMonth()
     * \see getDay()
     *
     * \since  \a_currentVersion
     * \author \a_currentAuthors
     */
    std::string getDayNow(uint16_t delta) const {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        day   = localTime.tm_mday + delta;
        std::stringstream ss; ss << day;

        return ss.str();
    }
};

/**
 * \class  Time
 * \cond german
 * \brief  Informationen für die Klasse Date, die verschiedene Funktionen
 *         zur Bearbeitung von Zeit-Werte bereitstellt.
 * \endcond
 *
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
class Time {
private:
    int hour   ;
    int minute ;
    int second ;
public:
    Time() {
        auto now = std::chrono::system_clock::now();  // current time
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        
        // -----------------------
        // Lokale Zeit darstellen
        // -----------------------
        std::tm localTime = *std::localtime(&time);
        
        // -----------------------------------
        // Zeit aus dem tm-Objekt extrahieren
        // -----------------------------------
        hour   = localTime.tm_hour;
        minute = localTime.tm_min;
        second = localTime.tm_sec;
    }
    
    std::string getHour() const {
        std::stringstream sd, st;
        ss  << std::setw(2)
            << std::setfill('0')
            << hour;
        return ss.str();
    }

    std::string getMinute() const {
        std::stringstream sd, st;
        ss  << std::setw(2)
            << std::setfill('0')
            << minute;
        return ss.str();
    }

    std::string getSecond() const {
        std::stringstream sd, st;
        ss  << std::setw(2)
            << std::setfill('0')
            << second;
        return ss.str();
    }
};

/**
 * \cond english
 * \brief  Each request, and response send/recieve a header + body.
 *
 * \param[in] uint32_t bcode   -  The code for the header
 * \param[in] uint32_t btype   -  The type for the header
 * \param[in] uint32_t length  -  The length for the body
 *
 * \return std::string  -  The combined header string
 * \endcond
 *
 * \cond german
 * \brief  Jede Anfrage und jede Antwort sendet/empfängt einen Header
 *         und einen Body.
 *
 * Im Header stehen informelle Daten über den Body der Nachricht, während
 * im Body die eigentlichen Daten der Nachricht gesendet bzw. empfangen
 * werden.
 *
 * \param[in] uint32_t bcode   -  Der Code für den Header
 * \param[in] uint32_t btype   -  Der Typ für den Header
 * \param[in] uint32_t length  -  Die Länge der Daten
 * \endcond
 *
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
std::string responseHeader(
    uint32_t bcode,
    uint32_t btype,
    uint32_t length) {
    auto * datum = Date();
    std::stringstream hdr;
    hdr << "VERSION 1"          << std::endl
        << "DATE "   << datum->getDate() << std::endl
        << "TIME "   << datum->getTime() << std::endl
        << "CODE "   << bcode   << std::endl
        << "TYPE "   << btype   << std::endl
        << "LENGTH " << length  << std::endl;

    delete datum;
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

/**
 * \class  Server
 * \cond german
 * \brief  Informationen für die Klasse Server, die verschiedene Funktionen
 *         zur Bereitstellung von serverbasierten Funktionen bereitstellt.
 * \endcond
 *
 * \cond english
 * \brief  The Server class for various server based functions.
 * \endcond
 *
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
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

/**
 * \cond german
 * \brief  Diese Funkion wird verwendet, wenn "exit()" oder eine
 *         Ausnahme (Exception), die EXIT_FAILURE zurückliefert
 *         aufgerufen.
 *
 * \param  keine
 * \endcond
 *
 * \cond english
 * \brief  This function will be called when the Application throw
 *         an Exception, and EXIT_FAILURE is returned. Or when the
 *         "exit()" Function is called.
 *
 * \param  nothing
 * \endcond
 *
 * \return void
 * \since  \a_currentVersion
 * \author \a_currentAuthors
 */
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
