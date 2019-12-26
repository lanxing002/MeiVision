#pragma once
#include <QObject>
#include <string>
using namespace std;

void my_write(const char* s, size_t l);
void my_write_error(const char* str, const char* format);

class ConsoleSender : public QObject
{
	Q_OBJECT

public:
	ConsoleSender(QObject* parent = nullptr) : QObject(parent) {};
	~ConsoleSender() {};

signals:
	void deep_sig_stdout(const QString& str);
};

class StaticSender {
public:
	static void init_sender(QObject* parent);
	static void destroy_sender();
	static const ConsoleSender* get_sender();
	static void send_msg(const string& str);
	static ConsoleSender* static_sender;
};