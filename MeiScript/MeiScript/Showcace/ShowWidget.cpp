#include "ShowWidget.h"

ShowWidget::ShowWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{
}

ShowWidget::~ShowWidget()
{
}

void ShowWidget::animate() {
	update();
}

void ShowWidget::setId(size_t id) {
	this->id = id;
}

void ShowWidget::show_test_img(QImage img) {
}

void ShowWidget::setMng(SourceMnger* mng) {
	this->mng = mng;
}

void ShowWidget::paintEvent(QPaintEvent* event) {
	QImage* p = mng->getImg(id);
	if (p == nullptr)
		return QOpenGLWidget::paintEvent(event);

	QImage img = *p;
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRectF target(0, 0, img.height(), img.width());
	painter.drawImage(target, img);
	painter.end();
}
