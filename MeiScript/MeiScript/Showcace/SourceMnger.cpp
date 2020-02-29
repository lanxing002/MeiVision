#include "SourceMnger.h"

SourceMnger::SourceMnger(QObject *parent)
	: QObject(parent)
{
}

SourceMnger::~SourceMnger()
{
	for each (QImage* img in vec)
	{
		delete img;
	}
}

size_t SourceMnger::openImg(const string& img_name) {
	QImage* img = new QImage(QString::fromStdString(img_name));
	if (img == NULL)
		return 0;
	
	vec.push_back(img);
	return vec.size();
}

size_t SourceMnger::grayImg(const size_t id) {
	QImage* t = vec[id - 1];
	QImage* img = new QImage(t->convertToFormat(QImage::Format_Grayscale8));
	vec.push_back(img);
	return vec.size();
}

QImage* SourceMnger::getImg(size_t id) {

	if (id > vec.size() || id == 0)
		return nullptr;

	return vec[id - 1];
}

void SourceMnger::showImg(size_t id) {
	if (id > vec.size() || id == 0)
		return;

	emit sig_show_msg(static_cast<uint>(id));
	//emit sig_show_img(*vec[id]);
}

void SourceMnger::clear() {
	for each (QImage * img in vec)
	{
		delete img;
	}
	vec.clear();
}