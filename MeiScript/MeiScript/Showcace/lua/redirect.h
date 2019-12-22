#pragma once
#include <stdio.h>

extern FILE* mystdout;
extern FILE* mystderr;

int init_io();

void close_io();

void my_write(const char* s, size_t l);

/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   my_write((s), l)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(mystdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(mystdout, (s), (p)), fflush(mystderr))
#endif