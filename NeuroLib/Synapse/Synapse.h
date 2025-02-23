#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Neuron\Neuron.h"
#include "Signal\Signal.h"

#include <map>

class Neuron;
class Signal;

class Synapse
{
private:
    double weight;
    Neuron* neuron1;
    Neuron* neuron2;
    std::map<int, Signal*> storedSignals;
public:
    Synapse(Neuron* neuron1, Neuron* neuron2);
    ~Synapse();

    double getWeight();
    void setWeight(double setWeight);

    void applyWeight(Signal* targetSignal);
    void addSignal(Signal* signal);
    void removeSignal(int index);
    Signal* popSignal(int index);
    void rewire(Neuron* neuron);

    Neuron* getNeuron1();
    Neuron* getNeuron2();
    std::map<int, Signal*> getSignals();
    void deleteSignals();
};

#endif //SYNAPSE_H