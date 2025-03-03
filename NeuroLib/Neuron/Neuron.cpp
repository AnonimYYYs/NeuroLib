#include "Neuron\Neuron.h"


double Neuron::activation(double inputValue)
{
    // �������
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


void IONeuron::setValue(double setValue)
{ 
   inputValue = setValue; 
}
double IONeuron::getOutputValue()
{ 
    return outputValue; 
}

double IONeuron::getInputValue()
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
    collectedSignals[index] = new Signal(0.0, index);

    for (Synapse* synapse : linkedSynapses)
    {
        //�������� �������
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            if (signalIndex == index)
            {
                Signal* currentSignal = synapse->popSignal(index);
                double setValue = collectedSignals[index]->getValue() + currentSignal->getValue();
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
        //����������� ����� �������� ������� � ����������
        //double sigmoidSumByIndex = 1.0 / (1.0 + std::exp(-(sum)));

        //?����� ����� ������� ���� ������� ����� ����, exp(-x) ������������ � 1
        //x: 1.94515e-95
        //exp(-x) : 1
        //Sigmoid result : 0.5

        std::cout << "x: " << sum << std::endl;
        double exp_minus_x = std::exp(-sum);
        std::cout << "exp(-x): " << exp_minus_x << std::endl;
        double result = 1.0 / (1.0 + exp_minus_x);
        std::cout << "Sigmoid result: " << result << std::endl << std::endl << std::endl;

        // �� ������ ������ ����!!!
        double outputValue = activation(sum);

        //���������� �������
        for (Synapse* synapse : linkedSynapses)
        {

            Signal* addSignal = new Signal(outputValue);
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
        //�������� �������
        for (auto [signalIndex, signal] : synapse->getSignals())
        {
            if (signalIndex == index)
            {
                Signal* currentSignal = synapse->popSignal(index);
                double setValue = collectedSignals[index]->getValue() + signal->getValue();
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
    
    //���������� �������
    for (Synapse* synapse : linkedSynapses)
    {
        for (auto [index, signal] : collectedSignals)
        {
            Signal* addSignal = new Signal(*signal);
            synapse->addSignal(addSignal);
            synapse->setWeight(synapse->getWeight() * sum);
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
//������ applyWeight, ������ setWeight �� ������
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


void IONeuron::forward(int index, double value)
{

    //����������� ����� �������� ������� � ����������
    //double sigmoidSumByIndex = 1.0 / (1.0 + std::exp(-(sum)));

    //?����� ����� ������� ���� ������� ����� ����, exp(-x) ������������ � 1
    //x: 1.94515e-95
    //exp(-x) : 1
    //Sigmoid result : 0.5


    // �� ������ ������ ����!!!
    double outputVal = activation(value);

    //���������� �������
    for (Synapse *synapse : linkedSynapses)
    {
        Signal *addSignal = new Signal(outputVal);
        synapse->addSignal(addSignal);
        synapse->applyWeight(addSignal);

    }
}