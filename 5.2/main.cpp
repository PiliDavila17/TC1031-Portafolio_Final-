// =================================================================
//
// File: main.cpp
// Author:Maria del Pilar Davila Verduzco
// Date:29/11/22
//
// =================================================================

#include <iostream>
#include <cstring>
#include <string>
#include "exception.h"
#include "hash.h"

using namespace std;

unsigned int myHash1(const string s) {
	unsigned int acum = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		acum += (int) s[i];
	}
	return acum;
}

unsigned int myHash2(const string s) {
	return (unsigned int) s[0];
}


int main(int argc, char* argv[]) {
	int cant_palabras = 0;
	int descripciones = 0;

	cin >> cant_palabras;
	cin >> descripciones;
	
	HashTable<string, int> hash(cant_palabras, string("empty"), myHash1); 

	for(int i = 0; i < cant_palabras; i++){
		string palabra = "";
		int valor = 0;

		cin >> palabra;
		cin >> valor;

		hash.put(string(palabra),valor);
	}

	for (int i = 0; i < descripciones; i++){
		string actual = "";
		cin >> actual;
		int acum = 0;
		while(actual != "."){
			if (hash.contains(actual)){
				acum += hash.get(actual);
			}
			cin >> actual;
		}
		
		cout << acum << "\n";
	}

	return 0;
}