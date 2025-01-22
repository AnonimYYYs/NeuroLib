#ifndef NEUROLIB_H
#define NEUROLIB_H

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#include <vector>
#include <iostream>
#include <math.h> 


extern "C" {
    namespace neurolib {
        DLLEXPORT int neuro_sum(int a, int b);
    }
}

using namespace std;

class Neuron;

class Synapse 
{
private:
    Neuron* input;
    Neuron* output;
    double weight;

public:
    Synapse(Neuron* in, Neuron* out, double w) : input(in), output(out), weight(w) {}

    Neuron* getInput() { return input; } 
    Neuron* getOutput() { return output; } 
   
    double applyWeight();
};

class Neuron 
{
private:
    double value;
    vector<Synapse*> linkedSynapses;

    double activation() 
    { 
        // сигмоид
        return 1.0 / (1.0 + std::exp(-value));
    }

public:
     Neuron(double setValue = 0) : value(setValue) {}

    void setValue(double setValue) { value = setValue; }
    double getValue() { return value; }

    void addSynapse(Synapse* synapse) { linkedSynapses.push_back(synapse); }

    double forward(); 
};

double Synapse::applyWeight()
{
    double weightedInput = input->getValue() * weight;
    output->setValue(weightedInput);
    return weightedInput;
}

double Neuron::forward() 
{
    double sum = 0;
    for (Synapse* synapse : linkedSynapses) 
    {
        sum += synapse->applyWeight();
    }
    value = sum;
    return activation();
}

#endif //NEUROLIB_H
