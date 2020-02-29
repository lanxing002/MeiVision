#include "MeiImg.h"

SourceMnger* MeiImg::imgMger = nullptr;

//args (void) return a table
int MeiImg::init(lua_State* L) {
	create_mat_metatable(L);
	lua_createtable(L, 0, 0);
	lua_pushvalue(L, 1);
	lua_setmetatable(L, -2);

	return 1;
}

void MeiImg::init_mat_table(lua_State* L, size_t id) {
	lua_pushnumber(L, id);
	lua_setfield(L, 1, "id");

	QImage* img = imgMger->getImg(id);
	lua_pushnumber(L, img->width());
	lua_setfield(L, 1, "width");
	lua_pushnumber(L, img->height());
	lua_setfield(L, 1, "height");
	lua_pushnumber(L, img->depth());
	lua_setfield(L, 1, "depth");
}

//args ({}, filename)
int MeiImg::open_mat(lua_State* L) {
	//a table function, first arg is a table
	//luaL_checktype(L, 1, LUA_TN);
	luaL_checktype(L, 1, LUA_TTABLE);
	string str(lua_tostring(L, 2));
	lua_pop(L, 1); // pop filename
	size_t id = imgMger->openImg(str);
	init_mat_table(L, id);

	//push bool and return 1
	return 1;
}

//args ({id})
int MeiImg::show_mat(lua_State* L) {  //connect with qt gui 
	size_t id = get_id(L);
	imgMger->showImg(id);
	return 0;
}

//args {r, b, g} = ({id}, x, y)
int MeiImg::at(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));
	int y = lua_tonumber(L, -1);
	int x = lua_tonumber(L, -2);
	lua_pop(L, 2); // pop x, y position
	QColor c = img->pixelColor(x, y);

	lua_createtable(L, 0, 0); // create color table

	lua_pushnumber(L, c.red());
	lua_pushnumber(L, c.green());
	lua_pushnumber(L, c.blue());
	//set field value in color table

	lua_setfield(L, 2, "b");
	lua_setfield(L, 2, "g");
	lua_setfield(L, 2, "r");

	return 1; // return a table
}

//args({id}, x， y, color = {})
int MeiImg::write(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));

	int y = luaL_checkinteger(L, -2);
	int x = luaL_checkinteger(L, -3);
	QColor c = img->pixelColor(x, y);
	luaL_argcheck(L, x >= 0 && y >= 0, 2, "color position out of range");
	
	luaL_checktype(L, -1, LUA_TTABLE);

	lua_getfield(L, -1, "r"); // push red to statck
	
	lua_getfield(L, -2, "g");
	lua_getfield(L, -3, "b");
	 
	int b = lua_isnil(L, -1) == 1 ? c.blue() :  lua_tonumber(L, -1);
	int g = lua_isnil(L, -2) == 1 ? c.green() : lua_tonumber(L, -2);
	int r = lua_isnil(L, -3) == 1 ? c.red() : lua_tonumber(L, -3);
	
	img->setPixelColor(x, y, {r, g, b});
	lua_pushboolean(L, true);
	return 1;
}

//args({id}, x， y, color = {})
int MeiImg::size(lua_State* L) {
	QImage* img = imgMger->getImg(get_id(L));
	lua_pushnumber(L, img->width());
	lua_setfield(L, 1, "width");
	lua_pushnumber(L, img->height());
	lua_setfield(L, 1, "height");
	lua_pushnumber(L, img->depth());
	lua_setfield(L, 1, "depth");
	return 0;
}

//args bool =   {{id}, string}
int MeiImg::save(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	string str(lua_tostring(L, 2));

	QImage* img = imgMger->getImg(get_id(L));
	bool result = img->save(QString::fromStdString(str), nullptr, 100);

	lua_pushboolean(L, result);
	return 1;
}

//args {}={{id}} 返回该表的拷贝
int MeiImg::grayscale(lua_State* L) {
	size_t id = imgMger->grayImg(get_id(L));
	luaL_checktype(L, 1, LUA_TTABLE);  // first is input lua table {id, width, height, depth, __index = {}}
	lua_createtable(L, 0, 0); // create gray img table
	if (lua_getmetatable(L, 1) != 0) {
		lua_setmetatable(L, 2);
	}
	lua_remove(L, 1); // remove source table 

	init_mat_table(L, id);

	return 1;
}

size_t MeiImg::get_id(lua_State* L) {
	//c
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_getfield(L, 1, "id");
	size_t id = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return id;
}

void MeiImg::create_mat_metatable(lua_State* L) {
	lua_createtable(L, 0, 1); //create metateable for a new table
	lua_createtable(L, 0, 4); // create __index table for basic function

	//render function
	lua_pushcfunction(L, Render::set_pen);
	lua_pushcfunction(L, Render::render_text);
	lua_pushcfunction(L, Render::render_Img);
	lua_pushcfunction(L, Render::render_line);
	lua_pushcfunction(L, Render::render_polygon);


	//img process fucntion
	lua_pushcfunction(L, MeiImg::grayscale);
	lua_pushcfunction(L, MeiImg::save);
	lua_pushcfunction(L, MeiImg::write);
	lua_pushcfunction(L, MeiImg::at);
	lua_pushcfunction(L, MeiImg::show_mat);
	lua_pushcfunction(L, MeiImg::open_mat);
	lua_pushcfunction(L, MeiImg::size);

	// register all function 
	lua_setfield(L, 2, "size");
	lua_setfield(L, 2, "open");
	lua_setfield(L, 2, "show");
	lua_setfield(L, 2, "at");
	lua_setfield(L, 2, "write");
	lua_setfield(L, 2, "save");
	lua_setfield(L, 2, "grayscale");

	lua_setfield(L, 2, "render_polygon");
	lua_setfield(L, 2, "render_line");
	lua_setfield(L, 2, "render_img");
	lua_setfield(L, 2, "render_text");
	lua_setfield(L, 2, "set_pen");

	lua_setfield(L, 1, "__index");

}
