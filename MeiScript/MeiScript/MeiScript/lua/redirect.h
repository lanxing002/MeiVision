#pragma once
#include <stdio.h>

extern FILE* mystdout;
extern FILE* mystderr;

int init_io();

void close_io();

void myfwrite(void const* _Buffer,
	size_t      _ElementSize,
	size_t      _ElementCount,
	FILE* _Stream);


/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), mystdout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(mystdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(mystderr, (s), (p)), fflush(mystderr))
#endif