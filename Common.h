#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>
#include <gc_allocator.h>
#include <gc_cpp.h>

// type defines for garbage collected versions of string and stringstream
typedef std::basic_string<char, std::char_traits<char>, gc_allocator<char> > string;
typedef std::basic_stringstream<char, std::char_traits<char>, gc_allocator<char> > stringstream;

//! Base Class For all Exceptions
class BaseException : public std::exception {};

#endif
