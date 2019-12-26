#pragma once

#include <QObject>
#include <QImage>
#include <string>
#include <map>
#include <vector>
#include <QVector>
using namespace std;

class SourceMnger : public QObject
{
	Q_OBJECT

public:
	SourceMnger(QObject *parent);
	~SourceMnger();

	int openImg(const string& img_name);
	QImage* getImg(int id);
	void showImg(int id);
	void clear();

signals:
	void sig_show_msg(int id);
	void sig_show_img(QImage img);

private:
	QVector<QImage*> vec;
};
