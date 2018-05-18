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
#include "stringSearch.h"
#include "menu.h"
#include "GraphViewer/graphviewer.h"

using namespace std;

int main() {

	Graph<string> grafo;


	loadNodes(grafo);
	loadEdges(grafo);
	grafo.findInterfaces();
	map<string, set<string>> test = grafo.listStationsByLine;
	
	for(auto itLines = test.begin(); itLines != test.end(); itLines++) {
		cout << "Line " << itLines->first << endl;
		for(auto itStations = itLines->second.begin(); itStations != itLines->second.end(); itStations++) {
			cout << *itStations << endl;
		}
		cout << endl << endl;
	}

	menu(grafo);
}
