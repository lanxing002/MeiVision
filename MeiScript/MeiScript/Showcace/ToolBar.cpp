#include "ToolBar.h"

PaintToolBar::PaintToolBar(QWidget* parent)
	: QToolBar(parent) 
{
	setIconSize(QSize(32, 32));

	painterAction = new QAction(this);
	painterAction->setIcon(QIcon(":/btn_icon/Resources/Painter.png"));
	colorPickActionAction = new QAction(this);
	colorPickActionAction->setIcon(QIcon(":/btn_icon/Resources/ColorPicker.png"));
	palletAction = new QAction(this);
	palletAction->setIcon(QIcon(":/btn_icon/Resources/pallet.png"));

	addAction(painterAction);
	addAction(colorPickActionAction);
	addAction(palletAction);
}

PaintToolBar::~PaintToolBar() {}


ScriptToolBar::ScriptToolBar(QWidget* parent)
	: QToolBar(parent) {
	setIconSize(QSize(32, 32));

	runAction = new QAction(this);
	runAction->setIcon(QIcon(":/btn_icon/Resources/play.png"));
	stopAction = new QAction(this);
	stopAction->setIcon(QIcon(":/btn_icon/Resources/stop.png"));


	addAction(runAction);
	addAction(stopAction);
}

ScriptToolBar::~ScriptToolBar() {}