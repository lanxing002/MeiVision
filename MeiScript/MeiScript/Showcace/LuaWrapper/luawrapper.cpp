#include "luawrapper.h"

namespace Lua {
	LuaScript::LuaScript(QObject* parent, SourceMnger* amng)
		:QThread(parent), mng(amng) {
		finished = true;
	}

	LuaScript::~LuaScript() {
		wait();
	}

	int LuaScript::check_ok(lua_State* L, int status) {
		if (status != LUA_OK) {
			//some error here
			const char* msg = lua_tostring(L, -1);
			lua_pop(L, -1);
			emit sig_outmsg(string(msg));
		}
		return status;
	}

	void LuaScript::run_script(const string& str) {
		if (!finished) return;  // last script has finished
		this->script_text = str;

		run();
	}

	void LuaScript::run() {
		//for multi thead
		mutex.lock();
		finished = false;
		mutex.unlock();

		lua_State* L;
		if (nullptr == (L = luaL_newstate())) {
			//cerr << "failed open lua" << endl;
			return;
		}

		//set vison moudle source manager
		MeiImg::imgMger = mng;

		luaL_openlibs(L);
		lua_register(L, "init", MeiImg::init);  // in lua return a table
		int status = luaL_dostring(L, script_text.c_str());
		int result = lua_toboolean(L, -1);
		check_ok(L, status);
		lua_close(L);
		
		//destory source manager

		mutex.lock();
		finished = true;
		mutex.unlock();

		return;
	}

}