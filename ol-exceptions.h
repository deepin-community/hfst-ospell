#ifndef _OL_EXCEPTIONS_H
#define _OL_EXCEPTIONS_H

#include "hfstol-stdafx.h"
#include <string>
#include <sstream>
#include <cstring>

namespace hfst_ospell
{

// This structure is inherited from for each exception. Taken from HFST library
// code.
//! @brief Top level exception class for ospell related errors.

//! Ospell exceptions can hold basic back-track information for programmer as
//! well as human readable explanation.
struct OspellException
{
    std::string name; //!< short description of exception
    std::string file; //!< file name of exception
    size_t line;      //!< line number of exception

    OspellException(void) {}

//!
//! construct exception with name, file and location
    OspellException(const std::string &name,const std::string &file,size_t line):
    name(name),
    file(file),
    line(line)
    {}

    //!
    //! create string representation of exception for output
    std::string operator() (void) const
    {
        std::ostringstream o;
        o << "Exception: "<< name << " in file: "
          << file << " on line: " << line;
        return o.str();
    }
    //!
    //! create char array representation of exception for output
    const char* what()
      {
        std::ostringstream o;
        o << file << ":" << line << ":" << name;
        return strdup(o.str().c_str());
      }
};

// These macros are used instead of the normal exception facilities.

#define HFSTOSPELL_THROW(E) throw E(#E,__FILE__,__LINE__)

#define HFSTOSPELL_THROW_MESSAGE(E,M) throw E(std::string(#E)+": "+std::string(M)\
                        ,__FILE__,__LINE__)

#define HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(CHILD) \
    struct CHILD : public OspellException \
    { CHILD(const std::string &name,const std::string &file,size_t line):\
    OspellException(name,file,line) {}}

#define HFST_CATCH(E)                           \
    catch (const E &e)                          \
    {                                   \
    std::cerr << e.file << ", line " << e.line << ": " <<       \
        e() << std::endl;                       \
    }

// Now the exceptions themselves

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(HeaderParsingException);

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(AlphabetParsingException);

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(IndexTableReadingException);

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(TransitionTableReadingException);

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(UnweightedSpellerException);

HFSTOSPELL_EXCEPTION_CHILD_DECLARATION(TransducerTypeException);
} // namespace
#endif // _OL_EXCEPTIONS_H
