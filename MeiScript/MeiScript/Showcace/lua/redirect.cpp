extern "C" {
#include "redirect.h"
}

#include <iostream>
#include <sstream>
using namespace std;

class OutBuffer {
public:
	static stringstream outbuffer;

	static stringstream& getBuffer() {
		return outbuffer;
	}
};


FILE* mystdout;
FILE* mystderr;

int init_io() {
	OutBuffer::outbuffer = stringstream("");
	mystdout = fopen("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stdout.tmp", "wb");
	mystderr = fopen("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stderr.tmp", "wb");

	if (mystdout == NULL || mystderr == NULL)
		return -1;
	else return 0;
}

void close_io() {
	fclose(mystdout);
	fclose(mystderr);
	//remove("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stdout.tmp");
	//remove("C:/Users/riseK/mine/program/MeiVision/MeiScript/MeiScript/lua_stderr.tmp");
}


void my_write(const char* s, size_t l) {
	std::cout.write(s, l);
}