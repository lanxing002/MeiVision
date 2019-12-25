#pragma once
#include <QImage>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include "VisionMoudle/MeiImg.h"
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
		LuaScript(QObject* parent, SourceMnger* mng);
		~LuaScript();

		int check_ok(lua_State* L, int status);
		void run_script(const string& str);

	signals:
		void sig_outmsg(string str);

	protected:
		void run();

	private:
		bool finished;
		SourceMnger* mng;
		QMutex mutex;
		string script_text;

	};
	
}