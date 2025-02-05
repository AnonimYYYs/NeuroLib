#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>
#include <format>

#include "Synapse\Synapse.h"
#include "Signal\Signal.h"

class Synapse;

class Neuron
{
private:
    static int counter;
    static void count();
protected:
    double inputValue;
    double outputValue;
    std::vector<Synapse*> linkedSynapses;
    int index;

public:
    Neuron();

    void activation();
    void setValue(double setValue);
    double getValue();
    double getInputValue();
    int const getIndex();

    void addSynapse(Synapse* synapse);
    std::vector<Synapse*> getSynapses();

    void forward();
};

class IONeuron : public Neuron
{
public:
    IONeuron(double setValue = 0);

    void spawnSignals();
    operator std::string() 
    {
        return std::format("IONeuron Index: {}, Input Value: {:.5f}, Output Value: {:.5f}", 
                index, inputValue, outputValue);
    }
};


#endif //NEURON_H