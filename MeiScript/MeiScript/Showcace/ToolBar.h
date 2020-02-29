#pragma once
#include <QComboBox>
#include <QToolBar>

class PaintToolBar : public QToolBar
{
	Q_OBJECT

public:
	PaintToolBar(QWidget* parent = nullptr);
	~PaintToolBar();

public:
	QAction* painterAction;
	QAction* colorPickActionAction;
	QAction* palletAction;
	QAction* zoominAction;
	QAction* zoomoutAction;
	QAction* resetAction;
};


class ScriptToolBar : public QToolBar
{
	Q_OBJECT

public:
	ScriptToolBar(QWidget* parent = nullptr);
	~ScriptToolBar();

public:
	QAction* runAction;
	QAction* stopAction;
	QAction* decFontAction;
	QAction* incFontAction;
	QAction* commentAction;
};
