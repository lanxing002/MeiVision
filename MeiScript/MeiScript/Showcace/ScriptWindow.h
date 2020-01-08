#pragma once

#include "HighLighter.h"

#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QAction>
#include <QSyntaxHighlighter>
#include <QDockWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QSet>


class LineNumberArea;
class DockEditor;

class ScriptEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	ScriptEditor(QWidget* parent);
	~ScriptEditor();

	int cnt_area_width();


protected:
	void resizeEvent(QResizeEvent* event) override;

public slots:
	void update_cnt_area(const QRect &rect, int dy);
	void update_cnt_area_width(int);
	void cnt_area_paint_event(QPaintEvent* e);
	void highlight_current_line();

	void copy_line();
	void comment_line();

private:
	QWidget* cnt_area;
};


class LineNumberArea : public QWidget {
public:
	LineNumberArea(ScriptEditor* editor) : QWidget(editor) {
		this->editor = editor;
	}

	QSize sizeHint() const Q_DECL_OVERRIDE {
		return QSize(editor->cnt_area_width(), 0);
	}

protected:
	void paintEvent(QPaintEvent* event) override {
		editor->cnt_area_paint_event(event);
	}

private:
	ScriptEditor* editor;
};

class DockEditor : public QDockWidget
{
	Q_OBJECT
public:
static int new_count;
static QSet<QString> openedFile;

public:
	explicit DockEditor(const QString& , QMainWindow* parent = nullptr, QString file_name = "");
	~DockEditor();

//warp eidt signal
signals:
	void textChanged();

public slots:
	void setChanged();
	void setSaved();
	bool save();

	QString text();
	void zoomIn(int range = 1) { editor->zoomIn(range); }
	void zoomOut(int range = 1) { editor->zoomOut(range); }
	void comment_line() { this->editor->comment_line(); }
	void openFile();

private:
	bool saveAs();
	bool saveFile(const QString& tmp_name);
	
	ScriptEditor* editor;
	QString edit_title;
	QString file_path_name;
 
	//一个文件只能在一个窗口之中打开
};
