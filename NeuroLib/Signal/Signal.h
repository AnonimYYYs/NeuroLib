#ifndef SIGNAL_H
#define SIGNAL_H

#include "Signal\Signal.h"

class Signal
{
private:
	double value;
	int index;
public:
	Signal(double value = 0, int index = 0);
	double getValue();
	void setValue(double setValue);
	int getIndex();
};
#endif //SIGNAL_H