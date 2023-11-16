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

/*
throw boost::enable_error_info(std::runtime_error("Beispiel mit errinfo_at_line"))
      << boost::throw_function("main")
      << boost::throw_file("example.cpp")
      << boost::throw_line(42);
*/