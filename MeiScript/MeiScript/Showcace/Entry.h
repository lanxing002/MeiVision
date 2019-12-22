#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include "ui_Entry.h"
#include "LuaWrapper/luawrapper.h"

class Entry : public QMainWindow
{
	Q_OBJECT

public:
	Entry(QWidget *parent = Q_NULLPTR);


public slots:
	void run_script();

private:
	Ui::EntryClass ui;
};
