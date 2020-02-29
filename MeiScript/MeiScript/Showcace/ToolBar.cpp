#include "ToolBar.h"

PaintToolBar::PaintToolBar(QWidget* parent)
	: QToolBar(parent) 
{
	setIconSize(QSize(28, 28));
	setWindowTitle(QString::fromLocal8Bit("绘图工具"));

	painterAction = new QAction(this);
	painterAction->setIcon(QIcon(":/btn_icon/Resources/Painter.png"));
	colorPickActionAction = new QAction(this);
	colorPickActionAction->setIcon(QIcon(":/btn_icon/Resources/ColorPicker.png"));
	palletAction = new QAction(this);
	palletAction->setIcon(QIcon(":/btn_icon/Resources/pallet.png"));


	zoominAction = new QAction(this);;
	zoominAction->setIcon(QIcon(":/btn_icon/Resources/zoomin.png"));
	zoomoutAction = new QAction(this);;
	zoomoutAction->setIcon(QIcon(":/btn_icon/Resources/zoomout.png"));
	resetAction = new QAction(this);
	resetAction->setIcon(QIcon(":/btn_icon/Resources/reset.png"));



	addAction(painterAction);
	addAction(colorPickActionAction);
	addAction(palletAction);
	addAction(zoominAction);
	addAction(zoomoutAction);
	addAction(resetAction);
}

PaintToolBar::~PaintToolBar() {}


ScriptToolBar::ScriptToolBar(QWidget* parent)
	: QToolBar(parent) {
	setIconSize(QSize(28, 28));
	setWindowTitle(QString::fromLocal8Bit("脚本工具"));

	runAction = new QAction(this);
	runAction->setIcon(QIcon(":/btn_icon/Resources/play.png"));
	runAction->setShortcut(tr("f5"));
	stopAction = new QAction(this);
	stopAction->setIcon(QIcon(":/btn_icon/Resources/stop.png"));
	stopAction->setShortcut(tr("shift+f5"));
	decFontAction = new QAction(this);
	decFontAction->setIcon(QIcon(":/btn_icon/Resources/DecFont.png"));
	decFontAction->setShortcut(QKeySequence::ZoomIn);
	incFontAction = new QAction(this);
	incFontAction->setIcon(QIcon(":/btn_icon/Resources/IncFont.png"));
	incFontAction->setShortcut(QKeySequence::ZoomOut);
	commentAction = new QAction(this);
	commentAction->setIcon(QIcon(":/btn_icon/Resources/comment.png"));
	commentAction->setShortcut(tr("ctrl+/"));

	addAction(runAction);
	addAction(stopAction);
	addAction(incFontAction);
	addAction(decFontAction);
	addAction(commentAction);

	stopAction->setDisabled(true);
}

ScriptToolBar::~ScriptToolBar() {}