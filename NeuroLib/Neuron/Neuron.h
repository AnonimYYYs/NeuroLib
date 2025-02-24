#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>
#include <format>

#include "Synapse\Synapse.h"
#include "Signal\Signal.h"

class Synapse;
class IONeuron;

class Neuron
{
protected:
    //TODO поменять на вектор для эффекта памяти
    double inputValue;
    double outputValue;
    std::vector<Synapse*> linkedSynapses;
    int index;

public:
    Neuron(int setIndex);
    ~Neuron();

    void activation();
    void setValue(double setValue);
    double getOutputValue();
    double getInputValue();
    int getIndex();

    void addSynapse(Synapse* synapse);
    std::vector<Synapse*> getSynapses();

    void forward();
    void backward();
};

class IONeuron : public Neuron
{
public:
    IONeuron(double setValue = 0, int setIndex = 0);

    void spawnSignals(double value);
    void spawnErrorSignals(double value);
    operator std::string();
};

#endif //NEURON_H