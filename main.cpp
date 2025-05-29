#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>
#include <chrono>


#include <vector>
#include <cmath>
#include <cstdlib>


size_t totalMemory = 0;
size_t* memory = &totalMemory;

void* operator new(size_t size) 
{
    *memory += size;
    return malloc(size);
}

void operator delete(void* ptr, size_t size)
{
    *memory -= size;
    free(ptr);
}

int main() 
{
    //TODO createrandom полностью связный при коннект=1
    int seed = 111;
    int* seedPtr = &seed;

    std::vector<std::vector<bool>> params;
    //int n = 12;
    //int total = 1 << n; // 2^n

    //for (int i = 1; i < total - 1; ++i)
    //{
    //    std::vector<bool> mask(n);
    //    for (int j = 0; j < n; ++j)
    //    {
    //        mask[n - j - 1] = (i >> j) & 1;
    //    }
    //    params.push_back(mask);
    //}
    params = { { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
              { 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0 },
              { 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1 },   
              { 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
              { 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 } };


    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    

    std::string filenameCsv = "..\\..\\..\\results\\network.csv";
    std::stringstream ss;
    ss << filenameCsv;
    std::ofstream csvFile(filenameCsv);
    csvFile << "Params;Score;Time;Memory\n";
    csvFile.close();

    for (auto mask : params)
    {
        for (int val : mask)
        {
            std::cout << val << " " << "\n";
        }
        std::cout << std::endl;

        totalMemory = 0;
        SimpleForwardNetwork* network = SimpleForwardNetwork::createSpiralNetwork(12, seedPtr);
        network->initGraphs();


        int epoch = 5;

        //"C:\Users\user\Desktop\Neuro\NeuroLib\datasets\2x100_sig_ax+b_dataset.csv" 
        //std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_ax+b_dataset.csv";
        std::string filename = "winequality-red.csv";
        std::string filepath = "..\\..\\..\\datasets\\" + filename;
        std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filepath);


        //csvFile1 << "Epoch;ErrorScore;time;w1;w2;w3;w4;w5;w6;w7;w8;w9;w10;w11;w12;w13;w14;w15;w16;w16;w17;w18;w19;w20;w21;w22;w23;w24;b1;b2;b3;b4;b5;b6;b7;b8;b9;b10;b11;b12;b13;b14;b15;b16\n";
        //csvFile1 << "Params;Score;Time\n";


        startTime = std::chrono::high_resolution_clock::now();

        network->learn(dataset, epoch, startTime, mask, seedPtr, filenameCsv, memory);

        delete network;
    }

    return 0;
}