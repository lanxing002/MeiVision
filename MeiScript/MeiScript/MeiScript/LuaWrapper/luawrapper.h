#pragma once
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

extern "C" {
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
		static int run_script() {

			init_io();
			lua_State* L;

			if (nullptr == (L = luaL_newstate())) {
				cerr << "failed open lua" << endl;
				return -1;
			}

			luaL_openlibs(L);
			lua_register(L, "init", Lua_CretaTable::init);

			std::string lua_script = "t = init()\nprint(t)\nt.show();";
			std::string lua_script2 = "prnint(\"ttttttttttttttttt\")\n";

			//if (luaL_dofile(L, "C:\\Users\\riseK\\mine\\program\\MeiVision\\MeiScript\\MeiScript\\MeiScript\\lua_script_test\\lua_create.lua")) {
			//	cerr << "failed open lua test file" << endl;
			//	return -1;
			//}
			luaL_dostring(L, lua_script2.c_str());


			lua_close(L);
			//close_io();
			return 0;
		}
	};
	
}