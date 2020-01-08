#pragma once

#include <QtWidgets/QMainWindow>
#include <QStatusBar>
#include <QSettings>
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
#include <QScrollArea>
#include <QColorDialog>
#include <QLabel>
#include <QComboBox>
#include "ToolBar.h"

class Entry : public QMainWindow
{
	Q_OBJECT

public:
	Entry(QWidget *parent = Q_NULLPTR);

	void setupUI();
	void setupToolBar();
	void setupMenuBar();
	void setupDockWidget();
	void setupCenterWidget();
	void setupStatusBar();
	void writeSettings(QString key = "Default");
	void readSettings(QString key = "Default");

	void createStatusBar();


public slots:
	//�ű�����slots
	void run_script();
	void stop_script();

	//���������Ϣslots
	void reset_show_img(size_t id);
	void update_statusbar_msg(const QString& msg, int time = 0);
	
	//�ű��༭����slots
	void create_script();
	void open();
	bool save();
	void comment_line() { this->activeEditor->comment_line(); }
	//void resetEditorFont();
	void editorZoomIn(int range = 1) { activeEditor->zoomIn(1); }
	void editorZoomOut(int range = 1) { activeEditor->zoomOut(1); }

	void set_active_editor(QDockWidget* dockWidget);
	void dockWidget_topLevelChanged(bool );
	void saveLayout();
	void loadLayout();
	void wirteSettings_slot() { writeSettings(); }
	void readSettings_slot() { readSettings(); }

	//������slots
	void pick_color();
	void resize_toolBar(QSize size);
	void set_btn_runstatu();
	void set_btn_stopstatu();

protected:
	void closeEvent(QCloseEvent* event);

private:
	Lua::LuaScript* run_thread;
	SourceMnger* mng;

	//����
	ShowWidget* center;
	//�ű��༭��
	QList<DockEditor*> editors;
	DockEditor* activeEditor;
	QTabWidget* tabEditors;
	//����̨���
	DockConsole* console;

	//������ ����
	PaintToolBar* paintTool;
	ScriptToolBar* scriptTool;
	QColor pen_color;
	QScrollArea* scrollArea;
	
	//
	QLabel* pixelMsg;
	QComboBox* zoomBox;
};
