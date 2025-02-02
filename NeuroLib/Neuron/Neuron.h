#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>
#include <sstream>

#include "Synapse\Synapse.h"
#include "Signal\Signal.h"

class Synapse;

class Neuron
{
private:
    double inputValue;
    double outputValue;
    std::vector<Synapse*> linkedSynapses;
    int const index;
public:
    Neuron(double setValue = 0, int index = 0);

    void activation();
    void setValue(double setValue);
    double getValue();
    double getInputValue();
    int const getIndex();

    void addSynapse(Synapse* synapse);
    std::vector<Synapse*> getSynapses();

    void forwardIn();
    void forwardOut();

    ///
    //virtual std::string toString() const {
    //    std::stringstream ss;
    //    ss << getValue();
    //    return ss.str();
    //}

};

//no operator "<<" matches these operands ?
//std::ostream& operator<<(std::ostream& os, const Neuron& neuron);

class IONeuron : public Neuron
{
public:
    IONeuron(double inputValue = 0, int index = 0);

    operator std::string() {
        std::stringstream ss;
        ss << "IONeuron Index: " << getIndex() << ", Input Value: " << getInputValue()
            << ", Output Value: " << getValue();
        return ss.str();
    }
};


#endif //NEURON_H