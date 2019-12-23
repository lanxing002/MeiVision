#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow(QWidget*parent)
	: QPlainTextEdit(parent), text_buffer(nullptr)
{
}

ConsoleWindow::~ConsoleWindow()
{
}


void ConsoleWindow::paintEvent(QPaintEvent* event)  {
	if (text_buffer != nullptr) {
		//text_buffer->clear();
		
		string line;
		while (getline(*text_buffer, line)) {
			qDebug() << QString::fromStdString(line) << "\n";
			this->insertPlainText(QString::fromStdString(line) + "\n");
		}
	}
	QPlainTextEdit::paintEvent(event);
}