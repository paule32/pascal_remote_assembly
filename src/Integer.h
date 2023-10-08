// -----------------------------------------------------------------
// File:   Integer.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#pragma once

# include <iostream>
# include <vector>
# include <any>
# include <memory>
# include <cxxabi.h>

template <typename T> class Integer {
public:
    Integer(T t);
};

template <typename T> Integer<T>::Integer(T t) {
    std::cout << "temol" << std::endl;
}

// -----------------------------------------------------------------
// demangles functions that are encoded with gnu cxx abi ...
// -----------------------------------------------------------------
auto cppDemangle(const std::string abiName)
{
    int status;    
    char *ret = abi::__cxa_demangle(abiName.c_str(), 0, 0, &status);
    
    auto deallocator = ( [](char *mem) { if (mem) free((void*)mem); } );
    
    if (status) {
        // ----------------------------------------------------------------------
        //  0: The demangling operation succeeded.
        // -1: A memory allocation failure occurred.
        // -2: mangled_name is not a valid name under the C++ ABI mangling rules.
        // -3: One of the arguments is invalid.
        // ----------------------------------------------------------------------
        std::unique_ptr<char, decltype(deallocator) > retval(nullptr, deallocator);
        return retval;
    }
    
    // --------------------------------------------------------------------------
    // Create a unique pointer to take ownership of the returned string so it
    // is freed when that pointers goes out of scope
    // --------------------------------------------------------------------------
    std::unique_ptr<char, decltype(deallocator) > retval(ret, deallocator);
    return retval;
}

std::vector< std::any    > ParamsValue;
std::vector< std::string > ParamsType;

void gget() {
    for (int i = 0; i < ParamsValue.size(); ++i) {
        std::cout << "arg: " << (i+1)   << " = " ;
        std::cout << ParamsType.at(i)   << " = " <<
        cppDemangle( ParamsType.at(i) ) << std::endl;
    }
}

template <typename... Args> void getArgsValue(Args && ... arg) {
    int i = 0;

    ParamsValue.clear();
    ParamsType .clear();

    ([&] {
        ++i;
        ParamsValue.push_back( arg );
        ParamsType .push_back( std::any( arg ).type().name() );
        std::cout << "arg: " << i << " = " << arg << std::endl;
    } (), ...);
}

template <typename ...Args> void f(const Args&... args) {
    constexpr auto size = sizeof ...(Args);
    std::cout << "Count: " << size << std::endl;

    std::cout << std::endl; getArgsValue(args...);
    std::cout << std::endl; gget();
}
