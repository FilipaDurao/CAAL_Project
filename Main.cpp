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

	GraphViewer *gv = new GraphViewer(1000,1000,false);
	gv->createWindow(1000,1000);
	gv->defineEdgeCurved(true);
	loadNodes(grafo, gv);
	loadEdges(grafo, gv);
	getchar();

	menu(grafo);

}
