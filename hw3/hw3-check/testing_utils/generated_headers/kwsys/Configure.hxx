/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing#kwsys for details.  */
#ifndef kwsys_Configure_hxx
#define kwsys_Configure_hxx

/* Include C configuration.  */
#include <kwsys/Configure.h>

/* Whether wstring is available.  */
#define kwsys_STL_HAS_WSTRING 1
/* Whether <ext/stdio_filebuf.h> is available. */
#define kwsys_CXX_HAS_EXT_STDIO_FILEBUF_H                         \
  1

#if defined(__SUNPRO_CC) && __SUNPRO_CC > 0x5130 && defined(__has_attribute)
#  define kwsys__has_cpp_attribute(x) __has_attribute(x)
#elif defined(__has_cpp_attribute)
#  define kwsys__has_cpp_attribute(x) __has_cpp_attribute(x)
#else
#  define kwsys__has_cpp_attribute(x) 0
#endif

#if __cplusplus >= 201103L
#  define kwsys_NULLPTR nullptr
#else
#  define kwsys_NULLPTR 0
#endif

#ifndef kwsys_FALLTHROUGH
#  if __cplusplus >= 201703L &&                                               \
    kwsys__has_cpp_attribute(fallthrough)
#    define kwsys_FALLTHROUGH [[fallthrough]]
#  elif __cplusplus >= 201103L &&                                             \
    kwsys__has_cpp_attribute(gnu::fallthrough)
#    define kwsys_FALLTHROUGH [[gnu::fallthrough]]
#  elif __cplusplus >= 201103L &&                                             \
    kwsys__has_cpp_attribute(clang::fallthrough)
#    define kwsys_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif
#ifndef kwsys_FALLTHROUGH
#  define kwsys_FALLTHROUGH static_cast<void>(0)
#endif

#undef kwsys__has_cpp_attribute

/* If building a C++ file in kwsys itself, give the source file
   access to the macros without a configured namespace.  */
#if defined(KWSYS_NAMESPACE)
#  if !kwsys_NAME_IS_KWSYS
#    define kwsys kwsys
#  endif
#  define KWSYS_NAME_IS_KWSYS kwsys_NAME_IS_KWSYS
#  define KWSYS_STL_HAS_WSTRING kwsys_STL_HAS_WSTRING
#  define KWSYS_CXX_HAS_EXT_STDIO_FILEBUF_H                                   \
    kwsys_CXX_HAS_EXT_STDIO_FILEBUF_H
#  define KWSYS_FALLTHROUGH kwsys_FALLTHROUGH
#  define KWSYS_NULLPTR kwsys_NULLPTR
#endif

#endif
