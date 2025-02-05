#ifndef SIGNAL_H
#define SIGNAL_H

#include "Signal\Signal.h"

class Signal
{
private:
	double value;
	int index;
	int lastNode;
public:
	Signal(double value = 0, int index = 0);
	Signal(Signal* signal, int node);
	double getValue();
	void setValue(double setValue);
	int getNode();
	void setNode(int index);
};
#endif //SIGNAL_H