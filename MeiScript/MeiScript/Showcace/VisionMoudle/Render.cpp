#include "Render.h"

SourceMnger* Render::imgMger = NULL;
QPoint Render::translate_p = QPoint(0, 0);
QColor Render::fill_c1 = Qt::cyan;
QColor Render::fill_c2;
int Render::penWidth = 3;
QColor Render::pen_color = Qt::darkRed;
int Render::rotationAngle = 0;

size_t get_id(lua_State* L) {
	//c
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_getfield(L, 1, "id");
	size_t id = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return id;
}

void Render::init_painter(QPainter& painter) {
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Render::fill_c1);
	painter.setPen(QPen(pen_color, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

//args : {{id}, {color = {},width, rotate, translate={x, y} fillcolor={}}}
int Render::set_pen(lua_State* L) {
	luaL_checktype(L, -1, LUA_TTABLE); // arg table

	lua_getfield(L, -1, "width");
	Render::penWidth = lua_isnil(L, -1) == 1 ? Render::penWidth : lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, -1, "rotate");
	Render::rotationAngle = lua_isnil(L, -1) == 1 ? Render::rotationAngle : lua_tonumber(L, -1);
	lua_pop(L, 1);

	//get_translate pointe
	lua_getfield(L, -1, "translate");
	if (lua_isnil(L, -1) != 1) {  // color table is not nil
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_pushnil(L);  /* first key */
		//this is a table in a table, this section, -1 index is value
		int point_v[2]; int i = 0;
		// sub table index = 1
		while (lua_next(L, -2) != 0) {
			/* uses 'key' (at index -2) and 'value' (at index -1) */
			//printf("%s - %s\n",
			int t = luaL_checkinteger(L, -1);
			luaL_argcheck(L, t >= 0, 1, "line position out of range");
			point_v[i++] = t;
			/* removes 'value'; keeps 'key' for next iteration */
			lua_pop(L, 1);
		}

		Render::translate_p = QPoint(point_v[0], point_v[1]);
	}
	lua_pop(L, 1);

	//get pen color
	lua_getfield(L, -1, "color");
	if (lua_isnil(L, -1) != 1) {  // color table is not nil
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_getfield(L, -1, "r"); // push red to statck
		int r = lua_isnil(L, -1) == 1 ? pen_color.red() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_getfield(L, -1, "g"); // push red to statck
		int g = lua_isnil(L, -1) == 1 ? pen_color.green() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_getfield(L, -1, "b"); // push red to statck
		int b = lua_isnil(L, -1) == 1 ? pen_color.blue() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		luaL_argcheck(L, r >= 0 && g >= 0 && b >= 0, 3, "pen color out of range");
		luaL_argcheck(L, r <= 255 && g <= 255 && b <= 255, 3, "pen color out of range");
		Render::pen_color = QColor(r,g,b);
	}
	lua_pop(L, 1);

	//get fill color
	lua_getfield(L, -1, "fillcolor");
	if (lua_isnil(L, -1) != 1) {  // color table is not nil
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_getfield(L, -1, "r"); // push red to statck
		int r = lua_isnil(L, -1) == 1 ? fill_c1.red() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_getfield(L, -1, "g"); // push red to statck
		int g = lua_isnil(L, -1) == 1 ? fill_c1.green() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_getfield(L, -1, "b"); // push red to statck
		int b = lua_isnil(L, -1) == 1 ? fill_c1.blue() : lua_tonumber(L, -1);
		lua_pop(L, 1);
		luaL_argcheck(L, r >= 0 && g >= 0 && b >= 0, 3, "fill color out of range");
		luaL_argcheck(L, r <= 255 && g <= 255 && b <= 255, 3, "fill color out of range");
		Render::fill_c1 = QColor(r, g, b);
	}
	lua_pop(L, 1);

	return 0;
}

//input args: ({id}, x, y, text->string)
int Render::render_text(lua_State* L){
	QImage* img = imgMger->getImg(get_id(L));

	//extra args from lua script
	const char* text = luaL_checkstring(L, -1);
	int y = luaL_checkinteger(L, -2);
	int x = luaL_checkinteger(L, -3);
	luaL_argcheck(L, x >= 0 && y >= 0, 2, "color position out of range");

	QPainter painter(img);
	init_painter(painter);
	painter.translate(translate_p);
	painter.rotate(Render::rotationAngle);
	painter.drawText(x, y, QString(text));
	return 0;
}

//args:  {{id}, x, y, id}
int Render::render_Img(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));
	int id = luaL_checkinteger(L, -1);
	int y = luaL_checkinteger(L, -2);
	int x = luaL_checkinteger(L, -3);
	luaL_argcheck(L, x >= 0 && y >= 0, 2, "color position out of range");
	QImage* img_draw = imgMger->getImg(id);
	luaL_argcheck(L, img_draw != NULL,1, "error drawed image id" );

	QPainter painter(img);
	painter.translate(translate_p);
	painter.rotate(Render::rotationAngle);
	if(img_draw != NULL) painter.drawImage(x, y, *img_draw);
	return 0;
}
//args: ({id}, x1, y1, x2, y2)
int Render::render_line(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));

	int y2 = luaL_checkinteger(L, -1);
	int x2 = luaL_checkinteger(L, -2);
	int y1 = luaL_checkinteger(L, -3);
	int x1 = luaL_checkinteger(L, -4);

	luaL_argcheck(L, x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0 
		, 4, "line position out of range");

	//render line code
	QPainter painter(img);
	init_painter(painter);
	painter.translate(translate_p);
	painter.rotate(rotationAngle);
	painter.drawLine(x1, y1, x2, y2);
	return 0;
}

void getPoint(lua_State* L, vector<QPointF>& points) {
	luaL_checktype(L, -1, LUA_TTABLE);
	lua_pushnil(L);  /* first key */
	//this is a table in a table, this section, -1 index is value
	int point_v[2]; int i = 0;
	// sub table index = 1
	while (lua_next(L, -2) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		//printf("%s - %s\n",
		int t = luaL_checkinteger(L, -1);
		luaL_argcheck(L, t>=0, 1, "line position out of range");
		point_v[i++] = t;
		if (i == 2) {
			points.push_back(QPointF(point_v[0], point_v[1]));
			i = 0;
		}
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}
}

//args: ({id}, {{},{}, {}, {}, {}})
int Render::render_polygon(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));

	luaL_checktype(L, -1, LUA_TTABLE); // points table

	vector<QPointF> points;

	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		getPoint(L, points);
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}

	QPainter painter(img);
	init_painter(painter);
	painter.translate(translate_p);
	painter.rotate(Render::rotationAngle);
	painter.drawPolyline(points.data(), points.size());
	return 0;
}