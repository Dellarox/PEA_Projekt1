#include "FileReader.h"

bool FileReader::fileReadLine(ifstream& file, int tab[], int size) {
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

bool FileReader::fileReadGraph(string fileName, bool isTest, int& numberOfCities, vector<vector<int>>& weightMatrix) {
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