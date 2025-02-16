#include "Signal\Signal.h"

Signal::Signal(double value, int index) : value(value), index(index), lastNeuron(index)
{
}
Signal::Signal(Signal* signal, int node) : value(signal->value), index(signal->index), lastNeuron(node) { }

double Signal::getValue()
{
	return value;
}

void Signal::setValue(double setValue)
{
	value = setValue;
}

int Signal::getLastNeuron()
{
	return lastNeuron;
}

void Signal::setLastNeuron(int index)
{
	lastNeuron = index;
}

int Signal::getIndex()
{
	return index;
}
