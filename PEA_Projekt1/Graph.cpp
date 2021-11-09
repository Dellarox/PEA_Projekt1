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

			numberOfCities = tabNumberOfCities[0]; // przypisanie ilo�ci miast z pierwszej linijki pliku

			if (!isTest)
				cout << endl << "Ilo�� miast:" << numberOfCities << endl << endl;

			weightMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

			for (int i = 0; i < numberOfCities; i++) {
				for (int j = 0; j < numberOfCities; j++) {
					file >> weightMatrix[i][j]; // kolejne dodawanie warto�ci do vectora
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

void Graph::prepareForDynamicProggramingCountMinimalCost(int numberOfCities, vector<vector<int>> weightMatrix) { // funkcja odpowiadaj�ca za przygotowanie zmiennych oraz vectror'�w do wykonania algorytmu dynamicznego programowania dla obliczenia najkr�tszej �cie�ki
	numberOfCitiesHelp = numberOfCities;
	weightMatrixHelp = weightMatrix;
	allVisitedCities = (1 << numberOfCitiesHelp) - 1; // zmienna pomagaj�ca sprawdza� czy wszystkie miasta zosta�y odwiedzone
	memory.resize((1 << numberOfCitiesHelp), vector<int>(numberOfCitiesHelp)); // rezerwujemy w pami�ci odpowiedni� liczb� kom�rek
	bestPath.resize((1 << numberOfCitiesHelp), vector<int>(numberOfCitiesHelp));
}

void Graph::prepareForDynamicProggramingFindBestPath() { //funkcja odpowiadaj�ca za przygotowanie zmiennych oraz vectror'�w do wykonania algorytmu dynamicznego programowania dla obliczenia najkr�tszej �cie�ki
	actualPathWeHave.resize(numberOfCitiesHelp); // rezerwujemy w pami�ci odpowiedni� liczb� kom�rek
	for (int i = 0; i < (1 << numberOfCitiesHelp); i++) { // p�tla odpowiadaj�ca za wype�nienie vectora warto�ciami max
		for (int j = 0; j < numberOfCitiesHelp; j++) {
			if(i< numberOfCitiesHelp)
				actualPathWeHave[i] = INT_MAX;
		}
	}
}

int Graph::dynamicProggramingCountMinimalCost(int visitedCitiesLocal, int cityWeChecking) {

	if (allVisitedCities == visitedCitiesLocal) // tutaj sprawdzamy, czy wszystkie miasta zosta�y odwiedzone
		return weightMatrixHelp[cityWeChecking][0]; // je�li tak to jest zwracana droga z ostatniego odwiedzonego miasta do pierwszego
	

	if (memory[visitedCitiesLocal][cityWeChecking] != 0) // tutaj sprawdzamy, czy miasto by�o ju� odwiedzone i je�li by�o
		return memory[visitedCitiesLocal][cityWeChecking]; // to zwracamy �cie�k� do niego

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
				
		} // w tym if'ie sprawdzana jest najoptymalniejsza �cie�ka dla ka�dego wierzcho�ka; nasza funkcja jest wywo�ywana rekursywnie
		// przesuni�cie bitowe wyst�puj�ce w kolejnych wywo�aniach funkcji sprawdza miasta ju� odwiedzone i potem sprawdzane jest, czy �cie�ka, kt�ra znalaz� jest najlepsza
	}
	memory[visitedCitiesLocal][cityWeChecking] = minimum;
	return minimum; // na koniec najlepsza �cie�ka jest zapisywana do vectora i jest zwracana
}

void Graph::dynamicProggramingFindBestPath(int visitingCity, int startingCity) {
	while (true) {
		int help = bestPath[visitingCity][startingCity]; // kt�ry wierzcho�ek aktualnie sprawdzamy
		actualPathWeHave[helpForActualPath] = help; // tutaj przechowywana jest nasza aktualna �cie�ka
		cout << help << "--->";
		visitingCity = visitingCity | (1 << help); // tutaj m�wimy visitingCity, �e ju� go odwiedzili�my i przy nast�pnym przej�ciu b�dzie odwiedzane kolejne miasto

		if ((actualPathWeHave.size() - 1) > helpForActualPath) {
			helpForActualPath++; // inkrementujemy to, �eby zapisa� kolejn� cz�� �cie�ki w vectorze actualPathWeHave
			startingCity = help; // i tutaj dajemy zna�, �e kolejnym odwiedzanym wierzcho�kiem b�dzie wierzcho�ek pomocniczy, czyli help
			continue;
		}
		break;
	}
}

void Graph::bruteForceCountMinimalCostAndBestPath(vector<vector<int>> weightMatrix, int& result, vector<int>& path) {
	vector<int> help;
	int i;

	help.resize(weightMatrix.size());

	for (i = 0; i < weightMatrix.size(); i++) // zape�nienie helpa indeksami wierzcho�k�w
		help[i] = i;

	i = 0;
	vector<int> bestPathLocal;
	int minPath = INT_MAX, pathValue = 0;

	do {
		pathValue = 0;
		for (i = 0; i < weightMatrix.size() - 1; i++) // w tej p�tli obliczamy drog� od indeksu 0 do indeksu ostatniego z vectora help
			pathValue += weightMatrix[help[i]][help[i + 1]];

		pathValue += weightMatrix[help[i]][help[0]]; // tutaj ��czy si� warto�� od wierzcho�ka ostatniego do pocz�tkowego, aby utworzy� cykl

		if (pathValue < minPath) { // a w tej p�tli por�wnujemy wynik
			minPath = pathValue; // przekazujemy warto�� najkr�tszej �cie�ki 
			bestPathLocal = help; // przekazujemy drog� pokonan�
		}
	} while (next_permutation(help.begin(), help.end())); // p�tl� wykonujemy dop�ki nie wykorzystany i wykonamy wszystkich mo�liwych permutacji przej�� - to co ma robi� brute force

	result = minPath;
	path = bestPathLocal; // przypisanie znalezionych warto�ci do zmiennych przekazanych przez funckj�
}