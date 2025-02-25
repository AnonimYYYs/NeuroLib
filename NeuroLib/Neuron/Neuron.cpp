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

int Neuron::getIndex()
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


void Neuron::forward(int index)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }
    std::map<int, Signal*> collectedSignals;
    collectedSignals[index] = new Signal(0, index);

    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            if (signalIndex == index)
            {
                Signal* currentSignal = synapse->popSignal(index);
                int setValue = collectedSignals[index]->getValue() + currentSignal->getValue();
                collectedSignals[index]->setValue(setValue);
            }
        }
    }
    double sum = 0;
    for (auto [index, signal] : collectedSignals)
    {
        sum += signal->getValue(); 
    }
    if (sum != 0)
    {
        //присваиваем сумму сигналов нейрону и активируем
        double sigmoidSumByIndex = 1.0 / (1.0 + std::exp(-(sum)));
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
            synapse->applyWeight(addSignal);
        }
    }
    collectedSignals.clear();
}

void Neuron::backward(int index, double eps)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }
    std::map<int, Signal*> collectedSignals;
    collectedSignals[index] = new Signal(0, index);

    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            if (signalIndex == index)
            {
                Signal* currentSignal = synapse->popSignal(index);
                int setValue = collectedSignals[index]->getValue() + signal->getValue();
                collectedSignals[index]->setValue(setValue);
            }
        }
    }

    double sum = 0;
    for (auto [index, signal] : collectedSignals)
    {
        sum += signal->getValue();
    }
    sum *= eps;
    
    //перемещаем сигналы
    for (Synapse* synapse : linkedSynapses)
    {
        for (auto [index, signal] : collectedSignals)
        {
            Signal* addSignal = new Signal(*signal);
            synapse->addSignal(addSignal);
            synapse->setWeight(sum);
        }
    }
    collectedSignals.clear();
}

IONeuron::IONeuron(double setValue, int setIndex) : Neuron(setIndex) 
{
    inputValue = setValue;
    outputValue = setValue;
}

void IONeuron::spawnSignals(double value)
{
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* signal = new Signal(value, index);
        synapse->addSignal(signal);
        synapse->applyWeight(signal);
    }
}
//вместо applyWeight, делаем setWeight от ошибки
void IONeuron::spawnErrorSignals(double value)
{
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* signal = new Signal(value, index);
        synapse->addSignal(signal);
        synapse->setWeight(value);
    }
}

IONeuron::operator std::string()
{
    {
        return std::format("IONeuron Index: {}, Input Value: {:.5f}, Output Value: {:.5f}",
            index, inputValue, outputValue);
    }
}
