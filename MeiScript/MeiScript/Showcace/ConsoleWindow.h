#pragma once

#include <QPlainTextEdit>
#include <QDebug>
#include <QDockWidget>
#include <sstream>
#include <string>
using namespace std;

class ConsoleWindow : public QPlainTextEdit
{
	Q_OBJECT

public:
	ConsoleWindow(QWidget* parent);
	~ConsoleWindow();

public slots:
	void update_log(const QString& str);
	void update_error_log(const QString& str);
};

class DockConsole : public QDockWidget
{
	Q_OBJECT

public:
	explicit DockConsole(const QString& colorName, QMainWindow* parent = nullptr);
	~DockConsole();

public slots:
	void update_log(const QString& str);
	void update_error_log(const QString& str);

	void clear();
	void insert_text(const QString& text);

private:
	QPlainTextEdit* console;
};
