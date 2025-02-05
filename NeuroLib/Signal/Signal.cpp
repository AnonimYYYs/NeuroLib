#include "Signal\Signal.h"

Signal::Signal(double value, int index) : value(value), index(index), lastNode(index)
{
}
Signal::Signal(Signal* signal, int node) : value(signal->value), index(signal->index), lastNode(node) { }

double Signal::getValue()
{
	return value;
}

void Signal::setValue(double setValue)
{
	value = setValue;
}

int Signal::getNode()
{
	return lastNode;
}

void Signal::setNode(int index)
{
	lastNode = index;
}