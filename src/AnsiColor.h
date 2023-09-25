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
    static struct Normal {
        std::string black  () const { return "\x1B[0;30m"; }
        std::string red    () const { return "\x1B[0;31m"; }
        std::string green  () const { return "\x1B[0;32m"; }
        std::string yellow () const { return "\x1B[0;33m"; }
        std::string blue   () const { return "\x1B[0;34m"; }
        std::string purple () const { return "\x1B[0;35m"; }
        std::string cyan   () const { return "\x1B[0;36m"; }
        std::string white  () const { return "\x1B[0;37m"; }
    } Normal;
    // -----------------------------------------
    // bold colors ...
    // -----------------------------------------
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