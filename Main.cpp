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
#include "menu.h"
#include "GraphViewer/graphviewer.h"

using namespace std;

int main() {

	Graph<string> grafo;


	loadNodes(grafo);
	loadEdges(grafo);

	menu(grafo);

}
