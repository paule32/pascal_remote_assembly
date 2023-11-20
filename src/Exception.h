// ------------------------------------------------------------------
// File:   Exception.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// ------------------------------------------------------------------
# pragma once

# include <iostream>
# include <exception>

// ------------------------------------------------------------------
// exception class, to reduce use size of code - instead conditional
// spagetty code ...
// ------------------------------------------------------------------
# define CreatePascalException(name)                                \
class EPascalException_ ## name: public std::exception {            \
public:EPascalException_ ## name (const char* message) :            \
errorMessage(message) {} virtual const char* what() const throw() { \
return errorMessage.c_str(); } private: std::string errorMessage; }
// ------------------------------------------------------------------
CreatePascalException (Pascal);
CreatePascalException (Argument);
CreatePascalException (FileNotFound);
CreatePascalException (FileNotOpen);

CreatePascalException (NoErrorExcpetion);
