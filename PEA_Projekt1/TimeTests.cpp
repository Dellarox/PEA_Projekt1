#include "TimeTests.h"

long long int TimeTests::read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForDynamicProggraming(Graph g, FileReader fr, string fileName, int numberOfCities, vector<vector<int>> weightMatrix) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = fr.fileReadGraph(fileName, true, numberOfCities, weightMatrix);

	timeOfTest = 0;
	start = read_QPC();
	for (int i = 0; i < 10; i++) {
		g.prepareForDynamicProggramingCountMinimalCost(numberOfCities, weightMatrix);
		g.dynamicProggramingCountMinimalCost(0, 1);
		g.memory.clear();
	}
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	cout << "Uœredniony czas testów dla " << numberOfCities << " miast w [s]: " << timeOfTest/100 << "." << endl;
}