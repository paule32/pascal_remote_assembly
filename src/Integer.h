// -----------------------------------------------------------------
// File:   Integer.h
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
#pragma once

# include <iostream>

template <typename T> class Integer {
public:
    Integer(T t);
};

template <typename T> Integer<T>::Integer(T t) {
    std::cout << "temol" << std::endl;
}
