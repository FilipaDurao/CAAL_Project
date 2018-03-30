/*
 * Main.cpp
 *
 *  Created on: 15/03/2018
 *      Author: filipa
 */

#include <iostream>
#include "Graph.h"
#include "Test.h"
#include "InfoLoader.h"

using namespace std;

int main() {

	Graph<string> grafo;

	grafo.addNode("0", 0, 0);

	grafo.addNode("1", 1, 0);

	grafo.addNode("2", 2, 0);

	grafo.addNode("3", 1, 4);

	grafo.addSubwayEdge(0, 1, 1, "A");
	grafo.addSubwayEdge(1, 2, 2, "B");
	grafo.addSubwayEdge(0, 2, 6, "C");

	Node<string> * lastNode;

	lastNode = grafo.dijkstra_queue_PRICE(grafo.getNodeByID(0),
			grafo.getNodeByID(2));

	cout << endl << grafo.getDetailedPath(lastNode, PRICE_MODE);

	lastNode = grafo.dijkstra_queue(grafo.getNodeByID(0), grafo.getNodeByID(2));

	cout << endl << grafo.getDetailedPath(lastNode, TIME_MODE);

//	loadNodes(grafo);
//	loadEdges(grafo);
//
//	Node<string> *lastNode;
//	vector<string> t;
//
//	lastNode = grafo.dijkstra_queue_TRANSBORDS(grafo.getNodeByID(0),
//											   grafo.getNodeByID(13), 1);
//
//	t = grafo.getPath(lastNode);
//
//	for (size_t i = 0; i < t.size(); i++)
//	{
//		if (i < (t.size() - 1))
//			cout << t.at(i) << "->";
//		else
//			cout << t.at(i);
//	}
//
//	cout << endl
//		 << grafo.getDetailedPath(lastNode) << endl;
//
//	lastNode = grafo.dijkstra_queue(grafo.getNodeByID(5),
//									grafo.getNodeByID(15));
//
//	t = grafo.getPath(lastNode);
//
//	for (size_t i = 0; i < t.size(); i++)
//	{
//		if (i < (t.size() - 1))
//			cout << t.at(i) << "->";
//		else
//			cout << t.at(i);
//	}
//
//	cout << endl;
//
//	cout << grafo.getDetailedPath(lastNode);

	/*

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

	 string stop0 = "São Bento";
	 string stop1 = "Aliados";
	 string stop2 = "Faria Guimarães";
	 string stop3 = "Marquês";
	 string stop4 = "Combatentes";

	 string line204 = "204";
	 string lineD = "D";
	 string lineA = "A";
	 string lineC = "C";
	 string line301 = "301";
	 string walk = "walk";

	 grafo.addNode(stop0, 0, 1);
	 grafo.addNode(stop1, 2, 1);
	 grafo.addNode(stop2, 3, 4);
	 grafo.addNode(stop3, 5, 6);
	 grafo.addNode(stop4, 1, 3);

	 grafo.addBusEdge(0, 2, 4, line204);
	 grafo.addBusEdge(2, 3, 4, line301);
	 grafo.addBusEdge(0, 3, 10, line301);
	 grafo.addSubwayEdge(0, 1, 1, lineA);
	 grafo.addSubwayEdge(1, 3, 1, lineD);

	 vector<Node<string> *> nodes = grafo.getNodes();
	 Node<string>* lastNode = grafo.dijkstra_queue_TRANSBORDS(
	 grafo.getNodeByID(0), grafo.getNodeByID(3), 1);

	 vector<string> t = grafo.getPath(lastNode);

	 for (size_t i = 0; i < t.size(); i++) {
	 if (i < (t.size() - 1))
	 cout << t.at(i) << "->";
	 else
	 cout << t.at(i);
	 }

	 */
}
