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
	return vec.size() - (size_t)1;
}

QImage* SourceMnger::getImg(size_t id) {
	if (id >= vec.size())
		return nullptr;

	return vec[id];
}

void SourceMnger::showImg(size_t id) {
	if (id >= vec.size())
		return;

	emit sig_show_msg(id);
	//emit sig_show_img(*vec[id]);
}

void SourceMnger::clear() {
	for each (QImage * img in vec)
	{
		delete img;
	}
	vec.clear();
}