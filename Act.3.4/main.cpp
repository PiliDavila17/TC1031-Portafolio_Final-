// =================================================================
//
// File: main.cpp
// Author: María del Pilar Dávila Verduzco
// Date: 20/11/2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include "Heap.h"
int main(int argc, char *argv[])
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	if (argc != 3)
	{
		std::cout << "Uso: " << argv[0] << " Input.txt Output.txt";
		return -1;
	}

	inputFile.open(argv[1]);
	if (inputFile.fail())
	{
		std::cout << "No se pudo abrir el archivo de entrada.";
		return -1;
	}

	outputFile.open(argv[2]);
	if (outputFile.fail())
	{
		std::cout << "No se pudo abrir el archivo de salida.";
		return -1;
	}

	int N, elem;
	inputFile >> N;

	MinHeap<int> heap;
	for (int i = 0; i < N; i++)
	{
		inputFile >> elem;
		heap.push(elem);
	}

	int acum = 0;
	int sum;
	while (heap.size() > 1)
	{
		sum = heap.pop() + heap.pop();
		heap.push(sum);
		acum += sum - 1;
	}
	outputFile << acum << std::endl;
}
