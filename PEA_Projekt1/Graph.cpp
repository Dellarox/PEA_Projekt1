#include "Graph.h"

bool Graph::fileReadLine(ifstream& file, int tab[], int size) {
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}

bool Graph::fileReadGraph(string fileName, bool isDirected) {
	ifstream file;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			numberOfCities = tabNumberOfCities[0];

			cout << "ilosc miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int ii = 0; ii < numberOfCities; ii++) {
					file >> weightMatrix[i][ii];
				}
			}

			cout << "Struktura w postaci macierzy wag:" << endl;
			showWeightMatrix();
			return true;
		}
		else
			cout << "File error - READ INFO" << endl;
		file.close();
		return false;
	}
	else
		cout << "File error - OPEN" << endl;

	return false;
}

void showRow(vector<int> weightMatrix) { // funkcja pomocnicza w wy�wietlaniu macierzy
	for (int i = 0; i < (int)weightMatrix.size(); i++) {
		cout << weightMatrix[i];
		if (weightMatrix[i] > 9) {
			if (weightMatrix[i] < 100) {
				cout << "  ";
			}
			else {
				cout << " ";
			}
		}
		else {
			cout << "   ";
		}
	}
}

void Graph::showWeightMatrix() {
	cout << "    ";
	for (int i = 0; i < numberOfCities; i++)
		cout << i + 1 << "___";
	cout << endl;

	for (int i = 0; i < numberOfCities; i++) {
		cout << i + 1 << "  |";
		showRow(weightMatrix[i]);
		cout << endl;
	}
	cout << endl;
}

void Graph::dynamicProgrammingAlgorithm() {
	cout << "Odleg�o�ci mi�dzy miastami:" << endl << endl;
	showWeightMatrix();
	cout << endl;
	cout << "\nMinimalna d�ugo�� drogi: " << dynamicProggraming(0, 1) << endl;
}

int Graph::dynamicProggraming(int cityWeChecking, int visitedCitiesLocal) {
	visitedCities = (1 << numberOfCities) - 1;

	memory.resize((1 << numberOfCities), vector<int>(numberOfCities));

	if (visitedCitiesLocal == visitedCities)
		return weightMatrix[cityWeChecking][0];

	if (memory[visitedCitiesLocal][cityWeChecking] != 0)
		memory[visitedCitiesLocal][cityWeChecking];

	int minimum = INT_MAX;

	for (int i = 0; i < numberOfCities; i++) {
		if (i == cityWeChecking)
			continue;

		if ((visitedCitiesLocal & (1 << i)) == 0){
			int temp = weightMatrix[cityWeChecking][i] + dynamicProggraming(i, visitedCitiesLocal | (1 << i));
			if (temp < minimum)
				minimum = temp;
		}
	}

	memory[visitedCitiesLocal][cityWeChecking] = minimum;
	return minimum;
}
