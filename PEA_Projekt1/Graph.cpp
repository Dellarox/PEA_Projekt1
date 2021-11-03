#include "Graph.h"
#include <unordered_map>

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

bool Graph::fileReadGraph(string fileName, bool isTest) {
	ifstream file;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			numberOfCities = tabNumberOfCities[0]; // przypisanie iloœci miast z pierwszej linijki pliku

			if(!isTest)
				cout << endl << "Iloœæ miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie wartoœci do vectora
				}
			}

			if (!isTest) {
				cout << endl << "Struktura w postaci macierzy wag:" << endl;
				showWeightMatrix();
			}
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

void showRow(vector<int> weightMatrix) { // funkcja pomocnicza w wyœwietlaniu macierzy
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

	for (int i = 0; i < numberOfCities; i++) {
		showRow(weightMatrix[i]);
		cout << endl;
	}
	cout << endl;
}

void Graph::prepareForDynamicProggraming() {
	visitedCities = (1 << numberOfCities) - 1; // zmienna pomagaj¹ca sprawdzaæ czy wszystkie miasta zosta³y odwiedzone
	memory.resize((1 << numberOfCities), vector<int>(numberOfCities)); // rezerwujemy w pamiêci odpowiedni¹ liczbê komórek
}

int Graph::dynamicProggraming(int cityWeChecking, int visitedCitiesLocal, vector<int> &path) {

	if (visitedCitiesLocal == visitedCities) // tutaj sprawdzamy, czy wszystkie miasta zosta³y odwiedzone
		return weightMatrix[cityWeChecking][0]; // jeœli tak to jest zwracana droga z ostatniego odwiedzonego miasta do pierwszego
	


	if (memory[visitedCitiesLocal][cityWeChecking] != 0) // tutaj sprawdzamy, czy miasto by³o ju¿ odwiedzone i jeœli by³o
		return memory[visitedCitiesLocal][cityWeChecking]; // to zwracamy œcie¿kê do niego

	int minimum = INT_MAX;

	for (int i = 0; i < numberOfCities; i++) {
		if (i == cityWeChecking)
			continue;

		if ((visitedCitiesLocal & (1 << i)) == 0) {
			int temp = weightMatrix[cityWeChecking][i] + dynamicProggraming(i, visitedCitiesLocal | (1 << i), path);
			if (temp < minimum)
				minimum = temp;
		} // w tym if'ie sprawdzana jest najoptymalniejsza œcie¿ka dla ka¿dego wierzcho³ka; nasza funkcja jest wywo³ywana rekursywnie
		// przesuniêcie bitowe wystêpuj¹ce w kolejnych wywo³aniach funkcji sprawdza miasta ju¿ odwiedzone i potem sprawdzane jest, czy œcie¿ka, która znalaz³ jest najlepsza
	}

	memory[visitedCitiesLocal][cityWeChecking] = minimum;
	return minimum; // na koniec najlepsza œcie¿ka jest zapisywana do vectora i jest zwracana
}