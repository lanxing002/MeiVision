#include "Entry.h"
#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QStyleFactory>
#include "Test/ReadTest.h"

#include "LuaWrapper/luawrapper.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));
	Entry w;
	//w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	w.show();

	//set font
	QFont font("YaHei Consolas Hybrid", 10);
	QApplication::setFont(font);
	
	return a.exec();
}
