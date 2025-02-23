#include "Neuron\Neuron.h"

void Neuron::activation()
{
    // сигмоид
    outputValue = 1.0 / (1.0 + std::exp(-inputValue));
}

Neuron::Neuron(int setIndex)
{ 
    index = setIndex;
}

Neuron::~Neuron()
{
    linkedSynapses.clear();
}


void Neuron::setValue(double setValue) 
{ 
   inputValue = setValue; 
}
double Neuron::getOutputValue()
{ 
    return outputValue; 
}

double Neuron::getInputValue()
{
    return inputValue;
}

int const Neuron::getIndex()
{
    return index;
}

int const getIndex2()
{
    return 0;
}


void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
}

std::vector<Synapse*> Neuron::getSynapses()
{
    return linkedSynapses;
}


void Neuron::forward()
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }
    std::map<int, Signal*> collectedSignals;
    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        for (auto [index, signal] : synapse->getSignals())
        {
            if (collectedSignals.contains(index) == true)
            {
                double sumByIndex = collectedSignals[index]->getValue() + signal->getValue();
                collectedSignals[index]->setValue(sumByIndex);
            }
            else
            {
                collectedSignals[index] = signal;
            }
            synapse->removeSignal(index);
        }
    }
    double sum = 0;
    for (auto [index, signal] : collectedSignals)
    {
        double sigmoidSumByIndex = 1.0 / (1.0 + std::exp(-(signal->getValue())));
        signal->setValue(sigmoidSumByIndex);
        sum += sigmoidSumByIndex;
    }
    if (sum != 0)
    {
        //присваиваем сумму сигналов нейрону и активируем
        inputValue = sum;
        activation();
    }
    //перемещаем сигналы
    for (Synapse* synapse : linkedSynapses)
    {
        for (auto [index, signal] : collectedSignals)
        {
            Signal* addSignal = new Signal(*signal);
            synapse->addSignal(addSignal);
        }
    }
}

IONeuron::IONeuron(double setValue, int setIndex) : Neuron(setIndex) 
{
    inputValue = setValue;
    activation();
}

void IONeuron::spawnSignals()
{
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* signal = new Signal(outputValue, index);
        synapse->addSignal(signal);
    }
}

IONeuron::operator std::string()
{
    {
        return std::format("IONeuron Index: {}, Input Value: {:.5f}, Output Value: {:.5f}",
            index, inputValue, outputValue);
    }
}
