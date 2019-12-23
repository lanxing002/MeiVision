#include "Entry.h"

Entry::Entry(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	connect(ui.run_btn, &QPushButton::clicked, this, &Entry::run_script);
}


void Entry::run_script() {
	outbuffer = stringstream("just for test \n");
	outbuffer << "a line \n";
	ui.console_text->set_text_buffer(&outbuffer);

	outbuffer << "run script:::: \n";
	QString text = ui.script_text->toPlainText();
	//Lua::Lua_script::run_script(text.toStdString(), outbuffer);
	//ui.console_text->clear_text_buffer();
}


