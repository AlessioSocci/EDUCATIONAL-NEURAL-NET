#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <vector>


using namespace std;


// TRAINING DATA

class Training
{
	public:

		Training(const string filename);
		bool endOfFile() {return trainingFile.eof();}
		void getTopology(vector<unsigned>& topology);
		unsigned prepareInputsForThisStep(vector<double>& input);
		unsigned getTargetOutputs(vector<double>& target);

	private:

		ifstream trainingFile; // declaration of an object type inputfilestream
};


Training::Training(const string filename)
{
	trainingFile.open(filename.c_str());
}


void Training::getTopology(vector<unsigned>& topology) // argument is an address of a type container because this method must modified it (arguments of a method are only a copy of out declared type)  
{
	string line;

	string lineStream;

	getline(trainingFile, line); // get first line of training file

	stringstream ss(line);

	ss >> lineStream; // a simple control for check if file start with a specific string, only to give it a format. 

	if (lineStream.compare("topology:") == 0)
	{
		abort();
	}

	while (!ss.eof())
	{
		unsigned n;

		ss >> n;

		topology.push_back(n);
	}

	return;
}


unsigned Training::prepareInputsForThisStep(vector<double>& input) // argument is an address of a type container because this method must modified it (arguments of a method are only a copy of out declared type)  
{
	input.clear(); // make sure that input vector is empty

	string line;

	getline(trainingFile, line);

	stringstream ss(line);

	string lineString;

	ss >> lineString;

	if (lineString.compare("in:") == 0) // set position in file where take the inputs
	{
		double value;

		while (ss >> value)
		{
			input.push_back(value); // queue each input value in the vector
		}
	}

	return input.size(); // method return size of vector
}


unsigned Training::getTargetOutputs(vector<double>& target)
{
	target.clear();

	string line;

	getline(trainingFile, line);

	stringstream ss(line);

	string lineStream;

	ss >> lineStream;

	if (lineStream.compare("out:") == 0) // set position where take the targets
	{
		double value;

		while (ss >> value)
		{
			target.push_back(value); // queue each input value in the vector
		}
	}

	return target.size(); // method return size of vector
}
