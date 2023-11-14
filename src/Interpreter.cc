// -----------------------------------------------------------------
// File:   Parser.cc
// Author: (c) 2023 Jens Kallup - paule32
// All rights reserved
//
// only for education, and non-profit usage !
// -----------------------------------------------------------------
# include <boost/program_options.hpp>
# include <zlib.h>
# include <functional>      // std::function
# include "Parser.h"

// -----------------------------------------------------------------
// global variable's / constant's ...
// -----------------------------------------------------------------
AsmParser    * asm_parser ;

std::map < std::string, asmjit::Label > app_Labels;

std::string file_input_asm;         // input assembly file
std::string file_input_obj;         // input coff object file

std::string file_output_cm;         // output main       C++ file
std::string file_output_ch;         // output header     C++ file
std::string file_output_ct;         // output misc/tools C++ file

// -----------------------------------------------------------------
// parser stuff ...
// -----------------------------------------------------------------
extern void asm_parser_main(void);
extern "C"  int yyparse(void);
extern "C"  FILE * yyin;
extern      int  TurboMain(void);   // console TUI - Turbo Vision

static bool found_args = false;     // program command line arguments

using namespace boost::program_options;

// -----------------------------------------------------------------
// application stuff (name, locale ...
// -----------------------------------------------------------------
static std::string ApplicationName( ASMJIT_APPNAME ); // -Define

static std::string de_DE("de_DE");  // german
static std::string en_US("en_US");  // english us

std::string locale_str;             // locales en = English, de = German

std::string locale_codepage_old;    // ANSI or OEM
std::string locale_codepage_new;    //

LCID locale_LCID_old;               // for restore the old locale
LCID locale_LCID_new;               //

// -----------------------------------------------------------------
// extend the namespace STD with "tab" - to produce \t into stream:
// -----------------------------------------------------------------
namespace std {
    template <typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits> &
        tab(basic_ostream<_CharT, _Traits> &__os) {
        return __os.put(__os.widen('\t'));
    }
}

// -----------------------------------------------------------------
// decompress gzip file...
// -----------------------------------------------------------------
int decompressGzipFile(
    const char* inputFileName,
    const char* outputFileName) {

    gzFile file = gzopen(inputFileName, "rb");
    if (file == NULL) {
        perror("Error at open input file.");
        return EXIT_FAILURE;
    }
    
    FILE * outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        perror("Error at open output file.");
        gzclose(file);
        return EXIT_FAILURE;
    }
    
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = gzread(file, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }
    
    gzclose(file);
    fclose(outputFile);
    
    return EXIT_SUCCESS;
}

// -----------------------------------------------------------------
// If the dot is at the beginning of the file name, do not treat
// it as a file extension.
// e.g., a hidden file:  ".alpha".
//
// This test also incidentally avoids a dot that is really a
// current directory indicator.
// e.g.:  "alpha/./bravo"
// -----------------------------------------------------------------
std::string
ExtractFileExtension( std::string const & path )
{
    std::string ext;

    // --------------------------
    // Find the last dot, if any.
    // --------------------------
    size_t dotIdx = path.find_last_of( "." );
    
    if ( dotIdx != std::string::npos )
    {
        // Find the last directory separator, if any.
        size_t dirSepIdx = path.find_last_of( "/\\" );
        if ( dotIdx > dirSepIdx + 1 )  {
            ext = path.substr( dotIdx );
        }
    }

    return ext;
}

// -----------------------------------------------------------
// Retrieve the system error message for the last-error code
// -----------------------------------------------------------
void ErrorExit(LPTSTR lpszFunction) 
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

// ----------------------------------------------
// Get the system codepage ...
// ----------------------------------------------
int handle_codepage()
{
    WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
    int result = GetUserDefaultLocaleName(
    localeName,
    LOCALE_NAME_MAX_LENGTH);

    // ----------------------------------------------
    // Get the ANSI code page for the current locale
    // ----------------------------------------------
    if (result > 0) {
        int ansiCodePage = GetLocaleInfoEx(
            localeName,
            LOCALE_IDEFAULTANSICODEPAGE,
            NULL,
            0);
        if (ansiCodePage > 0) {std::cout << "ansi" << std::endl;
            wchar_t* ansiCodePageBuffer = new wchar_t[ansiCodePage];
            GetLocaleInfoEx(
            localeName,
            LOCALE_IDEFAULTANSICODEPAGE,
            ansiCodePageBuffer,
            ansiCodePage);
            
            std::wstringstream wss;
            wss << "ansi: " << ansiCodePageBuffer;
            
            std::stringstream ss;
            std::wstring wideStr = wss.str();
            
            std::wstring_convert< std::codecvt_utf8< wchar_t >> converter;
            locale_codepage_new = converter.to_bytes(wideStr);
            
            delete [] ansiCodePageBuffer;
            
            return ansiCodePage;
        }

        // ---------------------------------------------
        // Get the OEM code page for the current locale
        // ---------------------------------------------
        int oemCodePage = GetLocaleInfoEx(
            localeName,
            LOCALE_IDEFAULTCODEPAGE,
            NULL,
            0);
        if (oemCodePage > 0) {std::cout << "OEM" << std::endl;
            wchar_t* oemCodePageBuffer = new wchar_t[oemCodePage];
            GetLocaleInfoEx(
            localeName,
            LOCALE_IDEFAULTCODEPAGE,
            oemCodePageBuffer,
            oemCodePage);
            
            std::wstringstream wss;
            wss << "oem: " << oemCodePageBuffer;
            
            std::stringstream ss;
            std::wstring wideStr = wss.str();
            
            std::wstring_convert< std::codecvt_utf8< wchar_t >> converter;
            locale_codepage_new = converter.to_bytes(wideStr);
            
            delete [] oemCodePageBuffer;
            
            return oemCodePage;
        }
    }
    else {
        std::cerr << "error: can not get codepage." <<
        std::endl;
    }
    return 0;
}

// ---------------------------------------------------------
// check file ...
// ---------------------------------------------------------
int check_file(
    std::string filename,
    std::function<int(void)> stat_func,
    std::function<int(void)> callback_ok)
{
    struct stat attr;
    
    // ---------------------------
    // if file exists ?
    // ---------------------------
    if (stat(filename.c_str(), &attr) == -1) {
        if (stat_func == nullptr) {
            std::cerr << "invalid: stat_func."
                      << std::endl;
            return EXIT_FAILURE;
        }
        else {
            stat_func();
            return EXIT_FAILURE;
        }
    }
    // ---------------------------
    // regular file
    // ---------------------------
    if (attr.st_mode & S_IFREG) {
        if (callback_ok == nullptr) {
            locale_str = en_US;
            std::cerr << "callback_ok(): failed,"
                      << std::endl;
            return EXIT_FAILURE;
        }
        else {
            callback_ok();
            return EXIT_SUCCESS;
        }
    }   else
    // ---------------------------
    // device file
    // ---------------------------
    if (attr.st_mode & S_IFCHR) {
        locale_str = en_US;
        std::cerr << filename << ": file is a devide."
                  << std::endl ;
        return EXIT_FAILURE;
    }   else
    // ---------------------------
    // file is a directory
    // ---------------------------
    if (attr.st_mode & S_IFDIR) {
        locale_str = en_US;
        std::cerr << filename << ": file is a directory."
                  << std::endl ;
        return EXIT_FAILURE;
    }
    // ---------------------------
    // unknown file
    // ---------------------------
    else {
        locale_str = en_US;
        std::cerr << filename << ": file format unknown."
                  << std::endl ;
        return EXIT_FAILURE;
    }   return EXIT_FAILURE;
}

// ---------------------------------------------------------
// get gzip'ed locale file, and dezip it ...
// ---------------------------------------------------------
int getLocaleSystemUTF8(std::string ls)
{
    std::string loca("localization error: ");
    std::stringstream ss1, ss2;
    
    ss1 << ".\\locale\\" << ls << ".utf8\\LC_MESSAGES\\" << ApplicationName << ".mo.gz";
    ss2 << ".\\locale\\" << ls << ".utf8\\LC_MESSAGES\\" << ApplicationName << ".mo";
        
    locale_str = ls;
    
    return check_file(ss1.str(),
        [&ls, &ss1]() -> int {
            std::cerr
                << "error: " << ss1.str()
                << ": file does not exists."
                << std::endl;
            return EXIT_FAILURE;
        },
        [&ls, &ss1, &ss2]() -> int {
                std::cout << ss1.str() << std::endl;
            int result = decompressGzipFile(
                ss1.str().c_str(),
                ss2.str().c_str());
            if (result == EXIT_FAILURE) {
                return EXIT_FAILURE;
            }
            else {
                setlocale( LC_ALL, "de_DE.utf-8" );
                
                bind_textdomain_codeset(ApplicationName.c_str(), "UTF-8");
                bindtextdomain( ApplicationName.c_str(),".\\locale");
                textdomain    ( ApplicationName.c_str() );
            
                std::wcout.imbue(std::locale());
                std::cout << gettext("File") << std::endl;
                
                HWND hwnd       = GetForegroundWindow();
                int  textLength = GetWindowTextLengthA(hwnd);
                
                if (hwnd) {                    
                    if (textLength < 1) {
                        std::cout << "error: can not get windows title." <<
                        std::endl ;
                        return EXIT_FAILURE;
                    }
                    
                    size_t sizeToAllocate  = 256;
                    LPVOID allocatedMemory = (PSTR) VirtualAlloc(NULL, sizeToAllocate,
                    MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
                        
                    if (!allocatedMemory) {
                        std::cerr << "error: could not allocate memory to get window title."
                                  << std::endl;
                        return EXIT_FAILURE;
                    }
                        
                    // --------------------------------
                    // GetWindowText needs TCHAR buffer
                    // --------------------------------
                    TCHAR windowText[ 256 ];
                    
                    textLength = GetWindowText(hwnd, windowText,
                    sizeof(windowText) / sizeof(windowText[0]));
                    
                    if (textLength > 0) {
                        size_t copyLength = (textLength + 1) * sizeof(TCHAR);
                        
                        std::cout << "len: " << textLength << std::endl;
                        std::cout << "cpy: " << copyLength << std::endl;
                        if (copyLength <= sizeToAllocate) {
                            memcpy(allocatedMemory, windowText, copyLength);
                            std::cout << "window ok: " << windowText <<
                            std::endl ;
                            
                            std::string wintxt = std::string(windowText, copyLength);
                            if (wintxt.find("MSYS32") != std::string::npos) {
                                std::cout << "Programm wurde in MSYS 32-bit gestartet." <<
                                std::endl ;
                            }   else
                            if (wintxt.find("MSYS64") != std::string::npos) {
                                std::cout << "Programm wurde in MSYS 64-bit gestartet." <<
                                std::endl ;
                            }   else
                            if (wintxt.find("MINGW32") != std::string::npos) {
                                std::cout << "Programm wurde in MINGW 32-bit gestartet." <<
                                std::endl ;
                            }   else
                            if (wintxt.find("MINGW64") != std::string::npos) {
                                std::cout << "Programm wurde in MINGW 64-bit gestartet." <<
                                std::endl ;
                            }
                        }
                        return EXIT_SUCCESS;
                    }
                    else {
                        std::cerr << "window title could not be get." <<
                        std::endl ;
                    }
                    
                    if (VirtualFree(windowText, 0, MEM_RELEASE) == 0) {
                        std::cerr << "error: could not free memory." <<
                        std::endl ;
                        ErrorExit(TEXT("VirtualFree"));
                    }
                }
            }
            return EXIT_FAILURE;
        }
    );
}

// ---------------------------------------------------------
// perform pre-tasks: de-compress the locale file:
// ---------------------------------------------------------
int handle_locale()
{
    // default:
    locale_str = en_US;
    LCID lcid  = 0;
    
    if (GetLocaleInfoEx(
        LOCALE_NAME_USER_DEFAULT,
        LOCALE_RETURN_NUMBER | LOCALE_ILANGUAGE,
        (LPWSTR)&lcid,
        sizeof(lcid)) < 2) {
        std::cerr << "can not get locale, use default en-US." <<
        std::endl ;
        
        return EXIT_FAILURE;
    }

    // -----------------
    // save old locale
    // -----------------
    locale_LCID_old = GetThreadLocale();
    
    // -----------------------------------------------------
    // supported locales ...
    // -----------------------------------------------------
    if (lcid == 0x0407) {
        SetConsoleOutputCP(65001); // set codepage UTF-8

        locale_str      = de_DE;
        locale_LCID_new =
            MAKELCID(
            MAKELANGID(
            LANG_GERMAN,
            SUBLANG_GERMAN),SORT_DEFAULT);

        // -------------------------
        // Make change known.
        // -------------------------
        SetEnvironmentVariable(
        LPCTSTR("LC_ALL"),
        LPCTSTR("de_DE.UTF-8"));
        
        SetEnvironmentVariable(
        LPCTSTR("LANGUAHE"),
        LPCTSTR("de_DE.UTF-8"));    {
            extern int  _nl_msg_cat_cntr;
            ++_nl_msg_cat_cntr;
        }
        
        SetThreadLocale(locale_LCID_new );
        return getLocaleSystemUTF8(de_DE);
    }
    else {
        std::cout << "4444444444444" << std::endl;
        SetConsoleOutputCP(65001); // set codepage UTF-8
        
        locale_str      = en_US;
        locale_LCID_new =
            MAKELCID(
            MAKELANGID(
            LANG_ENGLISH,
            SUBLANG_DEFAULT),SORT_DEFAULT);

        // -------------------------
        // Make change known.
        // -------------------------
        SetEnvironmentVariable(
        LPCTSTR("LC_ALL"),
        LPCTSTR("en_US.UTF-8"));
        
        SetEnvironmentVariable(
        LPCTSTR("LANGAGE"),
        LPCTSTR("en_US.UTF-8"));    {
            extern int  _nl_msg_cat_cntr;
            ++_nl_msg_cat_cntr;
        }
        
        SetThreadLocale(locale_LCID_new );
        return getLocaleSystemUTF8(en_US);

    }   return EXIT_FAILURE;
}

int handle_object_file( const char *filename)
{
    std::fstream fh;
    std::string  fpath(filename);
    std::string  ext(ExtractFileExtension(filename));
    
    fh.open(filename, std::fstream::in | std::fstream::binary);
    
    if (!fh.is_open()) {
        std::cout << "error: file '" << filename
                  << "' file is not open."
                  << std::endl;
        return EXIT_FAILURE;
    }
    if (fh.fail()) {
        std::cout << "error: file '" << filename
                  << "' could not be open."
                  << std::endl;
        return EXIT_FAILURE;
    }
    
    // ----------------------------
    // read COFF header:
    // ----------------------------
    IMAGE_FILE_HEADER hdr;
    fh.read((char*)&hdr, sizeof(IMAGE_FILE_HEADER));
    if (sizeof(hdr) != 20) {
        std::stringstream ss;
        ss << "IMAGE_FILE_HEADER has invalid size.";
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
    }
    
    if (hdr.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
        std::cout << "file is execute able."
                  << std::endl
                  << std::endl;
    }
    
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
    if (hdr.Machine == IMAGE_FILE_MACHINE_AMD64) {
        std::cout << "Intel/AMD x64 - 64 bit" << std::endl;
    }   else
    
    // ----------------------------
    // Intel Itanium
    // ----------------------------
    if (hdr.Machine == IMAGE_FILE_MACHINE_IA64) {
        std::cout << "Intel Itanium" << std::endl;
    }   else {
        std::stringstream ss;
        ss << "machine: could not determine." << std::endl;
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
    }
    
    // ----------------------------
    // Windows limit sections to 96
    // ----------------------------
    if ((hdr.NumberOfSections > 0) && (hdr.NumberOfSections < 96)) {
        std::cout << "NumberOfSections     : 0x" << hdr.NumberOfSections << std::endl;
    }   else {
        std::stringstream ss;
        ss << "NumberOfSecions >= 96." << std::endl;
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
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
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
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
    std::cout << "Characterisics       : "
              << hdr.Characteristics
              << std::endl;
    
    // ---------------------------------------------------------
    // Relocation information was stripped from the file.
    // The file must be loaded at its preferred base address.
    // If the base address is not available, the loader reports
    // an error ...
    // ---------------------------------------------------------
    if (hdr.Characteristics & IMAGE_FILE_RELOCS_STRIPPED) {
        std::cout << std::tab << "IMAGE_FILE_RELOCS_STRIPPED" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) {
        std::cout << std::tab << "IMAGE_FILE_EXECUTABLE_IMAGE" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED) {
        std::cout << std::tab << "IMAGE_FILE_LINE_NUMS_STRIPPED" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED) {
        std::cout << std::tab << "IMAGE_FILE_LOCAL_SYMS_STRIPPED" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_AGGRESIVE_WS_TRIM) {
        std::cout << std::tab << "IMAGE_FILE_AGGRESIVE_WS_TRIM" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE) {
        std::cout << std::tab << "IMAGE_FILE_LARGE_ADDRESS_AWARE" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_BYTES_REVERSED_LO) {
        std::cout << std::tab << "IMAGE_FILE_BYTES_REVERSED_LO" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_32BIT_MACHINE) {
        std::cout << std::tab << "IMAGE_FILE_32BIT_MACHINE" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_DEBUG_STRIPPED) {
        std::cout << std::tab << "IMAGE_FILE_DEBUG_STRIPPED" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) {
        std::cout << std::tab << "IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP) {
        std::cout << std::tab << "IMAGE_FILE_NET_RUN_FROM_SWAP" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_SYSTEM) {
        std::cout << std::tab << "IMAGE_FILE_SYSTEM" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_DLL) {
        std::cout << std::tab << "IMAGE_FILE_DLL" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY) {
        std::cout << std::tab << "IMAGE_FILE_UP_SYSTEM_ONLY" <<
        std::endl ;
    }
    if (hdr.Characteristics & IMAGE_FILE_BYTES_REVERSED_HI) {
        std::cout << std::tab << "IMAGE_FILE_BYTES_REVERSED_HI" <<
        std::endl ;
    }   std::cout << std::endl;
    
    
    // ------------------------------------------------------
    // if optional flag > 0 => check, if 32-, or 64-bit ...
    // ------------------------------------------------------
    if (hdr.SizeOfOptionalHeader > 0)
    {
        IMAGE_OPTIONAL_HEADER32 opthdr32;
        IMAGE_OPTIONAL_HEADER64 opthdr64;

        if (hdr.Machine == IMAGE_FILE_MACHINE_I386) {
            fh.read((char*)&opthdr32, sizeof(IMAGE_OPTIONAL_HEADER32));
            if (sizeof(opthdr32) != 20) {
                std::stringstream ss;
                ss << "IMAGE_OPTIONAL_HEADER32 invalid size.";
                std::cerr << ss.str() << std::endl;
                return EXIT_FAILURE;
            }
        }   else {
            fh.read((char*)&opthdr64, sizeof(IMAGE_OPTIONAL_HEADER64));
            if (sizeof(opthdr64) != 20) {
                std::stringstream ss;
                ss << "IMAGE_OPTIONAL_HEADER64 invalid size.";
                std::cerr << ss.str() << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    
    // ----------------------------
    // read section header:
    // ----------------------------
    std::cout << "Section Header:" << std::endl
              << "---------------" << std::endl;

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
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
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

    struct COFFSymbol {
        char name[8];
        uint32_t value;
        uint16_t section;
        uint16_t type;
    };
    
    size_t recordSize = sizeof(COFFSymbol);
    std::vector<COFFSymbol> symbols;
    COFFSymbol symbol;

    fh.seekg(hdr.PointerToSymbolTable,fh.beg);
    fh.read(reinterpret_cast<char*>(&symbol), recordSize);
    symbols.push_back(symbol);
    
    // ----------------------------
    // collect symbol names ...
    // ----------------------------
    for (int i = 0; i < hdr.NumberOfSymbols-2; ++i) {
        fh.seekg(hdr.PointerToSymbolTable
        + (sizeof(uint32_t) * (i + 1))
        + (sizeof(uint16_t) * (i + 1))
        + (sizeof(uint16_t) * (i + 1)) + (((i + 1) * 10)),
        fh.beg);
        fh.read((char*)&symbol, recordSize);
        symbols.push_back(symbol);
    }
    
    // ----------------------------
    // print symbol informations:
    // ----------------------------
    for (const COFFSymbol& symbol : symbols) {
        std::cout << std::endl;
        std::cout << "Name    : "   <<             symbol.name    << std::endl;
        std::cout << "Value   : 0x" << std::hex << symbol.value   << std::endl;
        std::cout << "Section : "   <<             symbol.section << std::endl;
        std::cout << "Type    : 0x" << std::hex << symbol.type    << std::endl;
        
        //asmjit::Label lbl = asm_parser->asm_code->newLabel();
        //asm_parser->asm_labels[ symbol.name ] = lbl;
    }
    fh.close();
    return EXIT_SUCCESS;
}

int handle_asm_file( const char *filename )
{
    std::fstream fh;
    std::string  fpath(filename);
    std::string  ext(ExtractFileExtension(filename));

    // ----------------------------
    // read .asm text file
    // ----------------------------
    if (ext == ".asm") {
        // ----------------------------
        // create assembler object ...
        // ----------------------------
        asm_parser = new AsmParser(filename,true);
        
        delete asm_parser;
        return EXIT_SUCCESS;
    }   else {
        if (asm_parser != nullptr)
        delete asm_parser;

        std::stringstream ss;
        ss << "usage: diss.exe [-io file.o] or [-ia file.asm]" << std::endl
           << gettext("use: --help for more options.");
        std::cerr << ss.str() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void asm_file_input( std::string i_file )
{
    file_input_asm = i_file;
}
void obj_file_input( std::string i_file )
{
    file_input_obj = i_file;
}
void cm_file_output( std::string o_file )
{
    file_output_cm = o_file;
}
void ch_file_output( std::string o_file )
{
    file_output_ch = o_file;
}
void ct_file_output( std::string o_file )
{
    file_output_ct = o_file;
}

// -----------------------------------------------------------------
// remove the de-gzip'ed locale file(s) ...
// -----------------------------------------------------------------
void removeLocaleFile( std::string ls )
{
    namespace fs = std::filesystem;
    
    std::stringstream ss;
    try {
    ss  << ".\\locale\\"
        << ls << ".utf8\\LC_MESSAGES\\"
        << ApplicationName
        << ".mo";
        fs::path filePath = ss.str();
        if (fs::exists( filePath )) {
            fs::remove( filePath );
        }
    }
    catch (std::exception &ex) {
        std::cerr << _("Error: file could not be deleted: ")
                  << ex.what()
                  <<
        std::endl ;
    }
}

// -----------------------------------------------------------------
// clean-up the workspace ...
// -----------------------------------------------------------------
void cleanup() {
    // -------------------------------------------------------------
    // at terminating application, delete de-packed .mo file.
    // this make space for other usage, with other application's ...
    // TODO: check directory, and/or file.
    // -------------------------------------------------------------
    removeLocaleFile( de_DE );
    removeLocaleFile( en_US );
    
    SetThreadLocale(locale_LCID_old);
}

// -----------------------------------------------------------------
// entry point function for our disassembler ...
// -----------------------------------------------------------------
int main(int argc, char **argv)
{
    options_description desc{"Options"};
    variables_map       vm;
    int                 result = 1;
    
    // ----------------------------
    // parse command line args:
    // ----------------------------
    try {
        if (handle_locale() == EXIT_FAILURE)
        return EXIT_FAILURE;

        if (handle_codepage() == 0)
        return EXIT_FAILURE;
std::cout << "---> " << locale_str << std::endl;
        // ----------------------------------
        // registering the clean-up function
        // ----------------------------------
        if (atexit(cleanup) != 0) {
            std::cerr << _("error: can not register cleanup function.") <<
            std::endl ;
            return EXIT_FAILURE;
        }
        
        // ----------------------------------
        // if no argument given, display help
        // ----------------------------------
        if (argc == 1) {
            std::cerr << gettext("use --help for help.") <<
            std::endl ;
            return EXIT_FAILURE;
        }

        // -------------------------------------------------------
        // --help:   help screen
        // --locale: use localization (en = english, de = german)
        // -------------------------------------------------------
        options_description general(_("General Options"));
            general.add_options()
            ("help,h"  , _("Help screen"))
            ("locale,l", value< std::string >()->default_value("en"  ), _("country locale"))
            ("gui,g"   , "TUI - Text User Interface");
            
        options_description input_long(_("Input Options (long)"));
            input_long.add_options()
            ("input-asm", value< std::string >()->notifier(asm_file_input), _("Input assembler file"))
            ("input-obj", value< std::string >()->notifier(obj_file_input), _("Input object file"));
            
        options_description input_short(_("Input Options (short)"));
            input_short.add_options()
            ("ia", value< std::string >()->notifier(asm_file_input), _("Input assembler file"))
            ("io", value< std::string >()->notifier(obj_file_input), _("Input object file"));
            
        options_description output_long(_("Output Options (long)"));
            output_long.add_options()
            ("output-ct" , value< std::string >()->notifier(ct_file_output), _("Output C++ tool file"))
            ("output-ch" , value< std::string >()->notifier(ch_file_output), _("Output C++ header file"))
            ("output-cm" , value< std::string >()->notifier(cm_file_output), _("Output C++ main file"));
            
        options_description output_short(_("Output Options (short)"));
            output_short.add_options()
            ("ct", value< std::string >()->notifier(ct_file_output), _("Output C++ tool file"))
            ("ch", value< std::string >()->notifier(ch_file_output), _("Output C++ header file"))
            ("cm", value< std::string >()->notifier(cm_file_output), _("Output C++ main file"));

        options_description allOptions("All Options");
        allOptions
            .add(general)
            .add(input_long)
            .add(input_short)
            .add(output_long)
            .add(output_short);
            
        store(parse_command_line(argc, argv, allOptions), vm);
        notify(vm);
        
        // ----------------------------
        // check given arguments:
        // ----------------------------
        if (vm.count("help")) {
            std::cout << allOptions << std::endl;
            return EXIT_SUCCESS;
        }   else
            
        // ----------------------------
        // localization:
        // ----------------------------
        if (vm.count("locale")) {
            locale_str = vm["locale"].as< std::string >();
            
            if (locale_str.length() <  2) {
                std::cerr << "invalid locale parameter length." << std::endl;
                return EXIT_FAILURE;
            }
            // ----------------------------
            // hard coded: en, de:
            // ----------------------------
            if((locale_str.length() >= 2) && (locale_str.length() < 4)) {
                size_t found_en ;
                size_t found_de ;
                size_t found = 0;
                
                found_en  = locale_str.find( std::string("en") );
                found_de  = locale_str.find( std::string("de") );
                
                if (found_en != std::string::npos) { found = 1; locale_str = "en"; } else
                if (found_de != std::string::npos) { found = 1; locale_str = "de"; } else
                
                locale_str = "en"; } else {
                locale_str = "en";
            }
            found_args = true;
        }

        // --------------------------------------
        // if all fails, use default en = English
        // --------------------------------------
        if (locale_str.empty()) {
            locale_str = "en";
            found_args = true;
        }
        
        
        // --------------------------------------
        // open textual GUI: TurboVision for DOS
        // --------------------------------------
        if (vm.count("gui")) {
            return TurboMain();
        }
        
        // --------------------------------------
        // check, if input, and output file is ok
        // --------------------------------------
        if (file_input_asm.empty()) {
            std::cerr << "// " <<  gettext("input assembly file missing.") << std::endl;
            return EXIT_FAILURE;
        }   else {
            std::stringstream ss;
            
            // asm input
            std::string ext(ExtractFileExtension(file_input_asm));
            if (ext != ".asm") {
                std::cerr << "// " <<  gettext("input main C++ file must have extension .asm")
                          << std::endl;
                return EXIT_FAILURE;
            }
            
            // c++ output.cc
            if (file_output_cm.empty()) {
                std::cout << "// " <<  gettext("output main C++ file missing, use default.")
                          << std::endl;
                file_output_cm = "aout_main.cc";
            }
            else {
                std::string ext(ExtractFileExtension(file_output_cm));
                if ((ext != ".cc") || (ext != ".cc")) {
                    std::cout << "// " << gettext("output main C++ file must have extension .cc")
                              << std::endl;
                    return EXIT_FAILURE;
                }
            }
            
            // c++ header.h
            if (file_output_ch.empty()) {
                std::cout << "// " <<  gettext("output header C++ file missing, use default.")
                          << std::endl;
                file_output_ch = "aout_header.h";
            }
            else {
                std::string ext(ExtractFileExtension(file_output_ch));
                if ((ext != ".h") || (ext != ".H")) {
                    std::cout << "// " <<  gettext("output header C++ file must have extension .h")
                              << std::endl;
                    return EXIT_FAILURE;
                }
            }
            
            // c++ misc.cc
            if (file_output_ct.empty()) {
                std::cout << "// " <<  "output tool C++ file missing, use default." << std::endl;
                file_output_ct = "aout_misc.cc";
            }
            else {
                std::string ext(ExtractFileExtension(file_output_ct));
                if ((ext != ".cc") || (ext != ".cc")) {
                    std::cout << "// " <<  "output misc C++ file must have extension .cc" << std::endl;
                    return EXIT_FAILURE;
                }
            }
            
            return handle_asm_file( file_input_asm.c_str() );
        }
        
        if (file_input_obj.empty()) {
            std::cerr << "input object file missing." << std::endl;
            return EXIT_FAILURE;
        }   else {
            return handle_object_file( file_input_obj.c_str() );
        }
    }
    // ----------------------------
    // we use try catch for errors:
    // ----------------------------
    catch (error const &e) {
        std::cerr << "boost exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "exception: common" << std::endl;
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}

AsmParser::AsmParser( const char *filename, bool mode )
{
    // --------------------------------------------------------
    // try to open input file.
    // --------------------------------------------------------
    if (mode == false)
        yyin = fopen( filename, "rb" ); else
        yyin = fopen( filename, "r"  );
    if(!yyin)
    throw EPascalException_FileNotOpen (_("parser file could not be open."));
    
    // ----------------------------
    // pre-tasks preparations ...
    // ----------------------------    
    env      = Environment::host();
    features = CpuInfo::host().features();
    
    uint64_t baseAddress = uint64_t(0x1974);
    
    code     = new CodeHolder();
    code->init(env, features, baseAddress);
    
    cod_code = new x86::Builder  ( code );
    asm_code = new x86::Assembler( code );
    
    yyparse();
    asm_parser_main();
}

// -----------------------------------------------------------------
// clean up global storage ...
// -----------------------------------------------------------------
AsmParser::~AsmParser()
{
    std::cout << "// " <<  _("please wait...") << std::endl;

    delete asm_code;
    delete cod_code;
    delete     code;
    
    fclose(yyin);
}

AsmParser::AsmParser() { }
