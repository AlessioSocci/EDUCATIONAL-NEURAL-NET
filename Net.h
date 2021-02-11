#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>

#include "Utilities.h"
#include "Neuron.h"

using namespace std;


class Net
{
	public:

		Net(vector<unsigned>& topology);

		void forwardPropagation(vector<double>& input);
		void backPropagation(vector<double>& target);

		void getResults(vector<double>& result);
		double getError(void) { return errorSum; }


	private:

		vector<Layer> Layers;
		double error;
		double errorSum;
		double smoothFactor;

};


Net::Net(vector<unsigned>& topology) // constructor of net
{
	unsigned numberOfLayer = topology.size();  // size method applied to container object, return number of element , in this case number of element is equal of the numbers of layer in net.

	for (unsigned i = 0; i < numberOfLayer; i++) // create the layers in m_layers container vector (it's a matrix with row and column that rapresents layer and neuron)
	{
		Layers.push_back(Layer()); // push_back method append vector Layer on vector m_layer; this create matrix of container type (not of simple array... vector type that contain object neuron!)

		unsigned numOutputs = i == topology.size() - 1 ? 0 : topology[i + 1]; // (- 1 if equal 0 to exclude bias neuron that hasn't input)

		for (unsigned j = 0; j <= topology[i]; j++) // this internal loop insert the neurons in this layer!
		{
			Layers.back().push_back(Neuron(numOutputs, j)); // create and queue in the container, each neuron present in this layer 

			cout << "one neuron created" << endl;
		}

		Layers.back().back().setOutputValue(1.0); // add the last neuron of the layer, the bias neuron
	}
}


void Net::forwardPropagation(vector<double>& input)  // argument is an address of a type container because this method must change this value also in external environtment
{
	assert(input.size() == Layers[0].size() - 1);

	for (unsigned i = 0; i < input.size(); ++i)
	{
		Layers[0][i].setOutputValue(input[i]); // assign input value for each neuron in this input layers, this is the first stage of the net
	}

	for (unsigned j = 1; j < Layers.size(); j++) // cycle start on 1 because input layers is already set in previous "for" cycle with the assigned input
	{
		Layer& prevLayer = Layers[j - 1]; // previous layer

		for (unsigned n = 0; n < Layers[j].size() - 1; n++) // minus one because bias neuron must not be calculated
		{
			Layers[j][n].neuronBehavior(prevLayer); // recall beaviour model method for each neuron in the previous layer
		}
	}
}


void Net::getResults(vector<double>& result)// argument is an address of a type container because this method must change this value also in external environtment
{
	result.clear();

	for (unsigned n = 0; n < Layers.back().size() - 1; n++)
	{
		result.push_back(Layers.back()[n].getOutputValue());
	}
}


void Net::backPropagation(vector<double>& target) // argument is an address of a type container because this method must change this value also in external environtment
{
	Layer& outputLayer = Layers.back();

	smoothFactor = 100.0;
	error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; n++)  // bias excluded
	{
		double delta = target[n] - outputLayer[n].getOutputValue();
		error += delta * delta; // error^2 
	}

	error /= outputLayer.size() - 1; // (error^2)/2
	error = sqrt(error); // RMS of error

	errorSum = (errorSum * smoothFactor + error) / (smoothFactor + 1.0);

	for (unsigned n = 0; n < outputLayer.size() - 1; n++)  // bias excluded
	{
		outputLayer[n].calcOutputGradients(target[n]);
	}

	for (unsigned layerNum = Layers.size() - 2; layerNum > 0; layerNum--)
	{
		Layer& hiddenLayer = Layers[layerNum];
		Layer& nextLayer = Layers[layerNum + 1];
		for (unsigned n = 0; n < hiddenLayer.size(); n++)
		{
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	for (unsigned layerNum = Layers.size() - 1; layerNum > 0; layerNum--) // input layer excluded
	{
		Layer& layer = Layers[layerNum];
		Layer& prevLayer = Layers[layerNum - 1];
		for (unsigned n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}