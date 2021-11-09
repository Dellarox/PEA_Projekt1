#include "Graph.h"

void Graph::prepareForDynamicProggramingCountMinimalCost(int numberOfCities, vector<vector<int>>& weightMatrix) {
	visitedCities = (1 << numberOfCities) - 1; // zmienna pomagaj¹ca sprawdzaæ czy wszystkie miasta zosta³y odwiedzone
	memory.resize((1 << numberOfCities), vector<int>(numberOfCities)); // rezerwujemy w pamiêci odpowiedni¹ liczbê komórek
	bestPath.resize((1 << numberOfCities), vector<int>(numberOfCities));
	numberOfCitiesHelp = numberOfCities;
	weightMatrixHelp = weightMatrix;
}

void Graph::prepareForDynamicProggramingFindBestPath(int numberOfCities) {
	actualPathWeHave.resize(numberOfCities);
	for (int i = 0; i < (1 << numberOfCities); i++) {
		for (int j = 0; j < numberOfCities; j++) {
			if(i<numberOfCities)
				actualPathWeHave[i] = INT_MAX;
		}
	}
}

int Graph::dynamicProggramingCountMinimalCost(int visitedCitiesLocal, int cityWeChecking) {

	if (visitedCities == visitedCitiesLocal) // tutaj sprawdzamy, czy wszystkie miasta zosta³y odwiedzone
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
		int help = bestPath[visitingCity][startingCity];
		actualPathWeHave[helpForActualPath] = help;
		cout << help << "--->";
		visitingCity = visitingCity | (1 << help);

		if ((actualPathWeHave.size() - 1) > helpForActualPath) {
			helpForActualPath++;
			startingCity = help;
			continue;
		}
		break;
	}
}

void Graph::bruteForceCountMinimalCostAndBestPath(vector<vector<int>> weightMatrix, int& result, vector<int>& path) {
	vector<int> help;
	int i;

	help.resize(weightMatrix.size());

	for (i = 0; i < weightMatrix.size(); i++)
		help[i] = i;

	i = 0;
	vector<int> bestPathLocal;
	int minPath = INT_MAX, pathLocal = 0;

	do {
		pathLocal = 0;
		for (i = 0; i < weightMatrix.size() - 1; i++)
			pathLocal += weightMatrix[help[i]][help[i + 1]];

		pathLocal += weightMatrix[help[i]][help[0]];

		if (pathLocal < minPath) {
			minPath = pathLocal;
			bestPathLocal = help;
		}
	} while (next_permutation(help.begin(), help.end()));

	result = minPath;
	path = bestPathLocal;
}