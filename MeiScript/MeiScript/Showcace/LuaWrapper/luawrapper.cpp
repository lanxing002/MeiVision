#include "luawrapper.h"

namespace Lua {

	static const luaL_Reg mat_meta_fun[] = {
		{"open", Lua_Mat::open_mat},
	    {"show", Lua_Mat::show_mat},
	    {"at", Lua_Mat::at},
	    {"write", Lua_Mat::write},
		{NULL, NULL}
	};

	int Lua_Mat::open_mat(lua_State* L) {
		// a table function, first arg is a table
		//luaL_checktype(L, 1, LUA_TNUMBER);  // is a hashcode for pointer
	
		//size_t hash_code = lua_tonumber(L, -1);
		//lua_createtable(L, 0, 0);
		//lua_pushnumber(L, hash_code);
		//lua_setfield(L, -2, "hash");

		// set metatable for this table
		std::cout << "mat \"open\" method recall" << endl;

		return 1; // return a table 


		//const char* imagePath = lua_tostring(L, 2);
		//QImage* img = new QImage(imagePath);
		//if (img == nullptr) {
		//	lua_pushboolean(L, false);  // print error message
		//	return 1;
		//}
		//else {
		//	lua_pushboolean(L, true);
		//}

		//size_t hash_code = hasher(img);
		//img_map[hash_code] = img;
		//conver pointer to hash value for resue
	}

	int Lua_Mat::show_mat(lua_State* L) {
		std::cout << "mat \"show\" method recall" << endl;
		return 1;
	}

	int Lua_Mat::at(lua_State* L) {
		std::cout << "mat \"at\" methond recall" << endl;
		return 1;
	}

	int Lua_Mat::write(lua_State* L) {
		std::cout << "mat \"write\" method recall" << endl;
		return 1;
	}

	void Lua_CretaTable::create_mat_metatable(lua_State* L) {
		lua_createtable(L, 0, 1); //create metateable for a new table
		lua_createtable(L, 0, 4); // create __index table for basic function
		
		lua_pushcfunction(L, Lua_Mat::write);
		lua_pushcfunction(L, Lua_Mat::at);
		lua_pushcfunction(L, Lua_Mat::show_mat);
		lua_pushcfunction(L, Lua_Mat::open_mat);

		// register all function 
		lua_setfield(L, 2, "open");
		lua_setfield(L, 2, "show");
		lua_setfield(L, 2, "at");
		lua_setfield(L, 2, "write");
		// set metatable's __index field
		lua_setfield(L, 1, "__index");
	}

	int Lua_CretaTable::init(lua_State* L) {
		
		//luaL_register(L, "mod", mat_meta_fun);
		create_mat_metatable(L);
		lua_createtable(L, 0, 0);
		lua_pushvalue(L,1);
		lua_setmetatable(L, -2);
		// return a table
		return 1;
	}
}