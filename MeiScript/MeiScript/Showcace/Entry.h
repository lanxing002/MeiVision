#pragma once

#include <QtWidgets/QMainWindow>
#include <QStatusBar>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_Entry.h"
#include "LuaWrapper/luawrapper.h"
#include "HighLighter.h"
#include <QDebug>
#include <QColorDialog>
#include <ToolBar.h>

class Entry : public QMainWindow
{
	Q_OBJECT

public:
	Entry(QWidget *parent = Q_NULLPTR);

	void createStatusBar();
	void setupToolBar();

public slots:
	void run_script();
	void open();
	void open_file(const QString& file_name);
	bool save();
	bool saveAs();
	bool save_file(const QString& file_name);
	void reset_show_img(size_t id);
	void update_statusbar_msg(const QString& msg, int time);

	//工具栏slots
	void pick_color();


	void receive_test(const string& str);

private:
	Ui::EntryClass ui;
	stringstream outbuffer;
	Lua::LuaScript* run_thread;
	SourceMnger* mng;
	QString cur_file;
	bool isUntitled;

	//工具栏 属性
	QColor pen_color;

	QToolBar* paintTool;
	QToolBar* scriptTool;

};
