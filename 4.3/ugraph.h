/*
 * graph.h
 *
 *  Created on: 3/11/2018
 *      Author: pperezm
 */

#ifndef UGRAPH_H_
#define UGRAPH_H_

#include <sstream>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include "exception.h"
#include "header.h"

/***********************************************************/
/********************** UnweightedGraph ********************/
/***********************************************************/

template<class Vertex>
class UnweightedGraph {
public:
	virtual void addEdge(Vertex, Vertex) = 0;
	virtual bool containsVertex(Vertex) const = 0;
	virtual std::vector<Vertex> getVertexes() const = 0;
	virtual std::set<Vertex> getConnectionFrom(Vertex) const = 0;
	virtual std::string toString() const = 0;
};

/***********************************************************/
/************************ UMatrixGraph *********************/
/***********************************************************/
template<class Vertex>
class UMatrixGraph : public UnweightedGraph<Vertex>{
private:
	int next, size;
	bool direction;
	std::vector<Vertex> vertexes;
	std::vector<std::vector<bool> > edges;

	int indexOf(Vertex v) const;

public:
	UMatrixGraph(int, bool dir = true);
	void addEdge(Vertex from, Vertex to);
	bool containsVertex(Vertex v) const;
	std::vector<Vertex> getVertexes() const;
	std::set<Vertex> getConnectionFrom(Vertex v) const;
	std::string toString() const;
};

template <class Vertex>
UMatrixGraph<Vertex>::UMatrixGraph(int max, bool dir) {
	size = max;
	if (size == 0) {
        throw RangeError();
	}

	next = 0;
	direction = dir;
	vertexes.resize(size);
	edges.resize(size);
	for (int i = 0; i < size; i++) {
		edges[i].resize(size, false);
		edges[i][i] = true;
	}
}

template <class Vertex>
int UMatrixGraph<Vertex>::indexOf(Vertex v) const {
	for (int i = 0; i < next; i++) {
		if (vertexes[i] == v) {
			return i;
		}
	}
	return -1;
}

template <class Vertex>
void UMatrixGraph<Vertex>::addEdge(Vertex from, Vertex to) {
	int fp = indexOf(from);
	if (fp == -1) {
		if (next == size) {
			throw OutOfMemory();
		}

		vertexes[next++] = from;
		fp = next - 1;
	}

	int tp = indexOf(to);
	if (tp == -1) {
		if (next == size) {
			throw OutOfMemory();
		}

		vertexes[next++] = to;
		tp = next - 1;
	}

	edges[fp][tp] = true;
	if (!direction) {
		edges[tp][fp] = true;
	}
}

template <class Vertex>
bool UMatrixGraph<Vertex>::containsVertex(Vertex v) const {
	return (indexOf(v) != -1);
}

template <class Vertex>
std::vector<Vertex> UMatrixGraph<Vertex>::getVertexes() const {
	std::vector<Vertex> result(vertexes);
	return result;
}

template <class Vertex>
std::set<Vertex> UMatrixGraph<Vertex>::getConnectionFrom(Vertex v) const {
	int i = indexOf(v);
	if (i == -1) {
		throw NoSuchElement();
	}

	std::set<Vertex> result;
	for (int j = 0; j < next; j++) {
		if (i != j && edges[i][j]) {
			result.insert(vertexes[j]);
		}
	}
	return result;
}

template <class Vertex>
std::string UMatrixGraph<Vertex>::toString() const {
	std::stringstream aux;

	for (int i = 0; i < next; i++) {
		aux << vertexes[i] << "\t";
		for (int j = 0; j < next; j++) {
			aux << edges[i][j] << "\t";
		}
		aux << "\n";
	}
	aux << "\n";
	return aux.str();
}

/***********************************************************/
/************************ UListGraph ***********************/
/***********************************************************/

template<class Vertex>
class UListGraph : public UnweightedGraph<Vertex>{
private:
	bool direction;
	std::set<Vertex> vertexes;
	std::map<Vertex, std::set<Vertex> > edges;

public:
	UListGraph(bool dir = true);
	void addEdge(Vertex from, Vertex to);
	bool containsVertex(Vertex v) const;
	std::vector<Vertex> getVertexes() const;
	std::set<Vertex> getConnectionFrom(Vertex v) const;
	std::string toString() const;
};

template <class Vertex>
UListGraph<Vertex>::UListGraph(bool dir) {
	direction = dir;
}

template <class Vertex>
void UListGraph<Vertex>::addEdge(Vertex from, Vertex to) {
	typename std::set<Vertex>::iterator it;
	typename std::list<Vertex>::iterator j;

	it = vertexes.find(from);
	if (it == vertexes.end()) {
		vertexes.insert(from);
		edges.insert(std::pair<Vertex,std::set<Vertex> >(from, std::set<Vertex>()));
	}

	it = vertexes.find(to);
	if (it == vertexes.end()) {
		vertexes.insert(to);
		edges.insert(std::pair<Vertex,std::set<Vertex> >(to, std::set<Vertex>()));
	}

	edges[from].insert(to);
	if (!direction) {
		edges[to].insert(from);
	}
}

template <class Vertex>
bool UListGraph<Vertex>::containsVertex(Vertex v) const {
	return (vertexes.find(v) != vertexes.end());
}

template <class Vertex>
std::vector<Vertex> UListGraph<Vertex>::getVertexes() const {
	std::vector<Vertex> result(vertexes.begin(), vertexes.end());
	return result;
}

template <class Vertex>
std::set<Vertex> UListGraph<Vertex>::getConnectionFrom(Vertex v) const {
	std::set<Vertex> result(edges.at(v));
	return result;
}

template <class Vertex>
std::string UListGraph<Vertex>::toString() const {
	std::stringstream aux;

	typename std::set<Vertex>::iterator i;
	typename std::set<Vertex>::const_iterator j;

	for (i = vertexes.begin(); i != vertexes.end(); i++) {
		aux << (*i) << "\t";
		for (j = edges.at((*i)).begin(); j != edges.at((*i)).end(); j++) {
			aux << (*j) << "\t";
		}
		aux << "\n";
	}
	aux << "\n";
	return aux.str();
}

/***********************************************************/
/**************************** DFS **************************/
/***********************************************************/

template <class Vertex>
std::set<Vertex> dfs(const Vertex& start,
	const UnweightedGraph<Vertex>* graph) { /*como parámetros pide dónde empieza y la dirección del grafo*/

	std::set<Vertex> visited; /*set es un contenedor*/
	std::stack<Vertex> pending; /*un stack con los vertex pendientes*/
	typename std::set<Vertex>::iterator itr; /*set que almacena iteradores apuntando a vertices*/

	pending.push(start); /*al pending se le agrega el vertice start, (donde quieres que empiece)*/
	while (!pending.empty()) { /*mientras el stack no esté vacío*/
		Vertex v = pending.top(); pending.pop(); /*creas la variable v que almacena el primer valor del stack pending y remúevelo*/
		if (visited.find(v) == visited.end()) { /*Si el elemento no está en el set visisted.... find en set busca un elemento y devuelve un iterador, si no lo encuentra regresa lo equivalente a set.end().  */
			visited.insert(v); /*agrega el elemento a visited*/
			std::set<Vertex> connected =  graph->getConnectionFrom(v);/*creas un set que contiene los vertices conectados al vertice actual*/
			for (itr = connected.begin(); itr != connected.end(); itr++) { /*se asgina itr a un iterador apuntando al primer valor, si aún no se han recorrido las conexiones del vertice, entonces agrega al stack pending el valor. conectado al vertice actual, función de la estructura set que regresa un iterador apuntando al primer elemento */
				pending.push( (*itr) ); /*agregas los valores conectados al vertice dado al stack de pending.*/
			}
		}
	}
	return visited; /*regresa los visitados*/
}


/***********************************************************/
/**************************** Cantidad_puertos **************************/
/***********************************************************/

template <class Vertex>
int cantidad(const Vertex& start,
	const UnweightedGraph<Vertex>* graph) { /*como parámetros pide dónde empieza y la dirección del grafo*/
    int cont = 0;
	std::set<Vertex> visited; /*set es un contenedor*/
	std::stack<Vertex> pending; /*un stack con los vertex pendientes*/
	typename std::set<Vertex>::iterator itr; /*set que almacena iteradores apuntando a vertices*/

	pending.push(start); /*al pending se le agrega el vertice start, (donde quieres que empiece)*/
	while (!pending.empty()) { /*mientras el stack no esté vacío*/
		Vertex v = pending.top(); pending.pop(); /*creas la variable v que almacena el primer valor del stack pending y remúevelo*/
		if (visited.find(v) == visited.end()) { /*Si el elemento no está en el set visisted.... find en set busca un elemento y devuelve un iterador, si no lo encuentra regresa lo equivalente a set.end().  */
			visited.insert(v); /*agrega el elemento a visited*/
            cont = cont + 1;
			std::set<Vertex> connected =  graph->getConnectionFrom(v);/*creas un set que contiene los vertices conectados al vertice actual*/
			for (itr = connected.begin(); itr != connected.end(); itr++) { /*se asgina itr a un iterador apuntando al primer valor, si aún no se han recorrido las conexiones del vertice, entonces agrega al stack pending el valor. conectado al vertice actual, función de la estructura set que regresa un iterador apuntando al primer elemento */
				pending.push( (*itr) ); /*agregas los valores conectados al vertice dado al stack de pending.*/
			}
		}
	}
	return cont; /*regresa los visitados*/
}
/***********************************************************/
/**************************** DFS MODIFICADO **************************/
/***********************************************************/

template <class Vertex>
std::set<Vertex> dfs_mod(const Vertex& start, const UnweightedGraph<Vertex>* graph, int MNP) { /*como parámetros pide dónde empieza, la dirección del grafo y el MNP (saltos)  */
	std::set<Vertex> visited; /*set es un contenedor*/
	std::stack<Vertex> pending; /*un stack con los vertex pendientes*/
	typename std::set<Vertex>::iterator itr; /*set que almacena iteradores apuntando a vertices*/
	pending.push(start); /*al pending se le agrega el vertice start, (donde quieres que empiece)*/
	while (!pending.empty() && MNP > 0) { /*mientras el stack no esté vacío*/
		Vertex v = pending.top(); pending.pop(); /*creas la variable v que almacena el primer valor del stack pending y remúevelo*/
        MNP = MNP -1;
		if (visited.find(v) == visited.end()) { /*Si el elemento no está en el set visited.... find en set busca un elemento y devuelve un iterador, si no lo encuentra regresa lo equivalente a set.end().  */
			visited.insert(v); /*agrega el elemento a visited*/
			std::set<Vertex> connected =  graph->getConnectionFrom(v);/*creas un set que contiene los vertices conectados al vertice actual*/
			for (itr = connected.begin(); itr != connected.end(); itr++) { /*se asgina itr a un iterador apuntando al primer valor, si aún no se han recorrido las conexiones del vertice, entonces agrega al stack pending el valor. conectado al vertice actual, función de la estructura set que regresa un iterador apuntando al primer elemento */
				pending.push( (*itr) ); /*agregas los valores conectados al vertice dado al stack de pending.*/
			}
		}
	}
	return visited; /*regresa los visitados*/
}

/***********************************************************/
/**************************** BFS **************************/
/***********************************************************/

template <class Vertex>
std::set<Vertex> bfs(const Vertex& start, const UnweightedGraph<Vertex>* graph) {
	std::set<Vertex> visited;
	std::queue<Vertex> pending;
	typename std::set<Vertex>::iterator itr;

	pending.push(start);
	while (!pending.empty()) {
		Vertex v = pending.front(); pending.pop();
		if (visited.find(v) == visited.end()) {
			visited.insert(v);
			std::set<Vertex> connected =
					graph->getConnectionFrom(v);

			for (itr = connected.begin();
					itr != connected.end(); itr++) {
				pending.push( (*itr) );
			}
		}
	}
	return visited;
}

#endif
