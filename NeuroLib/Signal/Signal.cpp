#include "Signal\Signal.h"

Signal::Signal(double value, int index) : value(value), index(index) {}

double Signal::getValue()
{
	return value;
}

void Signal::setValue(double setValue)
{
	value = setValue;
}
