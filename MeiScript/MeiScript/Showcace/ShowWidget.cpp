#include "ShowWidget.h"

ShowWidget::ShowWidget(QWidget* parent)
	: QOpenGLWidget(parent), id(0)
{
	//初始化透明化界面
	m_tile = QPixmap(96, 96);
	m_tile.fill(Qt::white);
	QPainter pt(&m_tile);
	QColor color(230, 230, 230);
	pt.fillRect(0, 0, 48, 48, color);
	pt.fillRect(48, 48, 48, 48, color);
	pt.end();
}

ShowWidget::~ShowWidget()
{
}

void ShowWidget::animate() {
	update();
}

void ShowWidget::setId(int id) {
	this->id = id;
	update();
}

void ShowWidget::show_test_img(QImage img) {
}

void ShowWidget::setMng(SourceMnger* mng) {
	this->mng = mng;
}
void ShowWidget::setPixelShowLabel(QLabel* l) {
	this->pixle_msg_label = l;
}


void ShowWidget::paintEvent(QPaintEvent* event) {
	QImage* p = mng->getImg(id);
	QImage img;
	if (p == nullptr) {
		img = bakImg;
	}
	else {
		img = *p; bakImg = img;
		resize(img.width(), img.height());
	}
	QPainter painter;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);

	//paint background
	painter.drawTiledPixmap(rect(), m_tile);
	//end of paint background

	QRectF target(width()/2 - img.width() /2, height()/2 - img.height()/2, img.width(), img.height());
	painter.drawImage(target, img);
	painter.end();
}



void ShowWidget::mouseMoveEvent(QMouseEvent* event) {
	//if (pixle_msg_label != nullptr) {
	//	QColor color = pickPixel(event->pos());
	//	int r = color.red();
	//	int g = color.green();
	//	int b = color.blue();
	//	QString msg = "r:" + QString::number(r) + " " + "g:" + QString::number(g) + " " + "b:"+QString::number(b);
	//	pixle_msg_label->setText(msg);
	//	return;
	//}
	QOpenGLWidget::mouseMoveEvent(event);
}

QColor ShowWidget::pickPixel(const QPoint& p) {
	const QPixmap pixmap(QSize(1, 1));
	QColor c = pixmap.toImage().pixel(0, 0);
	this->render((QPaintDevice*)&pixmap, QPoint(0, 0), QRegion(QRect(p, QSize(1,1))));
	QImage i = pixmap.toImage();
	return i.pixel(0, 0);
}
