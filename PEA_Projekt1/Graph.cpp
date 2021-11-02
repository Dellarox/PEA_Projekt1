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
	int x;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			removeGraph(); // czyszczenie pamieci z poprzedniego grafu

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

void Graph::removeGraph() {
	weightMatrix.clear();
	weightMatrix.resize(0);
}

void Graph::showWeightMatrix() {
	cout << "   ";
	for (int i = 0; i < numberOfCities; i++)
		cout << i + 1 << "___";
	cout << endl;

	for (int i = 0; i < numberOfCities; i++) {
		cout << i + 1 << "  |";
		for (int j = 0; j < numberOfCities; j++) {
			cout << weightMatrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::dynamicProgrammingAlgorithm() {
	cout << "Odleg³oœci miêdzy miastami:" << endl << endl;
	showWeightMatrix();
	cout << endl;
	cout << "\nMinimalna d³ugoœæ drogi: " << endl;
}
