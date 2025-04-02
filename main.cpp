#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>
#include <chrono>


int main() 
{
    //TODO createrandom полностью связный при коннект=1
    int seed = 11;
    int* seedPtr = &seed;

    //std::vector<int> rows = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    //int nIons = 20;

    ////для строк
    //for (int row : rows)
    //{
    //    //определяем название csv файла
    //    std::string filename = std::to_string(nIons) + "x" + std::to_string(row) + "_dataset.csv";
    //    std::string filepath = "..\\..\\..\\datasets\\Bulk_test\\" + filename;

    //    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(nIons, nIons * 3, 1, 0.2, seedPtr);
    //    network->initGraphs();

    //    std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filepath);
    //    network->learn(dataset, 10, seedPtr);
    //}

    ////для нейронов
    //int row = 100;
    //std::vector<int> nNeurons = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
    //for (int neuron : nNeurons)
    //{
    //    //определяем название csv файла
    //    std::string filename = std::to_string(nIons) + "x" + std::to_string(row) + "_dataset.csv";
    //    std::string filepath = "..\\..\\..\\datasets\\Bulk_test\\" + filename;

    //    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(nIons, neuron, 1, 0.2, seedPtr);
    //    network->initGraphs();

    //    std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filepath);
    //    network->learn(dataset, 10, seedPtr);
    //}

    ////для эпох
    //std::vector<int> epochs = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    //for (int epoch : epochs)
    //{
    //    //определяем название csv файла
    //    std::string filename = std::to_string(nIons) + "x" + std::to_string(row) + "_dataset.csv";
    //    std::string filepath = "..\\..\\..\\datasets\\Bulk_test\\" + filename;

    //    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(nIons, nIons * 3, 1, 0.2, seedPtr);
    //    network->initGraphs();

    //    std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filepath);
    //    network->learn(dataset, epoch, seedPtr);
    //}






    //размерности датасетов
    /*std::vector<int> cols = { 10, 50, 100, 200, 500 };
    //std::vector<int> rows= { 100, 1000, 10000, 100000};*/

    /*std::vector<int> cols = { 10 };
    std::vector<int> rows = { 10000 };*/

    /*std::ofstream outputFile("..\\..\\..\\results.csv");
    /utputFile << "Cols;Rows;Ions;Neurons;Epochs;BoolTimeTotal(s);BoolTimeAvg(s);PtrTimeTotal(s);PtrTimeAvg(s)\n";
    outputFile.flush();
    outputFile.close();*/

    //for (int col : cols) 
    //{
    //    //создаем нетворк с нужным количеством нейронов
    //    //!!для больших нетворков rewire часто создает несвязные графы, поэтому пока берем 0
    //    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(col, col * 3, 1, 0);
    //    network->initGraphs();

    //    for (int row : rows) 
    //    {
    //        //определяем название csv файла
    //        std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_dataset.csv";
    //        std::string filepath = "..\\..\\..\\datasets\\Bulk_test\\" + filename;

    //        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    //        std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    //        int epoch = 100;
    //        /*if (col > 50 && row > 100)
    //        {
    //            epoch = 1;
    //        }
    //        else
    //        {
    //            epoch = 100000 / (col * row);
    //        }*/
    //        //bool
    //        startTime = std::chrono::high_resolution_clock::now();
    //        for (int i = 0; i < epoch; i++) 
    //        {
    //            std::cout << i << std::endl;
    //            std::vector<std::vector<std::pair<double, bool>>> datasetBool = SimpleForwardNetwork::readDataBool(filepath);
    //            std::vector<std::vector<double>> predictedDataset = network->predictBool(datasetBool);
    //        }
    //        endTime = std::chrono::high_resolution_clock::now();
    //        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    //        std::pair<std::chrono::seconds, std::chrono::seconds> currentResult;
    //        currentResult.first = duration;

    //        //ptr
    //        startTime = std::chrono::high_resolution_clock::now();
    //        for (int i = 0; i < epoch; i++) 
    //        {
    //            std::cout << i << std::endl;
    //            std::vector<std::vector<double*>> datasetPtr = SimpleForwardNetwork::readDataPtr(filepath);
    //            std::vector<std::vector<double>> predictedDataset = network->predictPtr(datasetPtr);
    //        }
    //        endTime = std::chrono::high_resolution_clock::now();
    //        duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    //        currentResult.second = duration;

    //        std::ofstream outputFile("..\\..\\..\\results.csv", std::ios::app);
    //        outputFile << col << ";" << row << ";" << col << ";" << col * 3 << ";" << epoch << ";"
    //            << currentResult.first.count() << ";" << currentResult.first.count() / epoch << ";"
    //            << currentResult.second.count() << ";" << currentResult.second.count() / epoch << "\n";
    //        outputFile.flush();
    //        outputFile.close();
    //    }
    //}

    return 0;
}