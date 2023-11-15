#pragma once
typedef unsigned P_id_type;

#define _FAR


#define __fLink_def

struct fLink
{
    fLink _NEAR *f;
    class TStreamableClass _NEAR *t;
    static class TStreamableClass * volatile forceLink;
};

#define __TStreamable

class TStreamable
{

    friend class pstream;
    friend class opstream;
    friend class ipstream;

private:

    virtual const char *streamableName() const = 0;

protected:

    virtual void *read( ipstream& ) = 0;
    virtual void write( opstream& ) = 0;

};

#define __TStreamableClass

#include <tvision/compat/borland/dos.h>
#include <limits.h>
#include <stddef.h>

const P_id_type P_id_notFound = UINT_MAX;

typedef TStreamable *(*BUILDER)();

// This is now computed at runtime by ipstream.
#define __DELTA( d ) 0

class TStreamableClass
{

    friend TStreamableTypes;
    friend opstream;
    friend ipstream;

public:

    TStreamableClass( const char *n, BUILDER b, int /* unused */ = 0 ) noexcept;

private:

    const char *name;
    BUILDER build;

};

#define __TStreamableTypes

class TStreamableTypes : private TNSSortedCollection
{

public:

    TStreamableTypes() noexcept;
    ~TStreamableTypes();

    void registerType( const TStreamableClass * );
    const TStreamableClass *lookup( const char * );

    void *operator new( size_t sz ) { return ::operator new( sz ); }
    void *operator new( size_t, void * );

private:

    virtual void *keyOf( void * );
    int compare( void *, void * );

};

#define __TPWrittenObjects

class TPWrittenObjects : public TNSSortedCollection
{

    friend opstream;

public:

    void removeAll() { curId = 0; TNSSortedCollection::freeAll(); }

private:

    TPWrittenObjects() noexcept;
    ~TPWrittenObjects();

    void registerObject( const void *adr );
    P_id_type find( const void *adr );

    void *keyOf( void * );
    int compare( void *, void * );

    P_id_type curId;

};

class TPWObj
{

    friend TPWrittenObjects;

private:

    TPWObj( const void *adr, P_id_type id ) noexcept;

    const void *address;
    P_id_type ident;

};

#define __TPReadObjects

class TPReadObjects : public TNSCollection
{

    friend ipstream;

public:

    void removeAll() { curId = 0; TNSCollection::removeAll(); }

private:

    TPReadObjects() noexcept;
    ~TPReadObjects();

    void registerObject( const void *adr );
    const void *find( P_id_type id );

    P_id_type curId;

};

#define __pstream


class _FAR TStreamableTypes;

class pstream
{

    friend TStreamableTypes;

public:

    enum StreamableError { peNotRegistered, peInvalidType };
    enum PointerTypes { ptNull, ptIndexed, ptObject };

    _Cdecl pstream( streambuf _FAR * ) noexcept;
    virtual _Cdecl ~pstream();

    typedef int openmode;
    typedef int seekdir;

    int _Cdecl rdstate() const noexcept;
    int _Cdecl eof() const noexcept;
    int _Cdecl fail() const noexcept;
    int _Cdecl bad() const noexcept;
    int _Cdecl good() const noexcept;
    void _Cdecl clear( int = 0 ) noexcept;
    _Cdecl operator void *() const noexcept;
    int _Cdecl operator ! () const noexcept;

    streambuf _FAR * _Cdecl rdbuf() const noexcept;

    static void initTypes() noexcept;
    static void registerType( TStreamableClass *ts ) noexcept;

protected:

    _Cdecl pstream() noexcept;

    void _Cdecl error( StreamableError ) noexcept;
    void _Cdecl error( StreamableError, const TStreamable& ) noexcept;

    streambuf _FAR *bp;
    int state;

    void _Cdecl init( streambuf _FAR * ) noexcept;
    void _Cdecl setstate( int ) noexcept;

    static TStreamableTypes * _NEAR types;

};

class _FAR TStreamableClass;

class ipstream : virtual public pstream
{

public:

    _Cdecl ipstream( streambuf _FAR * ) noexcept;
    _Cdecl ~ipstream();

    streampos _Cdecl tellg();
    ipstream& _Cdecl seekg( streampos );
    ipstream& _Cdecl seekg( streamoff, pstream::seekdir );

    uchar _Cdecl readByte();
    void _Cdecl readBytes( void _FAR *, size_t );
    ushort _Cdecl readWord();
    char _FAR * _Cdecl readString();
    char _FAR * _Cdecl readString( char _FAR *, unsigned );

    friend ipstream& _Cdecl operator >> ( ipstream&, TStreamable& );
    friend ipstream& _Cdecl operator >> ( ipstream&, void _FAR *& );

protected:

    _Cdecl ipstream() noexcept;

    const TStreamableClass _FAR * _Cdecl readPrefix();
    void _FAR * _Cdecl readData( const TStreamableClass _FAR *,
                                        TStreamable _FAR * );
    void _Cdecl readSuffix();

    const void _FAR * _Cdecl find( P_id_type );
    void _Cdecl registerObject( const void _FAR *adr );

private:

    TPReadObjects objs;

};

#define __opstream



class _FAR TStreamableClass;

class opstream : virtual public pstream
{

public:

    _Cdecl opstream( streambuf _FAR * ) noexcept;
    _Cdecl ~opstream();

    streampos _Cdecl tellp();
    opstream& _Cdecl seekp( streampos );
    opstream& _Cdecl seekp( streamoff, pstream::seekdir );
    opstream& _Cdecl flush();

    void _Cdecl writeByte( uchar );
    void _Cdecl writeBytes( const void _FAR *, size_t );
    void _Cdecl writeWord( ushort );
    void _Cdecl writeString( const char _FAR * );
    void _Cdecl writeString( TStringView );

    friend opstream& _Cdecl operator << ( opstream&, TStreamable& );
    friend opstream& _Cdecl operator << ( opstream&, TStreamable _FAR * );

protected:

    _Cdecl opstream() noexcept;

    void _Cdecl writePrefix( const TStreamable& );
    void _Cdecl writeData( TStreamable& );
    void _Cdecl writeSuffix( const TStreamable& );

    P_id_type _Cdecl find( const void _FAR *adr );
    void _Cdecl registerObject( const void _FAR *adr );

private:

    TPWrittenObjects *objs;

};

#define __iopstream

class iopstream : public ipstream, public opstream
{

public:

    _Cdecl iopstream( streambuf _FAR * ) noexcept;
    _Cdecl ~iopstream();

protected:

    _Cdecl iopstream() noexcept;

};

#define __fpbase

#include <tvision/compat/borland/fstream.h>

class fpbase : virtual public pstream
{

public:

    _Cdecl fpbase() noexcept;
    _Cdecl fpbase( const char _FAR *, pstream::openmode);
    _Cdecl ~fpbase();

    void _Cdecl open( const char _FAR *, pstream::openmode);
    void _Cdecl close();
    filebuf _FAR * _Cdecl rdbuf() noexcept;

private:

    filebuf buf;

};

#define __ifpstream

class ifpstream : public fpbase, public ipstream
{

public:

    _Cdecl ifpstream() noexcept;
    _Cdecl ifpstream( const char _FAR *,
                      pstream::openmode = ios::in
                    );
    _Cdecl ~ifpstream();

    filebuf _FAR * _Cdecl rdbuf() noexcept;
    void _Cdecl open( const char _FAR *,
                      pstream::openmode = ios::in
                    );

};

#define __ofpstream


class ofpstream : public fpbase, public opstream
{

public:

    _Cdecl ofpstream() noexcept;
    _Cdecl ofpstream( const char _FAR *,
                      pstream::openmode = ios::out
                    );
    _Cdecl ~ofpstream();

    filebuf _FAR * _Cdecl rdbuf() noexcept;
    void _Cdecl open( const char _FAR *,
                      pstream::openmode = ios::out
                    );

};

#define __fpstream

class fpstream : public fpbase, public iopstream
{

public:

    _Cdecl fpstream() noexcept;
    _Cdecl fpstream( const char _FAR *, pstream::openmode);
    _Cdecl ~fpstream();

    filebuf _FAR * _Cdecl rdbuf() noexcept;
    void _Cdecl open( const char _FAR *, pstream::openmode);

};


