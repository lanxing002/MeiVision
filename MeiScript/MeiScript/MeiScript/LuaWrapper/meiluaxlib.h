#pragma once
#include <iostream>
using namespace std;

void cpp_write(void const*, size_t elem_size, size_t elem_count, iostream& out);
//overwrite by cpp
/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   cpp_write((s), sizeof(char), (l), cout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), cout.flush())
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(stderr, (s), (p)), fflush(stderr))
#endif


/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(stdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

#include "../lua/lauxlib.h"
