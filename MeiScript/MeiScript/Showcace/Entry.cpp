#include "Entry.h"

Entry::Entry(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.run_btn, &QPushButton::clicked, this, &Entry::run_script);
}


void Entry::run_script() {
	QString text = ui.script_text->toPlainText();
	Lua::Lua_script::run_script(text.toStdString());
}


