#include "Neuron\Neuron.h"


double Neuron::activation(double inputValue)
{
    // сигмоид + смещение
    //return (1.0 / (1.0 + std::exp(-inputValue))) + biasValue;
    //return inputValue + biasValue;
    return inputValue;
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

double Neuron::getBias()
{
    return biasValue;
}

void Neuron::setBias(double setBias)
{
    biasValue = setBias;
}

void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
}

void Neuron::removeSynapse(Synapse* synapse)
{
    for (auto iter = linkedSynapses.begin(); iter!=linkedSynapses.end(); iter++)
    {
        if (*iter == synapse)
        {
            linkedSynapses.erase(iter);
            return;
        }
    }
}

std::vector<Synapse*> Neuron::getSynapses()
{
    return linkedSynapses;
}


void Neuron::forwardOld(int index, bool input)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }

    std::vector<Synapse*> collectDirectionSynapses, spreadDirectionSynapses;
    if (input == true)
    {
        collectDirectionSynapses = inSynapses;
        spreadDirectionSynapses = outSynapses;
    }
    else
    {
        collectDirectionSynapses = outSynapses;
        spreadDirectionSynapses = inSynapses;
    }



    double sumSignals = 0;
    for (Synapse* synapse : collectDirectionSynapses)
    {
        //собираем сигналы
        Signal* currentSignal = synapse->popSignal(index);
        if(currentSignal != nullptr)
        {
            sumSignals += currentSignal->getValue();
        }
        delete currentSignal;
    }
    outputValue = activation(sumSignals);

    //перемещаем сигналы
    for (Synapse* synapse : spreadDirectionSynapses)
    {
        Signal* addSignal = new Signal(outputValue, index);
        synapse->addSignal(addSignal, input);
        //synapse->applyWeight(addSignal, input);
    }
}

void Neuron::backward(int index, bool input, double eps)
{
    if (linkedSynapses.size() == 0)
    {
        return;
    }

    std::vector<Synapse*> collectDirectionSynapses, spreadDirectionSynapses;
    if (input == true)
    {
        collectDirectionSynapses = outSynapses;
        spreadDirectionSynapses = inSynapses;
    }
    else
    {
        collectDirectionSynapses = inSynapses;
        spreadDirectionSynapses = outSynapses;
    }




    double sumSignals = 0;
    for (Synapse* synapse : collectDirectionSynapses)
    {
        //собираем сигналы
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            Signal* currentSignal = synapse->popSignal(index);
            if (currentSignal != nullptr)
            {
                sumSignals += currentSignal->getValue();
            }
            delete currentSignal;
        }
    }
    
    double error = sumSignals * eps;
    
    //перемещаем сигналы
    for (Synapse* synapse : spreadDirectionSynapses)
    {
        Signal* addSignal = new Signal(error, index);
        synapse->addSignal(addSignal, input);
        synapse->setWeight(synapse->getWeight() + error * outputValue);
    }
    biasValue += error;
}

Neuron::Neuron(int n_in, int n_weights_per_edge, std::vector<double> x_bounds, int degree) 
: xBounds(x_bounds)
{
    {
        //создаем веса
        for (int i = 0; i < weights.size(); i++)
        {
            weights[i] = Network::random(-1, 1);
        }

        //создаем сетку узлов
        //шаг сетки
        double step = (xBounds[1] - xBounds[0]) / (weights.size() - degree + 1 - 1); 

        //узлы
        for (int i = 0; i < knots.size(); i++)
        {
            knots[i] = xBounds[0] + (i - degree) * step;
        }

    }
}

double Neuron::sigmoid(double x)
{
    return x / (1.0 + std::exp(-x));
}


void Neuron::forwardKAN()
{

    std::vector<double> xmid;
    for (int i = 0; i < inSynapses.size(); i++)
    {
        Signal* currentSignal = inSynapses[i]->popSignal(index);
        double sum = 0.0;
        for (int k = 0; k < weights.size(); k++)
        {
            if (k == 0)
            {
                sum += weights[i] * sigmoid(currentSignal->getValue());
            }
            else
            {
                sum += weights[i] * inSynapses[k]->startCalc(currentSignal->getValue(), i);
            }
        }
        xmid[i] = sum;
        delete currentSignal;
    }

    //в нейроне все еще применяем активацию?
    double xout = 0.0;
    for (double val : xmid)
    {
        xout += val;
    }
    outputValue = std::tanh(xout); //+биас

    for (Synapse* synapse : outSynapses)
    {
        Signal* addSignal = new Signal(outputValue, index);
        synapse->addSignal(addSignal, 1);
    }

}


IONeuron::IONeuron(double setValue, int setIndex) : Neuron(setIndex) 
{
    inputValue = setValue;
    outputValue = setValue;
}

void IONeuron::spawnValueSignals(double value, bool input)
{
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* signal = new Signal(value, index);
        synapse->addSignal(signal, input);
        synapse->applyWeight(signal, input);
    }
}
//вместо applyWeight, делаем setWeight от ошибки
void IONeuron::spawnErrorSignals(double error)
{
    biasValue += error;
    for (Synapse* synapse : linkedSynapses)
    {
        Signal* signal = new Signal(error, index);
        //?
        synapse->addSignal(signal, 1);
        synapse->setWeight(synapse->getWeight() + error);
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

void Neuron::setOutputValue(double setValue)
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

double Neuron::getOutputValue()
{
    return outputValue;
}

