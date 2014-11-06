#ifndef NETSTRING_HPP
#define NETSTRING_HPP

#define LEN_BUFFER_SIZE 10

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

std::size_t netstring_decode(const char * __netstring, std::size_t __max_len, const char ** __string);

#endif
