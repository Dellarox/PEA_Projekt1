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
			numberOfCities = tabNumberOfCities[0]; // przypisanie ilo�ci miast z pierwszej linijki pliku

			if(!isTest)
				cout << endl << "Ilo�� miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie warto�ci do vectora
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

	for (int i = 0; i < numberOfCities; i++) {
		showRow(weightMatrix[i]);
		cout << endl;
	}
	cout << endl;
}

void Graph::prepareForDynamicProggraming() {
	visitedCities = (1 << numberOfCities) - 1; // zmienna pomagaj�ca sprawdza� czy wszystkie miasta zosta�y odwiedzone
	memory.resize((1 << numberOfCities), vector<int>(numberOfCities)); // rezerwujemy w pami�ci odpowiedni� liczb� kom�rek
}

int Graph::dynamicProggraming(int cityWeChecking, int visitedCitiesLocal, vector<int> &path) {

	if (visitedCitiesLocal == visitedCities) // tutaj sprawdzamy, czy wszystkie miasta zosta�y odwiedzone
		return weightMatrix[cityWeChecking][0]; // je�li tak to jest zwracana droga z ostatniego odwiedzonego miasta do pierwszego
	


	if (memory[visitedCitiesLocal][cityWeChecking] != 0) // tutaj sprawdzamy, czy miasto by�o ju� odwiedzone i je�li by�o
		return memory[visitedCitiesLocal][cityWeChecking]; // to zwracamy �cie�k� do niego

	int minimum = INT_MAX;

	for (int i = 0; i < numberOfCities; i++) {
		if (i == cityWeChecking)
			continue;

		if ((visitedCitiesLocal & (1 << i)) == 0) {
			int temp = weightMatrix[cityWeChecking][i] + dynamicProggraming(i, visitedCitiesLocal | (1 << i), path);
			if (temp < minimum)
				minimum = temp;
		} // w tym if'ie sprawdzana jest najoptymalniejsza �cie�ka dla ka�dego wierzcho�ka; nasza funkcja jest wywo�ywana rekursywnie
		// przesuni�cie bitowe wyst�puj�ce w kolejnych wywo�aniach funkcji sprawdza miasta ju� odwiedzone i potem sprawdzane jest, czy �cie�ka, kt�ra znalaz� jest najlepsza
	}

	memory[visitedCitiesLocal][cityWeChecking] = minimum;
	return minimum; // na koniec najlepsza �cie�ka jest zapisywana do vectora i jest zwracana
}