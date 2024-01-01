/**
 * \file      string.hpp
 * \namespace std
 * \cond german
 * \brief Der STL (Standard Template Library) std Namensbereich.
 *
 * Die \a_colorYellow{STL} ist eine hochflexible Sammlung von Template-Klassen.
 * Leider bringt diese Flexibilität eine Komplexität mit sich,
 * die es dem Anfänger schwer macht, die STL zu verstehen.
 * Das wird vermutlich der Grund sein, warum sie von manchen C++-Programmierern
 * nicht benutzt wird und von einigen C++-Büchern vollständig ignoriert wird.
 * \endcond
 *
 * \cond english
 * \brief The STL (Standard Template Library) std namespace
 *
 * The STL is a highly flexible Collection of Template Classes.
 * But they bring a very complexity, that make it hard to understand for youngsters.
 * That maybe the reason that many C++ Programmers don't use it, or they would be
 * ignore completly by modern C++ books.
 * \endcond
 */
namespace std
{
    template<typename CharT, typename Traits = char_traits<CharT>, typename Allocator = allocator<CharT>>
    class basic_string {
        // ...
    };

    /**
     * \cond german
     * \class string
     * \brief Dies ist die Hauptklasse für die String Behandlung und Manipulation.
     * \endcond
     *
     * \cond english
     * \class string
     * \brief This is the main class for String handling, and manipulation's.
     * \endcond
     */
    class string {
    };
    
    /**
     * \cond english
     * \brief This is a UTF-8 / Ansi String ( 1 Byte per Char ).
     * \endcond
     *
     * \cond german
     * \brief Dies ist ein UTF-8 / Ansi String ( 1 Byte pro Zeichen ).
     * \endcond
     */
    typedef basic_string<char> string;

    /**
     * \cond english
     * This is a Unicode String ( 2 Byte per Character ).
     * \endcond
     *
     * \cond german
     * \brief Dies ist ein Unicode String ( 2 Byte pro Zeichen ).
     * \endcond
     */
    typedef basic_string<wchar_t> wstring;
}
