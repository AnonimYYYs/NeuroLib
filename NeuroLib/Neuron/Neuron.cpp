#include "Neuron\Neuron.h"


double Neuron::activation(double inputValue)
{
    // сигмоид
    return 1.0 / (1.0 + std::exp(-inputValue));
}

Neuron::Neuron(int setIndex)
{ 
    index = setIndex;
}

Neuron::~Neuron()
{
    linkedSynapses.clear();
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
    double sumSignals = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        Signal* currentSignal = synapse->popSignal(index);
        if(currentSignal != nullptr)
        {
            sumSignals += currentSignal->getValue();
        }
    }
    //присваиваем сумму сигналов нейрону и активируем
    double outputValue = activation(sumSignals);

    //перемещаем сигналы
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* addSignal = new Signal(outputValue, index);
        synapse->addSignal(addSignal);
        synapse->applyWeight(addSignal);
    }
}

void Neuron::backward(int index, double eps)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }
    double sumSignals = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        //собираем сигналы
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            Signal* currentSignal = synapse->popSignal(index);
            if (currentSignal != nullptr)
            {
                sumSignals += currentSignal->getValue();
            }
        }
    }

    double error = sumSignals * eps;
    
    //перемещаем сигналы
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* addSignal = new Signal(error, index);
        synapse->addSignal(addSignal);
        //synapse->setWeight(synapse->getWeight() * error);
        synapse->setWeight(synapse->getWeight() + error);
    }
}

IONeuron::IONeuron(double setValue, int setIndex) : Neuron(setIndex) 
{
    inputValue = setValue;
    outputValue = setValue;
}

void IONeuron::spawnValueSignals(double value)
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


void IONeuron::setInputValue(double setValue)
{
    inputValue = setValue;
}

void IONeuron::setOutputValue(double setValue)
{
    outputValue = setValue;
}

double IONeuron::getInputValue()
{
    return inputValue;
}

std::map<int, Signal*> IONeuron::getCollectedSignals()
{
    return collectedSignals;
}

void IONeuron::collectSignal(int index, Signal* signal)
{
    collectedSignals[index] = signal;
}

void IONeuron::clearCollectedSignals()
{
    collectedSignals.clear();
}

double IONeuron::getOutputValue()
{
    return outputValue;
}

