#include <cassert>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>

#include <vector>


using namespace std;

#include "Utilities.h"
#include "Training.h"
#include "Neuron.h"
#include "Net.h"


int main()
{
	createTrainingData(); // call a fucntion to create a random training data

	Training trainingData("training.txt"); // load training data set file

	std::vector<unsigned> netTopology; // this container rapresent the topology of net: number of neuron for each input, hidden and output layers

	trainingData.getTopology(netTopology); // read training file to get net topology, place it in the vector continer previous declared  
	
	Net net(netTopology); // recall constructor to create a Net object, passing topology vector as argument

	std::vector<double> inputVector, targetVector, outputVector; // declare the vector containers of signal in, out, and target value that net should fit


	int trainingStep = 0; // variable used as a step counter

	while(!trainingData.endOfFile()) // read the previous created training file until the "end of file" 
	{
		trainingStep++;

		cout << endl << "Step number: " << trainingStep << endl; 

		if (trainingData.prepareInputsForThisStep(inputVector) != netTopology[0]) // get input for this step from file and check its size
		{
			cout << "error in input value in step:" + trainingStep << endl; 

			break;
		}

		printVector("Inputs:", inputVector);

		net.forwardPropagation(inputVector); // forward propagation to find delta, the difference between resul and target

		net.getResults(outputVector); 

		printVector("Outputs:", outputVector); 

		trainingData.getTargetOutputs(targetVector); 

		printVector("Targets:", targetVector); 

		assert(targetVector.size() == netTopology.back());

		net.backPropagation(targetVector); // backpropagagion to find new connection weights

		cout << "Error: " << net.getError() << endl;
	}

	cout << endl << "Done" << endl;
}