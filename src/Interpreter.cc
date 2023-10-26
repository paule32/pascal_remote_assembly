// -----------------------------------------------------------------
// File:   build.sh
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "error: file.o binary needed." << std::endl;
        return EXIT_FAILURE;
    }
    
    try {
        std::fstream fh;
        fh.open(argv[1], std::fstream::in | std::fstream::binary);
        
        if (!fh.is_open()) {
            std::cout << "error: file '" << argv[1]
                      << "' file is not open."
                      << std::endl;
            return EXIT_FAILURE;
        }
        if (fh.fail()) {
            std::cout << "error: file '" << argv[1]
                      << "' could not be open."
                      << std::endl;
            return EXIT_FAILURE;
        }
        
        IMAGE_FILE_HEADER hdr;
        fh.read((char*)&hdr, sizeof(IMAGE_FILE_HEADER));
        
        // 32-bit
        if (hdr.Machine == 0x014c) {
            std::cout << "machine: Intel/AMD x86 - 32 bit" << std::endl;
        }   else
            
        // 64-bit
        if (hdr.Machine == 0x8664) {
            std::cout << "machine: Intel/AMD x64 - 64 bit" << std::endl;
        }   else
        
        // Intel Itanium
        if (hdr.Machine == 0x0200) {
            std::cout << "machine: Intel Itanium" << std::endl;
        }   else {
            std::stringstream ss;
            ss << "machine: could not determine." << std::endl;
            throw ss.str();
        }
        
        fh.close();
    }
    catch (std::exception &e) {
        std::cerr << "error: " << e.what()
                  << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
