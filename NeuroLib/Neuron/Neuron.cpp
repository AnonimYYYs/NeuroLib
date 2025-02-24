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
        //? сигмоид примен€етс€ и к сигналам, которые были в одном экземпл€ре
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
            synapse->applyWeight(addSignal);
        }
    }
}

void Neuron::backward()
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
        
        inputValue = sum;
        activation();
    }
    //перемещаем сигналы
    //примен€ем сигмоиду и мен€ем ошибку? 
    //имеет ли смысл с учетом того, что ошибка одна на весь нетворк?
    for (Synapse* synapse : linkedSynapses)
    {
        for (auto [index, signal] : collectedSignals)
        {
            Signal* addSignal = new Signal(*signal);
            synapse->addSignal(addSignal);
            synapse->setWeight(sum);
        }
    }
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
