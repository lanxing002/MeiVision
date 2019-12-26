#pragma once

#include <QToolBar>

class PaintToolBar : public QToolBar
{
	Q_OBJECT

public:
	PaintToolBar(QWidget* parent);
	~PaintToolBar();

private:
	QAction* painterAction;
	QAction* colorPickActionAction;
	QAction* palletAction;
};


class ScriptToolBar : public QToolBar
{
	Q_OBJECT

public:
	ScriptToolBar(QWidget* parent);
	~ScriptToolBar();

private:
	QAction* runAction;
	QAction* stopAction;
};
