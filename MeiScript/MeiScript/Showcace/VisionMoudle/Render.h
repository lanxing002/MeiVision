#pragma once
#include "../SourceMnger.h"
#include <QImage>
#include <QPainter>

extern "C" {
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}

#include <QImage>

//static function fro lua
//static function for lua
struct Render
{
	//methods
	//void render_text(const QPoint& position, const QString& text);
	
	static int set_pen(lua_State* L);
	static int render_text(lua_State* L);
	static int render_Img(lua_State* L);
	static int render_line(lua_State* L);
	static int render_polygon(lua_State* L);

	//fields
	static SourceMnger* imgMger;
	static QPoint translate_p;
	static QColor fill_c1;
	static QColor fill_c2;
	static int penWidth;
	static QColor pen_color;
	static int rotationAngle;

	//¸¨Öú·½·¨
private:
	static void init_painter(QPainter& painter);
};