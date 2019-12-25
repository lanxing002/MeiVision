#pragma once

#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <QAction>
#include <QSyntaxHighlighter>

class LineNumberArea;

class ScriptEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	ScriptEditor(QWidget* parent);
	~ScriptEditor();

	int cnt_area_width();
	void copy_line();

protected:
	void resizeEvent(QResizeEvent* event) override;
	//void keyPressEvent(QKeyEvent* event) override;
	//void keyReleaseEvent(QKeyEvent* event) override;

public slots:
	void update_cnt_area(const QRect &rect, int dy);
	void update_cnt_area_width(int);
	void cnt_area_paint_event(QPaintEvent* e);
	void highlight_current_line();

private:
	QWidget* cnt_area;
	bool ctrl_press;
	QSet<int> pressedKeys;
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