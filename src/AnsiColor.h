// -----------------------------------------------------------------
// File:   AnsiColor.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#pragma once

# include <iostream>
# include <string>

class AnsiColor {
public:
    // -----------------------------------------
    // regular colors ...
    // -----------------------------------------
    /// \~German
    /// \brief Setzt die Vordergrund-Farbe für die Text-Ausgabe.
    ///
    /// \~English
    /// \brief Set Foreground Color Flag for Text Output Style.
    static struct Normal {
        /// \~German Farbe: schwarz \~English Color: black <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string black  () const { return "\x1B[0;30m"; }
        
        /// \~German Farbe: rot     \~English Color: red <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string red    () const { return "\x1B[0;31m"; }
        
        /// \~German Farbe: grün    \~English Color: green <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string green  () const { return "\x1B[0;32m"; }
        
        /// \~German Farbe: gelb    \~English Color: yellow <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string yellow () const { return "\x1B[0;33m"; }

        /// \~German Farbe: blau    \~English Color: blue <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string blue   () const { return "\x1B[0;34m"; }
        
        /// \~German Farbe: violett \~English Color: purple <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string purple () const { return "\x1B[0;35m"; }
        
        /// \~German Farbe: türkis  \~English Color: cyan <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string cyan   () const { return "\x1B[0;36m"; }
        
        /// \~German Farbe: weis    \~English Color: white <tt>  -  ANSI-Escape:  \x1B[0;30m</tt>
        std::string white  () const { return "\x1B[0;37m"; }
    } Normal;
    // -----------------------------------------
    // bold colors ...
    // -----------------------------------------
    /// \~German
    /// \brief Setzt die Farbe für Text-Fett-Druck-Ausgabe.
    ///
    /// \~English
    /// \brief Set bold Color Flag for Text Output Style.
    static struct Bold {
        std::string black  () const { return "\x1B[1;30m"; }
        std::string red    () const { return "\x1B[1;31m"; }
        std::string green  () const { return "\x1B[1;32m"; }
        std::string yellow () const { return "\x1B[1;33m"; }
        std::string blue   () const { return "\x1B[1;34m"; }
        std::string purple () const { return "\x1B[1;35m"; }
        std::string cyan   () const { return "\x1B[1;36m"; }
        std::string white  () const { return "\x1B[1;37m"; }
    } Bold;
    // -----------------------------------------
    // underline ...
    // -----------------------------------------
    /// \~German
    /// \brief Setzt die Farbe für unterstrichende Text-Ausgaben.
    ///
    /// \~English
    /// \brief Set underline Color Flag for Text Output Style.
    static struct UnderLine {
        std::string black  () const { return "\x1B[4;30m"; }
        std::string red    () const { return "\x1B[4;31m"; }
        std::string green  () const { return "\x1B[4;32m"; }
        std::string yellow () const { return "\x1B[4;33m"; }
        std::string blue   () const { return "\x1B[4;34m"; }
        std::string purple () const { return "\x1B[4;35m"; }
        std::string cyan   () const { return "\x1B[4;36m"; }
        std::string white  () const { return "\x1B[4;37m"; }
    } Underline;
    // -----------------------------------------
    // background colors ...
    // -----------------------------------------
    /// \~German
    /// \brief Setzt die Hintergrund-Farbe für die Text-Ausgabe.
    ///
    /// \~English
    /// \brief Set Background Color Flag for Text Output Style.
    static struct Background {
        std::string black  () const { return "\x1B[40m"; }
        std::string red    () const { return "\x1B[41m"; }
        std::string green  () const { return "\x1B[42m"; }
        std::string yellow () const { return "\x1B[43m"; }
        std::string blue   () const { return "\x1B[44m"; }
        std::string purple () const { return "\x1B[45m"; }
        std::string cyan   () const { return "\x1B[46m"; }
        std::string white  () const { return "\x1B[47m"; }
    } Background;
    // -----------------------------------------
    // high intensty colors ...
    // -----------------------------------------
    static struct High {
        std::string black  () const { return "\x1B[0;90m"; }
        std::string red    () const { return "\x1B[0;91m"; }
        std::string green  () const { return "\x1B[0;92m"; }
        std::string yellow () const { return "\x1B[0;93m"; }
        std::string blue   () const { return "\x1B[0;94m"; }
        std::string purple () const { return "\x1B[0;95m"; }
        std::string cyan   () const { return "\x1B[0;96m"; }
        std::string white  () const { return "\x1B[0;97m"; }
    } High;
    // -----------------------------------------
    // bold high intensty colors ...
    // -----------------------------------------
    static struct BoldHigh {
        std::string black  () const { return "\x1B[1;90m"; }
        std::string red    () const { return "\x1B[1;91m"; }
        std::string green  () const { return "\x1B[1;92m"; }
        std::string yellow () const { return "\x1B[1;93m"; }
        std::string blue   () const { return "\x1B[1;94m"; }
        std::string purple () const { return "\x1B[1;95m"; }
        std::string cyan   () const { return "\x1B[1;96m"; }
        std::string white  () const { return "\x1B[1;97m"; }
    } BoldHigh;
    // -----------------------------------------
    // high intensty background colors ...
    // -----------------------------------------
    static struct HighBackground {
        std::string black  () const { return "\x1B[0;100m"; }
        std::string red    () const { return "\x1B[0;101m"; }
        std::string green  () const { return "\x1B[0;102m"; }
        std::string yellow () const { return "\x1B[0;103m"; }
        std::string blue   () const { return "\x1B[0;104m"; }
        std::string purple () const { return "\x1B[0;105m"; }
        std::string cyan   () const { return "\x1B[0;106m"; }
        std::string white  () const { return "\x1B[0;107m"; }
    } HighBackground;
};
// -----------------------------------------------------------------
extern AnsiColor * ansi;