#include "Synapse\Synapse.h"

//incomplete type is not allowed (Signal)
#include "Signal\Signal.h"

Synapse::Synapse(Neuron* neuron1, Neuron* neuron2, double w, double v) :  weight(w), value(v) 
{ 
    linkedNeurons.push_back(neuron1);
    linkedNeurons.push_back(neuron2);

    neuron1->addSynapse(this);
    neuron2->addSynapse(this);
}

double Synapse::getValue()
{
    return value;
}
void Synapse::setValue(int n)
{
    value = linkedNeurons[n]->getValue();
}
void Synapse::moveValue(int n)
{
    linkedNeurons[n]->setValue(value);
}

void Synapse::applyWeight(Signal* signal)
{
    signal->setValue(signal->getValue() * weight);
} 

//void Neuron::forward()
//{
//    double sum = 0;
//    for (Synapse* synapse : linkedSynapses)
//    {
//        sum += synapse->applyWeight(this);
//    }
//    inputValue = sum;
//    activation();
//}


//создаем новый сигнал
void Synapse::forward(int destination)
{
    Signal* signal;
    for (Neuron* neuron : linkedNeurons)
    {
        if (neuron->getIndex() != destination)
        {
            signal = new Signal(neuron->getValue(), neuron->getIndex());
            storedSignals.push_back(signal);
        }
    }
    applyWeight(signal);
    //std::cout << signal->getValue() << std::endl;
    for (Neuron* neuron : linkedNeurons)
    {
        if (neuron->getIndex() == destination)
        {
            neuron->setValue(signal->getValue());
        }
    }
}

//перемещаем существующий сигнал
void Synapse::forward(Signal* signal, int destination)
{
    //удаляем сигнал из текущего синапса
    for (auto iterSignal {storedSignals.begin()}; iterSignal != storedSignals.end(); iterSignal++)
    {
        if (signal == *iterSignal)
        {
            storedSignals.erase(iterSignal);
        }
    }
    applyWeight(signal);
    //std::cout << signal->getValue();
    //перемещаем сигнал в следующий синапс
    for (Neuron* neuron : linkedNeurons)
    {
        for (Synapse* synapse : neuron->getSynapses())
        {
            for (Neuron* neuron2 : synapse->getNeurons())
            {
                if (neuron2->getIndex() == destination)
                {
                    synapse->storedSignals.push_back(signal);
                    neuron2->setValue(signal->getValue());
                    return;
                }
            }
        }
    }

}

std::vector<Neuron*> Synapse::getNeurons()
{
    return linkedNeurons;
}

std::vector<Signal*> Synapse::getSignals()
{
    return storedSignals;
}
