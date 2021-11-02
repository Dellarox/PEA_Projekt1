#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include <deque>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Graph {
public:
	vector<vector<int>> weightMatrix, memory;
	int numberOfCities = 0, visitedCities = 0;

	bool fileReadLine(ifstream& file, int tab[], int size);

	void showWeightMatrix();

	void prepareForDynamicProggraming();

	int dynamicProggraming(int cityWeChecking, int visitedCities);

	bool fileReadGraph(string fileName, bool isDirected);
};