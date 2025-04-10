#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>
#include <format>
#include <map>

#include "Synapse\Synapse.h"
#include "Signal\Signal.h"

class Synapse;
class IONeuron;

class Neuron
{
protected:
    //TODO поменять на вектор для эффекта памяти
    std::vector<Synapse*> linkedSynapses;
    int index;
    double outputValue;
    double biasValue = 0;

public:
    Neuron(int setIndex);
    ~Neuron();

    double activation(double inputValue);
    int getIndex();
    double getBias();
    void setBias(double setBias);
    void setOutputValue(double setValue);
    double getOutputValue();

    void addSynapse(Synapse* synapse);
    void removeSynapse(Synapse* synapse);
    std::vector<Synapse*> getSynapses();

    void forward(int index);
    void backward(int index, double eps = 0.1);
};

class IONeuron : public Neuron
{
private:
    double inputValue;
    std::map<int, Signal*> collectedSignals;
public:
    IONeuron(double setValue = 0, int setIndex = 0);

    void spawnValueSignals(double value);
    void spawnErrorSignals(double value);
    operator std::string();

    void setInputValue(double setValue);
    double getInputValue();

    std::map<int, Signal*> getCollectedSignals();
    void collectSignal(int index, Signal* signal);
    void clearCollectedSignals();
};

#endif //NEURON_H