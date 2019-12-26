#include "luawrapper.h"

namespace Lua {
	//LuaScript::LuaScript(SourceMnger* amng, QStatusBar* statusBar, QObject* parent)
	//	:QThread(parent), mng(amng), mainstatusBar(statusBar) {
	//	finished = true;
	//	StaticSender::init_sender(this);
	//	const ConsoleSender* console_sender = StaticSender::get_sender();
	//	connect(console_sender, &ConsoleSender::sig_stdout, this, &LuaScript::sig_stdoutmsg);
	//}

	LuaScript::LuaScript(SourceMnger* amng, QObject* parent)
		:QThread(parent), mng(amng) {
		StaticSender::init_sender(this);
		const ConsoleSender* console_sender = StaticSender::get_sender();
		connect(console_sender, &ConsoleSender::deep_sig_stdout, this, &LuaScript::sig_stdoutmsg);
	}


	LuaScript::~LuaScript() {
		wait();
	}

	int LuaScript::check_ok(lua_State* L, int status) {
		if (status != LUA_OK) {
			//some error here
			const char* msg = lua_tostring(L, -1);
			lua_pop(L, -1);
			emit sig_erroutmsg(QString(msg));
		}
		return status;
	}

	void LuaScript::set_script_run(const string& str) {
		if (isRunning()) return;  // last script has not finished
		this->script_text = str;
		mng->clear(); // 每一次脚本运行之后清理脚本所不能释放的资源， 例如图片
		start();
	}

	int LuaScript::lua_sleep(lua_State* L) {
		int x = luaL_checkinteger(L, -1);
		this->msleep(x);
		return 0;
	}

	void LuaScript::register_sleep(lua_State* L) {
		*static_cast<LuaScript**>(lua_getextraspace(L)) = this;
		lua_register(L, "sleep", &dispatch<&LuaScript::lua_sleep>);
	}


	void LuaScript::run() {
		QElapsedTimer timer;
		timer.start();
		//for multi thead
		run_script();  // invoke member function

		int time_used = timer.elapsed() / 1000;
		QString msg = "script used time: " + QString::number(time_used) + "s " + QString::number(timer.elapsed()) + "ms";
		//mainstatusBar->showMessage(msg, 8000);
		emit sig_took_time(msg, 8000);
		return;
	}

	void LuaScript::run_script() {
		lua_State* L;
		if (nullptr == (L = luaL_newstate())) {
			//cerr << "failed open lua" << endl;
			return;
		}
		//set vison moudle source manager
		MeiImg::imgMger = mng;

		luaL_openlibs(L);
		register_sleep(L);
		lua_register(L, "init", MeiImg::init);  // in lua return a table
		int status = luaL_dostring(L, script_text.c_str());
		int result = lua_toboolean(L, -1);
		check_ok(L, status);
		lua_close(L);
	}

}