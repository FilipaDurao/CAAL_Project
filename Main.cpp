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

//	string stop1 = "Estacao de Rio Tinto";	// ID = 0
//	string stop2 = "Baguim";				// ID = 1
//
//
//	cout << "Before inserting any node: " << grafo.getNumNodes() << endl;
//	grafo.addNode(stop1);
//	cout << "After inserting one node: " << grafo.getNumNodes() << endl;
//	cout << "The information in the first node: " << grafo.getNodes().at(0).getValue() << endl;
//
//	grafo.addNode(stop2);
//	cout << "After inserting another node: " << grafo.getNumNodes() << endl;
//	cout << "The information in the second node: " << grafo.getNodes().at(1).getValue() << endl << endl;
//
//	cout << "Number of edges before adding edge: " << grafo.getNumEdges() << endl;
//
//	grafo.addEdge(0, 1, 5);		// Source node, destiny node, weight(distance)
//
//	cout << "Number of edges after adding edge: " << grafo.getNumEdges() << endl << endl;
//
//	vector<Node<string>> nodes = grafo.getNodes();
//	vector<Edge<string>> edges = nodes.at(0).getEdges();
//
//	cout << "Source: " << nodes.at(0).getValue() << endl;
//	cout << "Destiny: " << edges.at(0).getDestiny()->getValue() << endl;
//	cout << "Distance: " << nodes.at(0).getEdges().at(0).getWeight();


	string stop0 = "0";
	string stop1 = "1";
	string stop2 = "2";
	string stop3 = "3";
	string stop4 = "4";

	grafo.addNode(stop0);
	grafo.addNode(stop1);
	grafo.addNode(stop2);
	grafo.addNode(stop3);
	grafo.addNode(stop4);


	grafo.addEdge(0, 1, 2);
	grafo.addEdge(0, 2, 8);
	grafo.addEdge(1, 3, 1);
	grafo.addEdge(3, 4, 1);
	grafo.addEdge(4, 2, 1);

	vector<Node<string> *> nodes = grafo.getNodes();

	grafo.dijsktra(nodes.at(0), nodes.at(4));


}
