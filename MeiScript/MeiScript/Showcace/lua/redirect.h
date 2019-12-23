#pragma once

#include <stdio.h>

void my_write(const char* s, size_t l);

void my_write_error(const char* str, const char* format);
/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   my_write((s), l)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (my_write_error((s), (p)))
#endif