
#include <QException>
class MultiOpenException : public QException {
public:
	void raise() const override { throw* this; }
	MultiOpenException* clone() const override { return new MultiOpenException(*this); }
};