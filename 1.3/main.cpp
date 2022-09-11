// =================================================================
// File: main.cpp
// Author: Maria del Pilar Davila Verduzco
// Matricula: A01708943
// Date:11/09/2022
// Compilacion: g++ -std=c++11 main.cpp -o app --> ./app input_file output_file
// =================================================================
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <time.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include "insertion.h"

int main(int argc, char *argv[])
{
  ifstream inputFile;
  ofstream outputFile;

  if (argc !=3){
		cout<<"Uso: "<<argv[0]<<"Input.txt Output.txt";
		return -1;
	}
	inputFile.open(argv[1]);
	if (inputFile.fail()){
		cout<<"No se pudo abrir el archivo de entrada";
		return -1;
	}
	outputFile.open(argv[2]);
	if(outputFile.fail()){
		cout<<"No se pudo abrir el archivo de salida.";
		return -1;
	}

  int n;
  std::string idSearch, date, hour, port, id;

  // Ship struct
  struct shipStruct
  {
    int year;
    int month;
    int day;
    std::string dateString;
    std::string hour;
    std::string port;
    std::string id;
  };
  // Ships vector
  vector<shipStruct> ships;

  // Read file
  inputFile >> n;
  inputFile >> idSearch;

  for (int i = 0; i < n; i++)
  {
    // Read file
    inputFile >> date >> hour >> port >> id;

    // Parse date
    std::string day = date.substr(0, date.find("-"));
    std::string month = date.substr(3, date.find("-"));
    std::string year = date.substr(6);

    // Find ships with idSearch in id
    std::size_t found = id.rfind(idSearch);
    if (found != string::npos)
    {
      // Add ship to ships vector
      ships.push_back({stoi(year), stoi(month), stoi(day), date, hour, port, id});
    }
  }

  // Sort ships vector by day and then my month with insertion sort algorithm
  insertionSortDay(ships);
  insertionSortMonth(ships);

  // Write output file
  for (int i = 0; i < ships.size(); i++)
  {
    outputFile << ships[i].dateString << " " << ships[i].hour << " " << ships[i].port << " " << ships[i].id << "\n";
  }

  inputFile.close();
  outputFile.close();

  return 0;
}