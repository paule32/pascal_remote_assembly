// -----------------------------------------------------------------
// File:   Exception.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# pragma once

# include <iostream>
# include <exception>

// -----------------------------------------------------------------
// exception class, to reduce use size of code - instead conditional
// spagetty code ...
// -----------------------------------------------------------------
class EPascalException: public std::exception
{
public:
    EPascalException(const char* message) : errorMessage(message) {}
    virtual const char* what() const throw() {
        return errorMessage.c_str();
    }
private:
    std::string errorMessage;
};

class EPascalException_Argument: public std::exception
{
public:
    EPascalException_Argument(const char* message) : errorMessage(message) {}
    virtual const char* what() const throw() {
        return errorMessage.c_str();
    }
private:
    std::string errorMessage;
};

class EPascalException_FileNotFound: public std::exception
{
public:
    EPascalException_FileNotFound(const char* message) : errorMessage(message) {}
    virtual const char* what() const throw() {
        return errorMessage.c_str();
    }
private:
    std::string errorMessage;
};
