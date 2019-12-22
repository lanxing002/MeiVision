#include <iostream>
#include "../LuaWrapper/luawrapper.h"
using namespace std;


lua_State* L;
static int average(lua_State* L) {
	int n = lua_gettop(L);
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += lua_tonumber(L, i);
	}
	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	return 2;
}

int main(void) {
	//L = lua_open();

	Lua::Lua_script::run_script();

	return 0;

	if (nullptr == (L = luaL_newstate())) {
		cerr << "failed open lua" << endl;
		return -1;
	}

	luaL_openlibs(L);
	lua_register(L, "average", average);

	lua_pushnumber(L, 12);
	cout << lua_gettop(L) << endl;

	lua_pushnumber(L, 13);
	cout << lua_gettop(L) << endl;

	lua_pushnumber(L, 14);
	cout << lua_gettop(L) << endl;

	int n = lua_tonumber(L, -1);
	cout << lua_gettop(L) << endl;


	lua_createtable(L, 0, 0);
	cout << "top value " << lua_tonumber(L, -1) << endl;
	lua_pushnumber(L, 13);
	cout << "top value " << lua_tonumber(L, -1) << endl;
	lua_setfield(L, -2, "hash");
	
	cout << "top value " << lua_tonumber(L, -1) << endl;
	cout << "top value " << lua_tonumber(L, -2) << endl;


	if (luaL_dofile(L, "C:\\Users\\riseK\\mine\\program\\MeiVision\\Test\\lua_script_test\\lua_test.lua")) {
		cerr << "failed open lua test file" << endl;
		return -1;
	}


	lua_close(L);
	return 0;
}

