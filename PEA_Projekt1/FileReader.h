#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class FileReader {
public:
	bool fileReadLine(ifstream& file, int tab[], int size);
	bool fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix);
};

