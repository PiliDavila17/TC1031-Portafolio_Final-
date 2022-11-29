// =================================================================
//
// File: main.cpp
// Author:Maria del Pilar Davila Verduzco
// Date:29/11/22
//
// =================================================================

#include <iostream>
#include <cstring>
#include "ugraph.h"
#include <string>



int main(int argc, char* argv[]) {
	//MatrixGraph

	int n;
	int consultas;

	std::cin >> n;
	UListGraph<std::string> umg(n);

	
	for (int i = 0; i < n; i++){
		  std::string s;
		  std::string s1;

		  std::cin >> s;
		  std::cin >> s1;

		  umg.addEdge(s,s1);
		  umg.addEdge(s1,s);
	};

	std::cin >> consultas;

	int intento = 1;

	for (int i = 0; i < consultas; i++){
		std::string puerto;
		int MNP;
		int puertos_tot = 0;
		int puertos_visited = 0;
		int puertos_not_visited = 0;

		std::cin >> puerto;
		std::cin >> MNP;

		std::set<string> edges = umg.getConnectionFrom(puerto);
		std::set<string>::iterator itr;

		
		edges = dfs(puerto, &umg);

		for (itr = edges.begin(); itr != edges.end(); itr++) {
		puertos_tot = puertos_tot + 1;
		}

		std::set<string> temporal;
		std::set<string> visitados = umg.getConnectionFrom(puerto);
		visitados.insert(puerto);
		std::set<string> opciones;

		std::set<string>::iterator itr2;
		std::set<string>::iterator itr3;
		std::set<string>::iterator itr4;
		

		for (int i = 0; i < MNP-1; i++){

			
			for (itr2 = visitados.begin(); itr2 != visitados.end(); itr2++){
				temporal = umg.getConnectionFrom(*itr2);

				for (itr3 = temporal.begin(); itr3 != temporal.end(); itr3++){

					if(visitados.find(*itr3) == visitados.end()){
						opciones.insert(*itr3);
					}
				}
			}

			for (itr4 = opciones.begin(); itr4 != opciones.end(); itr4++){
				visitados.insert(*itr4);

		}
		}

		puertos_visited = visitados.size();
		puertos_not_visited = puertos_tot - puertos_visited;

		std::cout << "Case " << intento << ": " << puertos_not_visited << " ports not reachable from port "<< puerto <<" with MNP = " << MNP << "\n";
		intento = intento + 1;
	}


}