#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>
#include <format>
#include <map>

#include "Synapse\Synapse.h"
#include "Signal\Signal.h"
#include "Network\Network.h"

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


    /*int nInputs;
    int nWeights;*/
    std::vector<double> xBounds;
    std::vector<double> weights;
    std::vector<double> knots;

    //std::vector<BSpline> splines;

public:
    std::vector<Synapse*> inSynapses;
    std::vector<Synapse*> outSynapses;


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

    void forwardOld(int index, bool input);
    void backward(int index, bool input, double eps = 0.1);



    Neuron(int n_in, int n_weights_per_edge, std::vector<double> x_bounds, int degree);
    double sigmoid(double x);
    void forwardKAN();

};

class IONeuron : public Neuron
{
private:
    double inputValue;
    std::map<int, Signal*> collectedSignals;
public:
    IONeuron(double setValue = 0, int setIndex = 0);

    void spawnValueSignals(double value, bool input);
    void spawnErrorSignals(double value);
    operator std::string();

    void setInputValue(double setValue);
    double getInputValue();

    std::map<int, Signal*> getCollectedSignals();
    void collectSignal(int index, Signal* signal);
    void clearCollectedSignals();
};

#endif //NEURON_H