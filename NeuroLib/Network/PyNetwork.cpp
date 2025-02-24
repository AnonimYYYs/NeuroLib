#ifndef PYNETWORK_CPP
#define PYNETWORK_CPP

#include "Network\Network.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C"
{
	DLLEXPORT Network* Network_new()
	{
		return new Network();
	}
	DLLEXPORT void Network_delete(Network* network)
	{
		delete network;
	}
	DLLEXPORT Network* Network_createRandomNetwork(int nIons, int nNeurons, float connect)
	{
		return Network::createRandomNetwork(nIons, nNeurons, connect);
	}
	DLLEXPORT Network* Network_createSmallWorldNetwork(int nIons, int nNeurons, int degree, float rewire)
	{
		return Network::createSmallWorldNetwork(nIons, nNeurons, degree, rewire);
	};
	DLLEXPORT void Network_printIons(Network* network)
	{
		network->printIons();
	}
	DLLEXPORT int Network_getIonsSize(Network* network)
	{
		return network->getIons().size();
	}
	//TODO сделать проверку по типу через мапу neurons
	DLLEXPORT bool Network_checkIfIon(Network* network, int index)
	{
		for (IONeuron* ion : network->getIons())
		{
			if (ion->getIndex() == index)
				return true;
		}
		return false;
	}
	DLLEXPORT int Network_getSynapsesSize(Network* network)
	{
		return network->getSynapses().size();
	}
	DLLEXPORT Synapse* Network_getSynapses(Network* network, int pos)
	{
		return network->getSynapses()[pos];
	}
	DLLEXPORT double Network_getSynapseWeight(Network* network, int pos)
	{
		return network->getSynapses()[pos]->getWeight();
	}
	DLLEXPORT int Network_getSynapseConnectedNeuron1(Network* network, int pos)
	{
		return network->getSynapses()[pos]->getNeuron1()->getIndex();
	}

	DLLEXPORT int Network_getSynapseConnectedNeuron2(Network* network, int pos)
	{
		return network->getSynapses()[pos]->getNeuron2()->getIndex();
	}
}
#endif //PYNETWORK_CPP