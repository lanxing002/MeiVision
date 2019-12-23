#pragma once
#include <QImage>
#include <QDebug>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

extern "C" {
//#include "../../MeiScript/lua/lua.h"
//#include "../../MeiScript/lua/lauxlib.h"
//#include "../../MeiScript/lua/lualib.h"
#include "../lua/redirect.h"
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}


namespace Lua {

	struct Lua_Mat {
		//function corrseponse with lua function
		static int open_mat(lua_State* L);
		static int show_mat(lua_State* L);  //connect with qt gui 
		static int at(lua_State* L);
		static int write(lua_State* L);
	};

	struct Lua_CretaTable {
		static void create_mat_metatable(lua_State* L);
		static int init(lua_State* L);
	};

	class Lua_script {
	public:
		static int run_script(const string& str, stringstream& outbuffer);
		static streambuf* redirect_io(stringstream&);
		static void reset_io(streambuf*);
	};
	
}