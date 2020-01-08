#pragma once
#include "SourceMnger.h"
#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
#include <QResizeEvent>
#include <QScreen>
#include <QSize>
#include <QLabel.h>

class ShowWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	ShowWidget(QWidget* parent);
	~ShowWidget();

	void setMng(SourceMnger* mng);
	void setPixelShowLabel(QLabel* l);

public slots:
	void animate();
	void setId(int t);
	void show_test_img(QImage img);

signals:
	void sig_resize(QSize size);
	void sig_current_pixel(QString c, int timeout);

protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent* event);
	//void resizeEvent(QResizeEvent* event);

private:
	QColor pickPixel(const QPoint &p);

	SourceMnger* mng;
	int id;
	QImage bakImg;
	QPixmap m_tile;
	QLabel* pixle_msg_label;
};
