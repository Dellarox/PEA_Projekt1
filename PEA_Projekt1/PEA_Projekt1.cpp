#include <iostream>
#include "Graph.h"
#include "TimeTests.h"

using namespace std;

vector<vector<int>> weightMatrixGlobal;
int numberOfCitiesGlobal;
TimeTests tt;
Graph gtt;

void showRow(vector<int> weightMatrix) { // funkcja pomocnicza w wyświetlaniu macierzy
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

void showWeightMatrix(int numberOfCities, vector<vector<int>> weightMatrix) {

    if (numberOfCities == 0) {
        cout << "Nie wczytano struktury lub liczba miast wynosi 0!" << endl;
    }
    else {
        for (int i = 0; i < numberOfCities; i++) {
            showRow(weightMatrix[i]);
            cout << endl;
        }
        cout << endl;
    }
}

void doDP() {
    Graph g;
    cout << "Odległości między miastami:" << endl << endl;
    showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
    cout << endl;
    g.prepareForDynamicProggramingCountMinimalCost(numberOfCitiesGlobal, weightMatrixGlobal);
    g.prepareForDynamicProggramingFindBestPath();
    cout << "\nMinimalna długość drogi: " << g.dynamicProggramingCountMinimalCost(1, 0) << endl;
    cout << "\nŚcieżka, która jest obierana: ";
    g.dynamicProggramingFindBestPath(0, 0);
    cout << "0" << endl;
}

void doBF() {
    Graph g;
    cout << "Odległości między miastami:" << endl << endl;
    showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
    int result;
    vector<int> path;
    g.bruteForceCountMinimalCostAndBestPath(weightMatrixGlobal, result, path);
    cout << "\nMinimalna długość drogi: " << result << endl;
    cout << "\nŚcieżka, która jest obierana: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << "--->";
    }
    cout << "0" << endl;
}

void tests() {
    cout << "Programowanie dynamiczne:" << endl;
    /*tt.timeTestsForDynamicProggraming(gtt, "18_miast.txt", 18, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "19_miast.txt", 19, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "20_miast.txt", 20, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "21_miast.txt", 21, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "22_miast.txt", 22, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "23_miast.txt", 23, weightMatrixGlobal);
    tt.timeTestsForDynamicProggraming(gtt, "24_miast.txt", 24, weightMatrixGlobal);*/
    cout << "Brute force:" << endl;
    tt.timeTestsForBruteForce(gtt, "zad.txt", 10, weightMatrixGlobal);
    /*tt.timeTestsForBruteForce(gtt, "19_miast.txt", 19, weightMatrixGlobal);
    tt.timeTestsForBruteForce(gtt, "20_miast.txt", 20, weightMatrixGlobal);
    tt.timeTestsForBruteForce(gtt, "21_miast.txt", 21, weightMatrixGlobal);
    tt.timeTestsForBruteForce(gtt, "22_miast.txt", 22, weightMatrixGlobal);
    tt.timeTestsForBruteForce(gtt, "23_miast.txt", 23, weightMatrixGlobal);
    tt.timeTestsForBruteForce(gtt, "24_miast.txt", 24, weightMatrixGlobal);*/
    cout << "KONIEC TESTÓW" << endl;
}

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

    do {
        system("cls");
        cout << "Projekt PEA    Kajetan Krasoń    252767" << endl << endl;
        cout << "1. Wczytaj strukturę z pliku i ją pokaż." << endl;
        cout << "2. Pokaż wczytaną strukturę." << endl;
        cout << "3. Rozwiąż problem komiwojażera na wczytanej strukturze  - programowanie dynamiczne." << endl;
        cout << "4. Rozwiąż problem komiwojażera na wczytanej strukturze  - brute force." << endl;
        cout << "5. Testy. " << endl;
        cin >> menuOperation;

        switch (menuOperation)
        {
            case 1:
                cout << "Podaj nazwę pliku: " << endl;
                cin >> fileName;
                checker = g.fileReadGraph(fileName, false, numberOfCitiesGlobal, weightMatrixGlobal);
                break;
            case 2:
                cout << "Odległości między miastami:" << endl << endl;
                showWeightMatrix(numberOfCitiesGlobal, weightMatrixGlobal);
                break;
            case 3:
                doDP();
                break;
            case 4:
                doBF();
                cout << endl;
                break;
            case 5:
                tests();
                break;
        }

        cout << endl << "Czy chcesz kontynuować działanie aplikacji? (T lub t oznacza \"tak\")" << endl;
        cin >> menuContinue;
    } while (menuContinue == 'T' || menuContinue == 't');
}