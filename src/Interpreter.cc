// -----------------------------------------------------------------
// File:   build.sh
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include "Parser.h"

namespace std {
    template <typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits> &
        tab(basic_ostream<_CharT, _Traits> &__os) {
        return __os.put(__os.widen('\t'));
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "error: file.o binary needed." << std::endl;
        return EXIT_FAILURE;
    }
    
    try {
        // ----------------------------
        // open file for input/read
        // ----------------------------
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
        
        // ----------------------------
        // read COFF header:
        // ----------------------------
        IMAGE_FILE_HEADER hdr;
        fh.read((char*)&hdr, sizeof(IMAGE_FILE_HEADER));
        
        std::cout << "File Image Header:" << std::endl
                  << "------------------" << std::endl;
        std::cout << "machine              : ";
        
        // ----------------------------
        // 32-bit
        // ----------------------------
        if (hdr.Machine == IMAGE_FILE_MACHINE_I386) {
            std::cout << "Intel/AMD x86 - 32 bit" << std::endl;
        }   else
            
        // ----------------------------
        // 64-bit
        // ----------------------------
        if (hdr.Machine == IMAGE_FILE_MACHINE_IA64) {
            std::cout << "Intel/AMD x64 - 64 bit" << std::endl;
        }   else
        
        // ----------------------------
        // Intel Itanium
        // ----------------------------
        if (hdr.Machine == IMAGE_FILE_MACHINE_AMD64) {
            std::cout << "Intel Itanium" << std::endl;
        }   else {
            std::stringstream ss;
            ss << "machine: could not determine." << std::endl;
            throw ss.str();
        }
        
        // ----------------------------
        // Windows limit sections to 96
        // ----------------------------
        if ((hdr.NumberOfSections > 0) && (hdr.NumberOfSections < 96)) {
            std::cout << "NumberOfSections     : 0x" << hdr.NumberOfSections << std::endl;
        }   else {
            std::stringstream ss;
            ss << "NumberOfSecions >= 96." << std::endl;
            throw ss.str();
        }
        
        // ----------------------------
        // time/date stamp:
        // ----------------------------
        std::time_t datime = hdr.TimeDateStamp;
        std::string satime(std::ctime(&datime));
        std::cout << "Time / Date          : "
                  << satime
                  << std::endl;
                  
        // ----------------------------
        // symbol table pointer:
        // ----------------------------
        DWORD PointerToSymbolTable = 0;
        if (!(PointerToSymbolTable = hdr.PointerToSymbolTable)) {
            std::stringstream ss;
            ss << "no symbol table found.";
            throw ss.str();
        }
        std::cout << "PtrToSymTable (hex)  : " << std::hex
                  << hdr.PointerToSymbolTable  << std::dec << std::endl
                  << "PtrToSymTable (dec)  : "
                  << hdr.PointerToSymbolTable
                  << std::endl
                  << std::endl;
        
        // ----------------------------
        // symbols found:
        // ----------------------------
        DWORD NumberOfSymbols = 0;
        if (!(NumberOfSymbols = hdr.NumberOfSymbols)) {
            std::stringstream ss;
            ss << "no symbols found.";
            throw ss.str();
        }
        std::cout << "Number of Symbols    : "
                  << NumberOfSymbols
                  << std::endl
                  << std::endl
                  << std::endl;
        
        // ----------------------------
        // optional header:
        // ----------------------------
        WORD SizeOfOptionalHeader = hdr.SizeOfOptionalHeader;
        std::cout << "Optional Header Size : "
                  << SizeOfOptionalHeader
                  << std::endl;
        
        // ----------------------------
        // characteristics...
        // ----------------------------
        WORD Characteristics = hdr.Characteristics;
        
        std::cout << "Characterisics       : " << Characteristics << std::endl;
        
        // ---------------------------------------------------------
        // Relocation information was stripped from the file.
        // The file must be loaded at its preferred base address.
        // If the base address is not available, the loader reports
        // an error ...
        // ---------------------------------------------------------
        if (Characteristics & IMAGE_FILE_RELOCS_STRIPPED) {
            std::cout << std::tab << "IMAGE_FILE_RELOCS_STRIPPED" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
            std::cout << std::tab << "IMAGE_FILE_EXECUTABLE_IMAGE" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED) {
            std::cout << std::tab << "IMAGE_FILE_LINE_NUMS_STRIPPED" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED) {
            std::cout << std::tab << "IMAGE_FILE_LOCAL_SYMS_STRIPPED" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_AGGRESIVE_WS_TRIM) {
            std::cout << std::tab << "IMAGE_FILE_AGGRESIVE_WS_TRIM" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE) {
            std::cout << std::tab << "IMAGE_FILE_LARGE_ADDRESS_AWARE" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_BYTES_REVERSED_LO) {
            std::cout << std::tab << "IMAGE_FILE_BYTES_REVERSED_LO" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_32BIT_MACHINE) {
            std::cout << std::tab << "IMAGE_FILE_32BIT_MACHINE" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_DEBUG_STRIPPED) {
            std::cout << std::tab << "IMAGE_FILE_DEBUG_STRIPPED" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) {
            std::cout << std::tab << "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP) {
            std::cout << std::tab << "IMAGE_FILE_NET_RUN_FROM_SWAP" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_SYSTEM) {
            std::cout << std::tab << "IMAGE_FILE_SYSTEM" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_DLL) {
            std::cout << std::tab << "IMAGE_FILE_DLL" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY) {
            std::cout << std::tab << "IMAGE_FILE_UP_SYSTEM_ONLY" <<
            std::endl ;
        }
        if (Characteristics & IMAGE_FILE_BYTES_REVERSED_HI) {
            std::cout << std::tab << "IMAGE_FILE_BYTES_REVERSED_HI" <<
            std::endl ;
        }   std::cout << std::endl;
        
        
        // TODO: optional header check
        
        // ----------------------------
        // read section header:
        // ----------------------------
        std::cout << "Optional Header:" << std::endl
                  << "----------------" << std::endl;

        IMAGE_SECTION_HEADER sechdr;
        fh.read((char*)&sechdr, sizeof(IMAGE_SECTION_HEADER));

        // -----------------------------------
        // check, if we can find code section:
        // -----------------------------------
        if (strcmp((const char*)sechdr.Name,".text") == 0) {
            if (sechdr.Characteristics & IMAGE_SCN_CNT_CODE) {
                std::cout << "Code Section         : "
                          << sechdr.Name
                          << "  contain executable code"
                          << std::endl;
            }   else {
                std::cout << "Code Section         : "
                          << sechdr.Name
                          << std::endl;
            }
        }   else {
            std::stringstream ss;
            ss << "can not get code section.";
            throw ss.str();
        }
        
        // ----------------------------
        // address of first byte
        // ----------------------------
        std::cout << "VirtualAddress       : "
                  << sechdr.VirtualAddress
                  << std::endl;
                  
        std::cout << "SizeOfRawData (hex)  : 0x" << std::hex << sechdr.SizeOfRawData << std::endl
                  << "SizeOfRawData (dec)  :   " << std::dec << sechdr.SizeOfRawData << std::endl;
        
        std::cout << "PtrToRawData (hex)   : 0x" << std::hex << sechdr.PointerToRawData << std::endl
                  << "PtrToRawData (dec)   :   " << std::dec << sechdr.PointerToRawData << std::endl;
                  
        std::cout << "PtrToRelocations     : "
                  << sechdr.PointerToRelocations
                  << std::endl;
                  
        std::cout << "PtrToLineNumbers     : "
                  << sechdr.PointerToLinenumbers
                  << std::endl;
                  
        std::cout << "NumberOfRelocations  : "
                  << sechdr.NumberOfRelocations
                  << std::endl;
                  
        std::cout << "NumberOfLineNumbers  : "
                  << sechdr.NumberOfLinenumbers
                  << std::endl;
        
        std::cout << "Characteristics (hex): 0x" << std::hex << sechdr.Characteristics << std::endl
                  << "Characteristics (dec):   " << std::dec << sechdr.Characteristics << std::endl;
        
        if (sechdr.Characteristics & IMAGE_SCN_TYPE_NO_PAD) {
            std::cout << std::tab << "IMAGE_SCN_TYPE_NO_PAD"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_CNT_CODE) {
            std::cout << std::tab << "IMAGE_SCN_CNT_CODE"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA) {
            std::cout << std::tab << "IMAGE_SCN_CNT_INITIALIZED_DATA"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA) {
            std::cout << std::tab << "IMAGE_SCN_CNT_UNINITIALIZED_DATA"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_LNK_OTHER) {
            std::cout << std::tab << "IMAGE_SCN_LNK_OTHER"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_LNK_INFO) {
            std::cout << std::tab << "IMAGE_SCN_LNK_INFO"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_LNK_REMOVE) {
            std::cout << std::tab << "IMAGE_SCN_LNK_REMOVE"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_LNK_COMDAT) {
            std::cout << std::tab << "IMAGE_SCN_LNK_COMDAT"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_NO_DEFER_SPEC_EXC) {
            std::cout << std::tab << "IMAGE_SCN_NO_DEFER_SPEC_EXC"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_GPREL) {
            std::cout << std::tab << "IMAGE_SCN_GPREL"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_PURGEABLE) {
            std::cout << std::tab << "IMAGE_SCN_MEM_PURGEABLE"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_LOCKED) {
            std::cout << std::tab << "IMAGE_SCN_MEM_LOCKED"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_PRELOAD) {
            std::cout << std::tab << "IMAGE_SCN_MEM_PRELOAD"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_1BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_1BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_2BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_2BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_4BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_4BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_8BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_8BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_16BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_16BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_32BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_32BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_64BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_64BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_128BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_128BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_256BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_256BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_512BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_512BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_1024BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_1024BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_2048BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_2048BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_4096BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_4096BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_ALIGN_8192BYTES) {
            std::cout << std::tab << "IMAGE_SCN_ALIGN_8192BYTES"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_LNK_NRELOC_OVFL) {
            std::cout << std::tab << "IMAGE_SCN_LNK_NRELOC_OVFL"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_DISCARDABLE) {
            std::cout << std::tab << "IMAGE_SCN_MEM_DISCARDABLE"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_NOT_CACHED) {
            std::cout << std::tab << "IMAGE_SCN_MEM_NOT_CACHED"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_NOT_PAGED) {
            std::cout << std::tab << "IMAGE_SCN_MEM_NOT_PAGED"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_SHARED) {
            std::cout << std::tab << "IMAGE_SCN_MEM_SHARED"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_EXECUTE) {
            std::cout << std::tab << "IMAGE_SCN_MEM_EXECUTE"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_READ) {
            std::cout << std::tab << "IMAGE_SCN_MEM_READ"
                      << std::endl;
        }
        if (sechdr.Characteristics & IMAGE_SCN_MEM_WRITE) {
            std::cout << std::tab << "IMAGE_SCN_MEM_WRITE"
                      << std::endl;
        }
        
//        std::cout << "Flags                : "
//                  << sechdr.f
        fh.close();
    }
    // ----------------------------
    // we use try catch for errors:
    // ----------------------------
    catch (std::exception &e) {
        std::cerr << "error: " << e.what()
                  << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
