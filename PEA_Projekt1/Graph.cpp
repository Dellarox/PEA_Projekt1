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

bool Graph::fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix) {
	ifstream file;
	int tabNumberOfCities[1];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tabNumberOfCities, 1))
		{
			weightMatrix.clear();
			weightMatrix.resize(0);

			numberOfCities = tabNumberOfCities[0]; // przypisanie iloœci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Iloœæ miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie wartoœci do vectora
				}
			}
			
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

void Graph::prepareForDynamicProggramingCountMinimalCost(int numberOfCities, vector<vector<int>> weightMatrix) { // funkcja odpowiadaj¹ca za przygotowanie zmiennych oraz vectror'ów do wykonania algorytmu dynamicznego programowania dla obliczenia najkrótszej œcie¿ki
	numberOfCitiesHelp = numberOfCities;
	weightMatrixHelp = weightMatrix;
	allVisitedCities = (1 << numberOfCitiesHelp) - 1; // zmienna pomagaj¹ca sprawdzaæ czy wszystkie miasta zosta³y odwiedzone
	memory.resize((1 << numberOfCitiesHelp), vector<int>(numberOfCitiesHelp)); // rezerwujemy w pamiêci odpowiedni¹ liczbê komórek
	bestPath.resize((1 << numberOfCitiesHelp), vector<int>(numberOfCitiesHelp));
}

void Graph::prepareForDynamicProggramingFindBestPath() { //funkcja odpowiadaj¹ca za przygotowanie zmiennych oraz vectror'ów do wykonania algorytmu dynamicznego programowania dla obliczenia najkrótszej œcie¿ki
	actualPathWeHave.resize(numberOfCitiesHelp); // rezerwujemy w pamiêci odpowiedni¹ liczbê komórek
	for (int i = 0; i < (1 << numberOfCitiesHelp); i++) { // pêtla odpowiadaj¹ca za wype³nienie vectora wartoœciami max
		for (int j = 0; j < numberOfCitiesHelp; j++) {
			if(i< numberOfCitiesHelp)
				actualPathWeHave[i] = INT_MAX;
		}
	}
}

int Graph::dynamicProggramingCountMinimalCost(int visitedCitiesLocal, int cityWeChecking) {

	if (allVisitedCities == visitedCitiesLocal) // tutaj sprawdzamy, czy wszystkie miasta zosta³y odwiedzone
		return weightMatrixHelp[cityWeChecking][0]; // jeœli tak to jest zwracana droga z ostatniego odwiedzonego miasta do pierwszego
	

	if (memory[visitedCitiesLocal][cityWeChecking] != 0) // tutaj sprawdzamy, czy miasto by³o ju¿ odwiedzone i jeœli by³o
		return memory[visitedCitiesLocal][cityWeChecking]; // to zwracamy œcie¿kê do niego

	int minimum = INT_MAX;

	for (int i = 0; i < numberOfCitiesHelp; i++) {
		if (cityWeChecking == i)
			continue;

		if ((visitedCitiesLocal & (1 << i)) == 0) {
			int temp = weightMatrixHelp[cityWeChecking][i] + dynamicProggramingCountMinimalCost(visitedCitiesLocal | (1 << i), i);
			if (temp < minimum || minimum == INT_MAX) {
				minimum = temp;
				bestPath[visitedCitiesLocal][cityWeChecking] = i;
			}
				
		} // w tym if'ie sprawdzana jest najoptymalniejsza œcie¿ka dla ka¿dego wierzcho³ka; nasza funkcja jest wywo³ywana rekursywnie
		// przesuniêcie bitowe wystêpuj¹ce w kolejnych wywo³aniach funkcji sprawdza miasta ju¿ odwiedzone i potem sprawdzane jest, czy œcie¿ka, która znalaz³ jest najlepsza
	}
	memory[visitedCitiesLocal][cityWeChecking] = minimum;
	return minimum; // na koniec najlepsza œcie¿ka jest zapisywana do vectora i jest zwracana
}

void Graph::dynamicProggramingFindBestPath(int visitingCity, int startingCity) {
	while (true) {
		int help = bestPath[visitingCity][startingCity]; // który wierzcho³ek aktualnie sprawdzamy
		actualPathWeHave[helpForActualPath] = help; // tutaj przechowywana jest nasza aktualna œcie¿ka
		cout << help << "--->";
		visitingCity = visitingCity | (1 << help); // tutaj mówimy visitingCity, ¿e ju¿ go odwiedziliœmy i przy nastêpnym przejœciu bêdzie odwiedzane kolejne miasto

		if ((actualPathWeHave.size() - 1) > helpForActualPath) {
			helpForActualPath++; // inkrementujemy to, ¿eby zapisaæ kolejn¹ czêœæ œcie¿ki w vectorze actualPathWeHave
			startingCity = help; // i tutaj dajemy znaæ, ¿e kolejnym odwiedzanym wierzcho³kiem bêdzie wierzcho³ek pomocniczy, czyli help
			continue;
		}
		break;
	}
}

void Graph::bruteForceCountMinimalCostAndBestPath(vector<vector<int>> weightMatrix, int& result, vector<int>& path) {
	vector<int> help;
	int i;

	help.resize(weightMatrix.size());

	for (i = 0; i < weightMatrix.size(); i++) // zape³nienie helpa indeksami wierzcho³ków
		help[i] = i;

	i = 0;
	vector<int> bestPathLocal;
	int minPath = INT_MAX, pathValue = 0;

	do {
		pathValue = 0;
		for (i = 0; i < weightMatrix.size() - 1; i++) // w tej pêtli obliczamy drogê od indeksu 0 do indeksu ostatniego z vectora help
			pathValue += weightMatrix[help[i]][help[i + 1]];

		pathValue += weightMatrix[help[i]][help[0]]; // tutaj ³¹czy siê wartoœæ od wierzcho³ka ostatniego do pocz¹tkowego, aby utworzyæ cykl

		if (pathValue < minPath) { // a w tej pêtli porównujemy wynik
			minPath = pathValue; // przekazujemy wartoœæ najkrótszej œcie¿ki 
			bestPathLocal = help; // przekazujemy drogê pokonan¹
		}
	} while (next_permutation(help.begin(), help.end())); // pêtlê wykonujemy dopóki nie wykorzystany i wykonamy wszystkich mo¿liwych permutacji przejœæ - to co ma robiæ brute force

	result = minPath;
	path = bestPathLocal; // przypisanie znalezionych wartoœci do zmiennych przekazanych przez funckjê
}