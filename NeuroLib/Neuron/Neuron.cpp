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

void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
}

std::vector<Synapse*> Neuron::getSynapses()
{
    return linkedSynapses;
}


void Neuron::forward(std::vector<IONeuron*> ions)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }
    std::vector<Signal*> collectedSignals;
    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        for (Signal* signal : synapse->getSignals())
        {
            collectedSignals.push_back(signal);
            synapse->removeSignal(signal);
        }
    }
    double sum = 0;
    for (IONeuron* ion : ions)
    {
        double sumByIndex = 0;
        int index = ion->getIndex();
        for (Signal* signal : collectedSignals)
        {
            if (index == signal->getIndex())
            {
                sumByIndex += signal->getValue();
            }
        }
        //перемещаем сигналы
        double sigmoidSumByIndex = 1.0 / (1.0 + std::exp(-sumByIndex));
        for (Synapse* synapse : linkedSynapses)
        {
            synapse->addSignal(new Signal(sigmoidSumByIndex, index));
        }
        sum += sigmoidSumByIndex;
    }
    if (sum != 0)
    {
        //присваиваем сумму сигналов нейрону и активируем
        inputValue = sum;
        activation();
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
