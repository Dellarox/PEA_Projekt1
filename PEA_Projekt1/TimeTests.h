#pragma once
#include <iomanip>
#include <windows.h>
#include "Graph.h"
#include "FileReader.h"

using namespace std;

class TimeTests {
public:
	double timeOfTest = 0;

	long long int read_QPC();

	void timeTestsForDynamicProggraming(Graph g, FileReader fr, string fileName, int numberOfCities, vector<vector<int>> weightMatrix);
};