#include "TimeTests.h"

long long int TimeTests::read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForDynamicProggraming(Graph g, string fileName) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	bool checker = g.fileReadGraph(fileName, true);

	if (!checker) {
		cout << "Nie ma takiego pliku!" << endl;
		system("pause");
	}

	timeOfTest = 0;

	start = read_QPC();
	for (int i = 0; i < 100; i++) {
		g.prepareForDynamicProggraming();
		g.dynamicProggraming(0, 1);
		g.memory.clear();
	}
	elapsed = read_QPC() - start;
	timeOfTest = (1.0 * elapsed) / frequency;
	cout << "Czas testów dla " << g.numberOfCities << " miast w [s]: " << timeOfTest << "." << endl;
}