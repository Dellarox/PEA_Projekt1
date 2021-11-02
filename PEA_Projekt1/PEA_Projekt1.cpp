#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
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
        cout << "4. Testy. " << endl;
        cin >> menuOperation;

        switch (menuOperation)
        {
            case 1:
                cout << "Podaj nazwę pliku: " << endl;
                cin >> fileName;
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
                g.prepareForDynamicProggraming();
                cout << "\nMinimalna długość drogi: " << g.dynamicProggraming(0, 1) << endl;
                break;
            case 4:
                cout << "KONIEC TESTÓW" << endl; 
                break;
        }

        cout << endl << "Czy chcesz kontynuować działanie aplikacji? (T lub t oznacza \"tak\")" << endl;
        cin >> menuContinue;
    } while (menuContinue == 'T' || menuContinue == 't');
}