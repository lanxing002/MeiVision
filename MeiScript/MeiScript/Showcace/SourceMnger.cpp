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
int SourceMnger::openImg(const string& img_name) {
	QImage* img = new QImage(QString::fromStdString(img_name));
	
	if (img == NULL)
		return 0;
	
	vec.push_back(img);
	return vec.size() - 1;
}

QImage* SourceMnger::getImg(int id) {
	if (id >= vec.size())
		return nullptr;

	return vec[id];
}

void SourceMnger::showImg(int id) {
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