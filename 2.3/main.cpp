// =================================================================
//
// File: main.cpp
// Author: María del Pilar Dávila Verduzco
// Date: 17/10/2021
//
// =================================================================
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ship.h"
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;
    ofstream outputFile;

    if (argc != 3)
    {
        cout << "Uso: " << argv[0] << " Input.txt Output.txt";
        return -1;
    }

    inputFile.open(argv[1]);
    if (inputFile.fail())
    {
        cout << "No se pudo abrir el archivo de entrada.";
        return -1;
    }

    outputFile.open(argv[2]);
    if (outputFile.fail())
    {
        cout << "No se pudo abrir el archivo de salida.";
        return -1;
    }

    int N;
    std::string find, date, time, UBI;
    char origin;

    inputFile >> N >> find;

    vector<Ship> ships;

    for (int i = 0; i < N; i++)
    {
        inputFile >> date >> time >> origin >> UBI;

        if (UBI.substr(0, 3) == find)
            ships.push_back(Ship(date, time, origin, UBI));
    }

    std::sort(ships.begin(), ships.end());

    std::string months[] = {"jan", "feb", "mar", "apr", "may", "jun",
                            "jul", "aug", "sep", "oct", "nov", "dec"};
    int ship_count = 0;

    std::vector<std::string> m;
    std::vector<std::string> r;

    for (int i = 1; i <= 12; i++)
    {
        while (ships[ship_count].get_month() == i)
        {
            if (ship_count >= ships.size())
                break;

            else if (ships[ship_count].get_origin() == 'M')
                m.push_back(ships[ship_count].get_UBI());

            else
                r.push_back(ships[ship_count].get_UBI());

            ship_count;
        }

        outputFile << months[i - 1] << std::endl;

        if (m.size() > 0)
        {
            outputFile << "M " << m.size() << ": ";

            for (const auto &ship : m)
                outputFile << ship << ' ';

            outputFile << std::endl;
        }

        if (r.size() > 0)
        {
            outputFile << "R " << r.size() << ": ";

            for (const auto &ship : r)
                outputFile << ship << ' ';

            outputFile << std::endl;
        }

        m.clear();
        r.clear();
    }

    return 0;
}
