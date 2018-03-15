/*
 * Main.cpp
 *
 *  Created on: 15/03/2018
 *      Author: filipa
 */

#include <iostream>
#include "Graph.h"

using namespace std;

int main(){

	Graph<string> grafo;

	string stop = "EstacaoRioTinto";
	cout << grafo.getNumNodes();
	grafo.addNode(stop);
	cout << grafo.getNumNodes();

}
