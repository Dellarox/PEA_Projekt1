#pragma once
#include <iomanip>
#include <windows.h>
#include "Graph.h"

using namespace std;

class TimeTests {
public:
	double timeOfTest = 0;

	long long int read_QPC();

	void timeTestsForDynamicProggraming(Graph g, string fileName, int numberOfCities, vector<vector<int>> weightMatrix);
	void timeTestsForBruteForce(Graph g, string fileName, int numberOfCities, vector<vector<int>> weightMatrix);
};