#include "redirect.h"

FILE* mystdout;
FILE* mystderr;

int init_io() {
	mystdout = fopen("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stdout.tmp", "wb");
	mystderr = fopen("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stderr.tmp", "wb");

	if (mystdout == NULL || mystderr == NULL)
		return -1;
	else return 0;
}

void close_io() {
	fclose(mystdout);
	fclose(mystderr);
	remove("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stdout.tmp");
	remove("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stderr.tmp");
}

void myfwrite(void const* _Buffer,
 size_t      _ElementSize,
 size_t      _ElementCount,
 FILE* _Stream) {
	fwrite(_Buffer, _ElementSize, _ElementCount, _Stream);
}