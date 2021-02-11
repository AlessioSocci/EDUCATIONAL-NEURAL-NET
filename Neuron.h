#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>

#include "Utilities.h"

using namespace std;


class Neuron;

typedef vector<Neuron> Layer;

class Neuron
{
	public:

		Neuron(unsigned numOutputs, unsigned myIndex);

		void setOutputValue(double val) {outputValue = val;}
		double getOutputValue(void) {return outputValue;}

		void neuronBehavior(Layer& prevLayer);
		void calcOutputGradients(double targetVals);
		void calcHiddenGradients(Layer& nextLayer);
		void updateInputWeights(Layer& prevLayer);

	private:

		unsigned index;

		double outputValue;
		double gradientAtThisStep;

		vector<Connection> outputWeights; // vector of weights contained in struct named "connection", so it's a matrix: weight and delta-weight double type element for each neuron.

		static double transferFunction(double x, string function); // used in forward prop. in this example, use a hyperbolic tangent function, that assume value between 1 and -1 (no sigmoid)
		static double transferFunctionDerivative(double x, string function); // used in back prop. to obtain the error (delta) of each neuron respect the wanted output
		static double randomWeight(void) {return rand() / double(RAND_MAX);} // value between 0 and 1
};


Neuron::Neuron(unsigned numOutputs, unsigned myIndex) // implement constructor of the neuron
{
	for (unsigned i = 0; i < numOutputs; i++) // cycle in base of number of neurons presents in next layer to give the right number of weights at this neurons.
	{
		outputWeights.push_back(Connection()); // matrix of weights , composed by weight and delta-weight
		outputWeights.back().weight = randomWeight(); // random value assign to weights of neuron output "axons"
	}

	index = myIndex;
}

void Neuron::neuronBehavior(Layer& prevLayer) // argument is an address of a type container because this method must change this value also in external environtment
{
	double argument = 0.0;

	for (unsigned i = 0; i < prevLayer.size(); i++) // create input argument for forward trasnfer function
	{
		argument += prevLayer[i].getOutputValue() * prevLayer[i].outputWeights[index].weight; // sum of  output * weight of each neuron
	}

	outputValue = Neuron::transferFunction(argument, "tanh"); // here call the forward transfer function
}



void Neuron::calcOutputGradients(double targetVals)
{
	double delta = targetVals - outputValue;

	gradientAtThisStep = delta * Neuron::transferFunctionDerivative(outputValue, "tanh");
}


void Neuron::calcHiddenGradients(Layer& nextLayer)
{
	double value = 0;

	for (unsigned i = 0; i < nextLayer.size() - 1; i++) // bias excluded
	{
		value += outputWeights[i].weight * nextLayer[i].gradientAtThisStep;
	}

	gradientAtThisStep = value * Neuron::transferFunctionDerivative(outputValue, "tanh");
}


void Neuron::updateInputWeights(Layer& prevLayer) // argument is an address of a type container because this method must change this value also in external environtment
{
	double eta = 0.15; // training rate between 0 and 1
	double alpha = 0.5; // momentum betwen 0 and 1

	for (unsigned i = 0; i < prevLayer.size(); i++)
	{
		Neuron& neuron = prevLayer[i];

		double oldDeltaWeight = neuron.outputWeights[index].deltaWeight;

		double newDeltaWeight = eta * neuron.getOutputValue() * gradientAtThisStep + alpha * oldDeltaWeight;

		neuron.outputWeights[index].deltaWeight = newDeltaWeight;

		neuron.outputWeights[index].weight += newDeltaWeight;
	}
}


double Neuron::transferFunction(double x, string function) // Activation Function ...tanh = 2 * Sigmoid(2x)... Sigmoid = e^x/(1 + e^x)
{
	if(function._Equal("tanh"))
	{

		return tanh(x);
	}
	else if(function._Equal("relu"))
	{
		if (x <= 0)
		return 0;
		
		else
		return x;
	}
}


double Neuron::transferFunctionDerivative(double x, string function) // Derivative of Activation Function 
{
	

	if (function._Equal("tanh"))
	{
		return 1.0 - x * x;
	}
	else if (function._Equal("relu"))
	{
		return x > 0;
	}
}
