#include "ShowWidget.h"

ShowWidget::ShowWidget(QWidget* parent)
	: QOpenGLWidget(parent), id(0), bakImg(QSize(600, 400), QImage::Format_RGB32)
{
	bakImg.fill(qRgb(0, 0, 0));
	//��ʼ��͸��������
}

ShowWidget::~ShowWidget()
{
}

void ShowWidget::animate() {
	update();
}

void ShowWidget::bak_last_img() {
	QImage* p = mng->getImg(this->id);

	if (p != nullptr) {
		QImage img = *p;
		bakImg = img;
	}
}

void ShowWidget::setId(uint id) { //size_t���� QVariant ���ͣ����ܴ���
	this->id = static_cast<size_t>(id);
	update();
}

void ShowWidget::show_test_img(QImage img) {
}

void ShowWidget::zoomin_img() {
	if (noscaledImg.isNull()) {
		noscaledImg = bakImg;
		bakImg = bakImg.scaled(QSize(bakImg.width() * 1.5, bakImg.height() * 1.5));
	}
	else bakImg = bakImg.scaled(QSize(bakImg.width() * 1.5, bakImg.height() * 1.5));
	update();
}
void ShowWidget::zoomout_img() {
	if (noscaledImg.isNull()) {
		//��һ�����ţ�����ͼƬ�洢������ָ�Բ��״
		noscaledImg = bakImg;
		bakImg = bakImg.scaled(QSize(bakImg.width() / 1.5, bakImg.height() / 1.5));
	}
	else bakImg = bakImg.scaled(QSize(bakImg.width() / 1.5, bakImg.height() / 1.5));
	update();
}
void ShowWidget::reset_img() {
	if (noscaledImg.isNull()) //û����������
		return;

	bakImg = noscaledImg;
	noscaledImg = QImage();
	update();
}

void ShowWidget::setMng(SourceMnger* mng) {
	this->mng = mng;
}
void ShowWidget::setPixelShowLabel(QLabel* l) {
	this->pixle_msg_label = l;
}

void ShowWidget::paintEvent(QPaintEvent* event) {
	QImage* p = mng->getImg(this->id);
	if (p != nullptr) {
		QImage img = *p;
		bakImg = img;
	}
	resize(bakImg.width(), bakImg.height());

	QPainter painter;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawImage(QPointF(0, 0), bakImg);
	
	painter.end();
}


void ShowWidget::mouseMoveEvent(QMouseEvent* event) {
	QOpenGLWidget::mouseMoveEvent(event);
}

QColor ShowWidget::pickPixel(const QPoint& p) {
	const QPixmap pixmap(QSize(1, 1));
	QColor c = pixmap.toImage().pixel(0, 0);
	this->render((QPaintDevice*)&pixmap, QPoint(0, 0), QRegion(QRect(p, QSize(1,1))));
	QImage i = pixmap.toImage();
	return i.pixel(0, 0);
}
