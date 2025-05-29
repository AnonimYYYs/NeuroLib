#include "Synapse\Synapse.h"

Synapse::Synapse(Neuron* neuron1, Neuron* neuron2, double setWeight)
{ 
    weight = setWeight;
    this->neuron1 = neuron1;
    this->neuron2 = neuron2;
}

Synapse::~Synapse()
{
    deleteSignals();
}

double leakyRelu(double x, double alpha = 0.01) 
{
    if (x > 0)
    {
        return x;
    }
    else
    {
        return alpha * x;
    }
}

double leakyReluInv(double y, double alpha = 0.01) 
{
    if (y >= 0) 
    {
        return y;      
    }
    else 
    {
        return y / alpha;
    }
}

double rrelu(double x, int* seedPtr)
{
    if (x > 0)
    {
        return x;
    }
    else
    {
        double alpha = Network::random(-1.0, 1.0, seedPtr);
        return alpha * x;
    }
}

double rreluInv(double y, int* seedPtr)
{
    if (y >= 0)
    {
        return y;
    }
    else
    {
        double alpha = Network::random(-1.0, 1.0, seedPtr);
        return y / alpha;
    }
}
double srelu(double x, double t_l, double t_r, double a_l, double a_r) 
{
    if (x >= t_r) 
    {
        return t_r + a_r * (x - t_r); 
    }
    else if (x <= t_l) 
    {
        return t_l + a_l * (x - t_l);
    }
    return x; 
}

double sreluInv(double y, double t_l, double t_r, double a_l, double a_r) 
{
    if (y >= t_r) 
    {
        return t_r + (y - t_r) / a_r; 
    }
    else if (y <= t_l) 
    {
        return t_l + (y - t_l) / a_l; 
    }
    return y;
}

double apl(double x, std::vector<double> a = {0.5, -0.2}, std::vector<double> b = {1.0, -0.5})
{
    double result = std::max(0.0, x);
    for (size_t s = 0; s < a.size(); ++s) 
    {
        result += a[s] * std::max(0.0, -x + b[s]);
    }
    return result;
}

double aplInv(double y, std::vector<double> a = { 0.5, -0.2 }, std::vector<double> b = { 1.0, -0.5 })
{
   
    double x = y;  
    double epsilon = 1e-6;
    for (int i = 0; i < 100; ++i) 
    {
        double fx = apl(x, a, b) - y;
        if (std::abs(fx) < epsilon) break;

       
        double dx = 1e-6;
        double dfx = (apl(x + dx, a, b) - apl(x, a, b)) / dx;

        x = x - fx / dfx;
    }
    return x;
}

double bentIdentity(double x) 
{
    return (sqrt(x * x + 1) - 1) / 2 + x;
}

double bentIdentityInv(double y)
{
    double t = 2 * y + 1;
    return (t - sqrt(t * t - 4 * y * y - 4 * y)) / 2;
}

double softExponential(double x, double alpha) 
{
    if (alpha < 0)
    {
        return -log(1 - alpha * (x + alpha)) / alpha;
    }
    return x;  // Для a=0 возвращает x
}

double softExponentialInv(double y, double alpha) 
{
    if (alpha > 0) 
    {
        // Для a > 0: y = (e^{ax}-1)/a + a
        return log(alpha * (y - alpha) + 1) / alpha;
    }
    else if (alpha < 0) 
    {
        // Для a < 0: y = -ln(1-a(x+a))/a
        return (1 - exp(-alpha * y)) / alpha - alpha;
    }
    return y;  // Для a = 0: y = x
}

double Synapse::defaultActivation(double inputValue, int* seedPtr)
{
    //return inputValue * weight + biasValue;

    //
    //return leakyRelu(inputValue);
    //return rrelu(inputValue, seedPtr);
    return srelu(inputValue, -0.5, 0.5, 0.1, 0.1);
    //return apl(inputValue);
    //return bentIdentity(inputValue);
    //return softExponential(inputValue, 0.5);
}

double Synapse::reverseActivation(double inputValue, int* seedPtr)
{
    //return inputValue / weight + biasValue;

    //
    //return leakyReluInv(inputValue);
    //return rreluInv(inputValue, seedPtr);
    return srelu(inputValue, -0.5, 0.5, 0.1, 0.1);
    //return aplInv(inputValue);
    //return bentIdentityInv(inputValue);
    //return softExponentialInv(inputValue, 0.5);
}


double Synapse::getWeight()
{
    return weight;
}

void Synapse::setWeight(double setWeight)
{
    weight = setWeight;
}

double Synapse::getBias()
{
    return biasValue;
}

void Synapse::setBias(double setBias)
{
    biasValue = setBias;
}

/*
@brief multiplies signal's stored value by synapse's weight
*/
void Synapse::applyWeight(Signal* signal, bool input)
{
    if (input == true)
    {
        signal->setValue(signal->getValue() * weight);
    }
    else
    {
        signal->setValue(signal->getValue() * 1 / weight);
    }
} 

void Synapse::addSignal(Signal* signal, bool input, int* seedPtr)
{
    double value = signal->getValue();
    if (input == true)
    {
        value = defaultActivation(value, seedPtr);
    }
    else
    {
        value = reverseActivation(value, seedPtr);
    }
    signal->setValue(value);
    storedSignals[signal->getIndex()] = signal;
}
void Synapse::removeSignal(int index)
{
    storedSignals.erase(index);
}

Signal* Synapse::popSignal(int index)
{
    Signal* signal = storedSignals[index];
    storedSignals.erase(index);
    return signal;
}

void Synapse::rewire(Neuron* neuron)
{
    neuron2->removeSynapse(this);
    neuron->addSynapse(this);
    neuron2 = neuron;
}

Neuron* Synapse::getNeuron1()
{
    return neuron1;
}

Neuron* Synapse::getNeuron2()
{
    return neuron2;
}

std::map<int, Signal*> Synapse::getSignals()
{
    return storedSignals;
}
void Synapse::deleteSignals()
{
    for (auto [index, signal] :storedSignals)
    {
        delete signal;
    }
    storedSignals.clear();
}

// Алгоритм де Бура
double Synapse::calcBaseSpline(double x, int i, int k)
{
    if (k == 0)
    {
        // ti <= x < ti+1
        if (knots[i] <= x && x < knots[i + 1])
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    }

    double c1 = 0.0;
    if (knots[i + k] != knots[i])
    {
        c1 = (x - knots[i]) / (knots[i + k] - knots[i]) * calcBaseSpline(x, i, k - 1);
    }

    double c2 = 0.0;
    if (knots[i + k + 1] != knots[i + 1])
    {
        c2 = (knots[i + k + 1] - x) / (knots[i + k + 1] - knots[i + 1]) * calcBaseSpline(x, i + 1, k - 1);
    }
    return c1 + c2;
}

double Synapse::startCalc(double x, int i)
{
    return calcBaseSpline(x, i, degree);
}
