extern "C" {
#include "redirect.h"
}

#include "redirectCpp.h"

ConsoleSender* StaticSender::static_sender = nullptr;


void StaticSender::init_sender(QObject* parent) {
	static_sender =new ConsoleSender(parent);
}

void StaticSender::destroy_sender() {
	if (static_sender != nullptr) {
		delete static_sender;
	}
}

const ConsoleSender* StaticSender::get_sender() {
	return static_sender;
}

void StaticSender::send_msg(const string& str) {
	if (static_sender != nullptr) {
		emit static_sender->sig_stdout(str);
	}
	return;
}

void my_write(const char* s, size_t l) {
	StaticSender::send_msg(string(s, l));

}
void my_write_error(const char* str, const char* format) {
	char buffer[1024];
	sprintf(buffer, str, format);
	StaticSender::send_msg(string(buffer));
}
