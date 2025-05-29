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
    double biasValue = 0;
    Neuron* neuron1;
    Neuron* neuron2;
    std::map<int, Signal*> storedSignals;


    int degree;
    std::vector<double> knots;
public:
    Synapse(Neuron* neuron1, Neuron* neuron2, double weight = 0);
    ~Synapse();

    double defaultActivation(double inputValue, int* seedPtr);
    double reverseActivation(double inputValue, int* seedPtr);

    double getWeight();
    void setWeight(double setWeight);
    double getBias();
    void setBias(double setBias);

    void applyWeight(Signal* targetSignal, bool input);
    void addSignal(Signal* signal, bool input, int* seedPtr = nullptr);
    void removeSignal(int index);
    Signal* popSignal(int index);
    void rewire(Neuron* neuron);

    Neuron* getNeuron1();
    Neuron* getNeuron2();
    std::map<int, Signal*> getSignals();
    void deleteSignals();


    double calcBaseSpline(double x, int i, int k);
    double startCalc(double x, int i);
};

#endif //SYNAPSE_H