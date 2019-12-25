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

public slots:
	void update_log(std::string str);
	void update_error_log(std::string str);
};
