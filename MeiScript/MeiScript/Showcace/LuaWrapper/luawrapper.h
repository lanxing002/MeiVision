#ifndef LuaWrapper_H
#define LuaWrapper_H

#include <QImage>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QElapsedTimer>
#include <QStatusBar>
#include "VisionMoudle/MeiImg.h"
#include "lua/redirectCPP.h"

using namespace std;

extern "C" {
#include "../lua/redirect.h"
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}


namespace Lua {

	class LuaScript : public QThread {
		Q_OBJECT
	public:
		LuaScript(SourceMnger* mng, QStatusBar* statusBar, QObject* parent = 0);
		~LuaScript();

		int check_ok(lua_State* L, int status);
		void set_script_run(const string& str);
		void run_script();
		void register_sleep(lua_State* L);
		int lua_sleep(lua_State* L);
		bool isFinished();

	signals:
		void sig_erroutmsg(const string& str);
		void sig_stdoutmsg(const string& str);

	protected:
		void run();

	private:
		bool finished;
		SourceMnger* mng;
		QMutex mutex;
		string script_text;
		QStatusBar* mainstatusBar;
	};

	typedef int (LuaScript::* mem_func)(lua_State* L); // 重定义类内函数指针

	template<mem_func func>
	int dispatch(lua_State* L) {
		LuaScript* ptr = *(static_cast<LuaScript**>(lua_getextraspace(L)));  // get pointer which init the l_State*;
		return ((*ptr).*func)(L);
	}

}

#endif