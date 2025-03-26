#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>
#include <chrono>


int main() 
{
    //TODO createrandom ��������� ������� ��� �������=1
    int seed = 111;
    int* seedPtr = &seed;


    //SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(6, 10, 1, 0.3, seedPtr);
    //network->initGraphs();

    //std::string filename = "..\\..\\..\\datasets\\10x100_dataset.csv";
    //std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filename);
    //network->learn(dataset, 10, seedPtr);




    //����������� ���������
    /*std::vector<int> cols = { 10, 50, 100, 200, 500 };
    std::vector<int> rows = { 100, 1000, 10000, 100000};*/

    std::vector<int> cols = { 100 };
    std::vector<int> rows = { 100 };

    std::vector<std::pair<std::chrono::seconds, std::chrono::seconds>> results;

    for (int col : cols)
    {
        //������� ������� � ������ ����������� ��������
        //!!��� ������� ��������� rewire ����� ������� ��������� �����, ������� ���� ����� 0
        SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(col, col * 3, 1, 0, seedPtr);
        network->initGraphs();

        for (int row : rows)
        {
            //���������� �������� csv �����
            std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_dataset.csv";
            std::string filepath = "..\\..\\..\\datasets\\Bulk_test\\" + filename;


            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
            int epoch = 1;
            /*int epoch;
            if (col > 50 && row > 10000)
            {
                epoch = 1;
            }
            else
            {
                epoch = 10000000 / (col * row);
            }*/
            //bool
            startTime = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < epoch; i++)
            {
                std::vector<std::vector<std::pair<double, bool>>> datasetBool = SimpleForwardNetwork::readDataBool(filepath);
                std::vector<std::vector<double>> predictedDataset = network->predictBool(datasetBool);
            }
            endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

            std::pair<std::chrono::seconds, std::chrono::seconds> currentResult;
            currentResult.first = duration / epoch;

            //ptr
            startTime = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < epoch; i++)
            {

                std::vector<std::vector<double*>> datasetPtr = SimpleForwardNetwork::readDataPtr(filepath);
                std::vector<std::vector<double>> predictedDataset = network->predictPtr(datasetPtr);
            }
            endTime = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

            currentResult.second = duration / epoch;
            results.push_back(currentResult);
        }
    }

    int i = 0;
    for (int col : cols)
    {
        for (int row : rows)
        {
            auto result = results[i];
            std::string filename = std::to_string(col) + "x" + std::to_string(row) + "_dataset.csv";
            std::cout << "Size: " << col << "x" << row << std::endl
                << "Bool Average Time: " << result.first << std::endl
                << "Ptr Average Time: " << result.second << std::endl << std::endl;
            i++;
        }
    }


    return 0;
}