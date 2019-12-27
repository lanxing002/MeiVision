#pragma once

#include <QToolBar>

class PaintToolBar : public QToolBar
{
	Q_OBJECT

public:
	PaintToolBar(QWidget* parent);
	~PaintToolBar();

public:
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

public:
	QAction* runAction;
	QAction* stopAction;
};
