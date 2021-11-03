#include <iostream>
#include "Graph.h"
#include "TimeTests.h"

using namespace std;

int main()
{
    srand(time(NULL));
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    setlocale(LC_ALL, "polish");

    int menuOperation;
    char menuContinue;
    string fileName;
    bool checker;
    Graph g;
    TimeTests tt;

    do {
        system("cls");
        cout << "Projekt PEA    Kajetan Krasoń    252767" << endl << endl;
        cout << "1. Wczytaj strukturę z pliku i ją pokaż." << endl;
        cout << "2. Pokaż wczytaną strukturę." << endl;
        cout << "3. Rozwiąż problem komiwojażera na wczytanej strukturze  - programowanie dynamiczne." << endl;
        cout << "4. Testy. " << endl;
        cin >> menuOperation;

        switch (menuOperation)
        {
            case 1:
                cout << "Podaj nazwę pliku: " << endl;
                //cin >> fileName;
                fileName = "20_miast.txt";
                checker = g.fileReadGraph(fileName, false);

                if (!checker) {
                    cout << "Nie ma takiego pliku!" << endl;
                    system("pause");
                    return 0;
                }
                break;
            case 2:
                g.showWeightMatrix();
                break;
            case 3:
                cout << "Odległości między miastami:" << endl << endl;
                g.showWeightMatrix();
                cout << endl;

                start = tt.read_QPC();
                g.prepareForDynamicProggraming();
                cout << "\nMinimalna długość drogi: " << g.dynamicProggraming(0, 1) << endl;
                elapsed = tt.read_QPC() - start;
                cout << "Czas testów dla " << g.numberOfCities << " miast w [s]: " << (1.0 * elapsed) / frequency << "." << endl;

                tt.timeTestsForDynamicProggraming(g, "20_miast.txt");
                break;
            case 4:
                //tt.timeTestsForDynamicProggraming(g, "18_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "20_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "22_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "23_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "24_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "25_miast.txt");
                //tt.timeTestsForDynamicProggraming(g, "26_miast.txt");
                cout << "KONIEC TESTÓW" << endl; 
                break;
        }

        cout << endl << "Czy chcesz kontynuować działanie aplikacji? (T lub t oznacza \"tak\")" << endl;
        cin >> menuContinue;
    } while (menuContinue == 'T' || menuContinue == 't');
}