#pragma once


#include <cassert>
#include <string>
#include <iostream>
#include <sstream> 
#include <fstream>

#include <vector>


using namespace std;


struct Connection
{
	double weight;
	double deltaWeight;
};


string toString(int i)
{
	stringstream ss;

	ss << i;

	return ss.str();
}

void printVector(string label, std::vector<double>& v)
{
	cout << label << " ";

	for (unsigned i = 0; i < v.size(); ++i) cout << v[i] << " ";

	cout << endl;
}

void createTrainingData()
{
	ofstream fileOut("training.txt");

	cout << "TRAINING SET:" << endl << endl;

	cout << "topology 2 4 1" << endl << endl;

	fileOut << "topology 2 4 1" << endl;

	for (int i = 2000; i >= 0; --i)
	{
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));

		int t = n1 ^ n2; // should be 0 or 1

		cout << "in: " << n1 << ".0 " << n2 << ".0 " << endl;

		fileOut << "in: " << toString(n1) << ".0 " << toString(n2) << ".0 " << endl;

		cout << "out: " << t << ".0 " << endl << endl;

		fileOut << "out: " << toString(t) << ".0 " << endl;
	}

	fileOut.close();
}
