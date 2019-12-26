#pragma once
#include "SourceMnger.h"
#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
class ShowWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	ShowWidget(QWidget* parent);
	~ShowWidget();

	void setMng(SourceMnger* mng);

public slots:
	void animate();
	void setId(int t);
	void show_test_img(QImage img);

protected:
	void paintEvent(QPaintEvent *event);

private:
	SourceMnger* mng;
	int id;
	QImage bakImg;
};
