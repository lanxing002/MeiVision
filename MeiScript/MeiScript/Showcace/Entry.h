#pragma once

#include <QtWidgets/QMainWindow>
#include <QStatusBar>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "ShowWidget.h"
#include "ScriptWindow.h"
#include "ConsoleWindow.h"
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

	void setupUI();
	void createStatusBar();
	void setupToolBar();
	void setupMenuBar();
	void setupDockWidget();
	void setupCenterWidget();

public slots:
	void run_script();
	void stop_script();
	void open();
	void open_file(const QString& file_name);
	bool save();
	//bool saveAs();
	//bool save_file(const QString& file_name);
	void reset_show_img(size_t id);
	void update_statusbar_msg(const QString& msg, int time);
	void create_script();

	void set_active_editor(QDockWidget* dockWidget);
	void dockWidget_topLevelChanged(bool );

	//工具栏slots
	void pick_color();

	void receive_test(const string& str);

private:
	stringstream outbuffer;
	Lua::LuaScript* run_thread;
	SourceMnger* mng;
	QString cur_file;
	bool isUntitled;

	//中心
	ShowWidget* center;
	//脚本编辑器
	QList<DockEditor*> editors;
	DockEditor* activeEditor;
	QTabWidget* tabEditors;
	//控制台输出
	DockConsole* console;

	//工具栏 属性
	PaintToolBar* paintTool;
	ScriptToolBar* scriptTool;
	QColor pen_color;

	//菜单栏
};
