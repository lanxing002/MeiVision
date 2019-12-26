#include "ShowWidget.h"

ShowWidget::ShowWidget(QWidget* parent)
	: QOpenGLWidget(parent), id(0)
{
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

void ShowWidget::paintEvent(QPaintEvent* event) {
	QImage* p = mng->getImg(id);
	QImage img;
	if (p == nullptr) {
		img = bakImg;
	}
	else {
		img = *p; bakImg = img;
	}

	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRectF target(0, 0, img.height(), img.width());
	painter.drawImage(target, img);
	painter.end();
}
