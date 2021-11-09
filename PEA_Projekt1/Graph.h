#pragma once
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
	vector<vector<int>> memory, bestPath, weightMatrixHelp;
	vector<int> actualPathWeHave;
	int visitedCities = 0, helpForActualPath = 0, numberOfCitiesHelp;

	//void showWeightMatrix(int& numberOfCities, vector<vector<int>>& weightMatrix);

	bool fileReadLine(ifstream& file, int tab[], int size);

	bool fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix);

	void prepareForDynamicProggramingCountMinimalCost(int numberOfCities, vector<vector<int>> weightMatrix);

	void prepareForDynamicProggramingFindBestPath();

	int dynamicProggramingCountMinimalCost(int visitedCities, int cityWeChecking);

	void dynamicProggramingFindBestPath(int visitingCity, int startingCity);

	void bruteForceCountMinimalCostAndBestPath(vector<vector<int>> weightMatrix, int& result, vector<int>& pathVar);
};