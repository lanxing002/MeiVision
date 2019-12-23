#pragma once

#include <QPlainTextEdit>
#include <QDebug>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class ConsoleWindow : public QPlainTextEdit
{
	Q_OBJECT

public:
	ConsoleWindow(QWidget* parent);
	~ConsoleWindow();

	void set_text_buffer(stringstream* buffer) { this->text_buffer = buffer; };
	void clear_text_buffer() { this->text_buffer = nullptr; };

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	stringstream* text_buffer;
};
