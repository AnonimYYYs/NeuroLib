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
double Neuron::getValue()
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

void Neuron::forward()
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }

    double sum = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        for (Signal* signal : synapse->getSignals())
        {
            //берем один сигнал из синапса
            if (signal->getNode() != index)
            {
                sum += signal->getValue();
                break;
            }
        }
    }

    if (sum != 0)
    {
        //присваиваем сумму сигналов нейрону и активируем
        inputValue = sum;
        activation();

        //перемещаем сигналы, которые просуммировали
        for (Synapse* synapse : linkedSynapses)
        {
            for (Signal* signal : synapse->getSignals())
            {
                if (signal->getNode() != index)
                {
                    //удаляем сигнал из текущего синапса
                    signal->setValue(outputValue);
                    synapse->removeSignal(signal);

                    //направляем сигнал в следующие синапсы
                    for (Synapse* synapse2 : linkedSynapses)
                    {
                        if (synapse2 != synapse)
                        {
                            synapse2->addSignal(new Signal(signal, index));
                        }
                    }
                    break;
                }
            }
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