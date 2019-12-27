#include "ConsoleWindow.h"
#include <QThread>

ConsoleWindow::ConsoleWindow(QWidget* parent)
	: QPlainTextEdit(parent)
{
}

ConsoleWindow::~ConsoleWindow()
{
}

void ConsoleWindow::update_log(const QString& str) {
	this->insertPlainText(str);
	update();
}

void ConsoleWindow::update_error_log(const QString& str) {
	stringstream ss(str.toStdString());
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



DockConsole::DockConsole(const QString &name, QMainWindow *parent)
	: QDockWidget(name, (QWidget*)parent)
{
	this->console = new QPlainTextEdit(this);
	setWidget(console);
	setFeatures(QDockWidget::DockWidgetClosable ); // 不能让该窗口移动，不然标签化的脚本编辑器会有错误
	this->console->setReadOnly(true);
}
DockConsole::~DockConsole() {}

void DockConsole::update_log(const QString& str) {
	this->console->insertPlainText(str);
	update();
}

void DockConsole::update_error_log(const QString& str) {
	stringstream ss(str.toStdString());
	string line;
	QString html_text;
	html_text += "<font color=\"red\">";
	while (getline(ss, line)) {
		html_text += QString::fromStdString(line);
	}
	html_text += "</font>";
	this->console->appendHtml(html_text);
	update();
}

void DockConsole::clear() {
	this->console->clear();
	update();
}
void DockConsole::insert_text(const QString& text) {
	this->console->insertPlainText(text);
	update();
}