#pragma once
#include "SourceMnger.h"

extern "C" {
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}

//static function for lua
struct MeiImg
{
	static SourceMnger* imgMger;
	static int init(lua_State* L);
	static int open_mat(lua_State* L);
	static int show_mat(lua_State* L);  //connect with qt gui 
	static int at(lua_State* L);
	static int write(lua_State* L);
private:
	static size_t get_id(lua_State* L);
	static void create_mat_metatable(lua_State* L);
};

