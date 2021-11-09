#include "TimeTests.h"

long long int TimeTests::read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForDynamicProggraming(Graph g, string fileName, int numberOfCities, vector<vector<int>> weightMatrix) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = g.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	timeOfTest = 0;
	start = read_QPC();
	for (int i = 0; i < 1; i++) {
		g.prepareForDynamicProggramingCountMinimalCost(numberOfCities, weightMatrix);
		g.dynamicProggramingCountMinimalCost(1, 0);
		g.memory.clear();
	}
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	cout << "Uœredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest/100 << "." << endl;
}

void TimeTests::timeTestsForBruteForce(Graph g, string fileName, int numberOfCities, vector<vector<int>> weightMatrix, int howMuchAttempts) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = g.fileReadGraph(fileName, true, numberOfCities, weightMatrix);
	int result;
	vector<int> path;

	timeOfTest = 0;
	start = read_QPC();
	if (howMuchAttempts == 100) 
		for (int i = 0; i < 100; i++)
			g.bruteForceCountMinimalCostAndBestPath(weightMatrix, result, path);

	if (howMuchAttempts == 30) {
		for (int i = 0; i < 30; i++)
			g.bruteForceCountMinimalCostAndBestPath(weightMatrix, result, path);
	}
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	if (howMuchAttempts == 100)
		cout << "Uœredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest/100 << "." << endl;
	if (howMuchAttempts == 30)
		cout << "Uœredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest/30 << "." << endl;
}	