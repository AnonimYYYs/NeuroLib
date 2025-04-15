#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>
#include <chrono>


int main() 
{
    //TODO createrandom полностью связный при коннект=1
    int seed = 111;
    int* seedPtr = &seed;

    SimpleForwardNetwork* network1 = new SimpleForwardNetwork();
    network1->addIONeuron(new IONeuron(Network::random(-1, 1, seedPtr), 0));
    network1->addIONeuron(new IONeuron(Network::random(-1, 1, seedPtr), 1));
    network1->addSynapse(new Synapse(network1->getIons()[0], network1->getIons()[1], Network::random(-1.0, 1.0, seedPtr)));
    network1->initGraphs();

    SimpleForwardNetwork* network2 = new SimpleForwardNetwork();
    network2->addIONeuron(new IONeuron(Network::random(-1, 1, seedPtr), 0));
    network2->addIONeuron(new IONeuron(Network::random(-1, 1, seedPtr), 1));
    network2->addNeuron(new Neuron(2));
    network2->addNeuron(new Neuron(3));
    network2->addSynapse(new Synapse(network2->getNeurons()[0], network2->getNeurons()[2], (Network::random(-1, 1, seedPtr))));
    network2->addSynapse(new Synapse(network2->getNeurons()[2], network2->getNeurons()[1], (Network::random(-1, 1, seedPtr))));
    network2->addSynapse(new Synapse(network2->getNeurons()[0], network2->getNeurons()[3], (Network::random(-1, 1, seedPtr))));
    network2->addSynapse(new Synapse(network2->getNeurons()[3], network2->getNeurons()[1], (Network::random(-1, 1, seedPtr))));
    network2->initGraphs();

    int col = 2;
    //std::vector<int> rows = { 10, 100, 1000, 10000, 100000, 1000000 };
    std::vector<int> rows = { 10 };


    for (int row : rows) 
    {
        int epoch = 100000;
        //"C:\Users\user\Desktop\Neuro\NeuroLib\datasets\2x10000_y=x_dataset.csv"   
        std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_sig_ax+b_dataset.csv";
        std::string filepath = "..\\..\\..\\datasets\\" + filename;

        std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filepath);

        /*std::string filenameCsv1 = "..\\..\\..\\results\\network1_rows_" + std::to_string(row) + ".csv";
        std::string filenameCsv2 = "..\\..\\..\\results\\network2_rows_" + std::to_string(row) + ".csv";*/
        std::string filenameCsv1 = "..\\..\\..\\results\\network1.csv";
        std::string filenameCsv2 = "..\\..\\..\\results\\network2.csv";

        std::stringstream ss1, ss2;
        ss1 << filenameCsv1;
        ss2 << filenameCsv2;

        std::ofstream csvFile1(filenameCsv1);
        std::ofstream csvFile2(filenameCsv2);

        csvFile1 << "Epoch;ErrorScore;w1;b1;b2\n";
        csvFile2 << "Epoch;ErrorScore;w1;w2;w3;w4;b1;b2;b3;b4\n";

        csvFile1.close();
        csvFile2.close();
        
        network1->learn(dataset, epoch, seedPtr, filenameCsv1);
        network2->learn(dataset, epoch, seedPtr, filenameCsv2);
    }



    /*std::ofstream outputFile("..\\..\\..\\results.csv");
    outputFile << "Cols;Rows;Ions;Neurons;Epochs;BoolTimeTotal(s);BoolTimeAvg(s);PtrTimeTotal(s);PtrTimeAvg(s)\n";
    outputFile.flush();
    outputFile.close();*/

    //for (int row : rows) 
    //{
    //    //определяем название csv файла
    //    std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_dataset.csv";
    //    std::string filepath = "..\\..\\..\\datasets\\" + filename;

    //    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    //    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    //    int epoch = 100;
    //    /*if (col > 50 && row > 100)
    //    {
    //        epoch = 1;
    //    }
    //    else
    //    {
    //        epoch = 100000 / (col * row);
    //    }*/
    //    //bool
    //    startTime = std::chrono::high_resolution_clock::now();
    //    for (int i = 0; i < epoch; i++) 
    //    {
    //        std::cout << i << std::endl;
    //        std::vector<std::vector<std::pair<double, bool>>> datasetBool = SimpleForwardNetwork::readDataBool(filepath);
    //        std::vector<std::vector<double>> predictedDataset = network->predictBool(datasetBool);
    //    }
    //    endTime = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    //    std::pair<std::chrono::seconds, std::chrono::seconds> currentResult;
    //    currentResult.first = duration;

    //    //ptr
    //    startTime = std::chrono::high_resolution_clock::now();
    //    for (int i = 0; i < epoch; i++) 
    //    {
    //        std::cout << i << std::endl;
    //        std::vector<std::vector<double*>> datasetPtr = SimpleForwardNetwork::readDataPtr(filepath);
    //        std::vector<std::vector<double>> predictedDataset = network->predictPtr(datasetPtr);
    //    }
    //    endTime = std::chrono::high_resolution_clock::now();
    //    duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    //    currentResult.second = duration;

    //    std::ofstream outputFile("..\\..\\..\\results.csv", std::ios::app);
    //    outputFile << col << ";" << row << ";" << col << ";" << col * 3 << ";" << epoch << ";"
    //        << currentResult.first.count() << ";" << currentResult.first.count() / epoch << ";"
    //        << currentResult.second.count() << ";" << currentResult.second.count() / epoch << "\n";
    //    outputFile.flush();
    //    outputFile.close();
    //}




    //размерности датасетов
    /*std::vector<int> cols = { 10, 50, 100, 200, 500 };
    //std::vector<int> rows= { 100, 1000, 10000, 100000};*/

    /*std::vector<int> cols = { 10 };
    std::vector<int> rows = { 10000 };*/

    /*std::ofstream outputFile("..\\..\\..\\results.csv");
    outputFile << "Cols;Rows;Ions;Neurons;Epochs;BoolTimeTotal(s);BoolTimeAvg(s);PtrTimeTotal(s);PtrTimeAvg(s)\n";
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