#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow(QWidget* parent)
	: QPlainTextEdit(parent)
{
}

ConsoleWindow::~ConsoleWindow()
{
}

void ConsoleWindow::update_log(std::string str) {
	this->insertPlainText(QString::fromStdString(str));
	update();
}

void ConsoleWindow::update_error_log(std::string str) {
	stringstream ss(str);
	string line;
	QString html_text;
	html_text += "<font color=\"red\">";
	while (getline(ss, line)) {
		html_text += QString::fromStdString(line) ;
	}
	html_text += "</font>";
	this->appendHtml(html_text);
	update();
}
