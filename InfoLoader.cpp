#include "InfoLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void loadNodes(Graph<string> & grafo, GraphViewer* gv) {

	string line;
	ifstream file("nos.txt");

	if (!file.is_open()) {
		cout << "error opening file...\n";
		exit(1);
	}

	unsigned int id  = 0; // id's for graphviewer nodes
	while (getline(file, line)) {

		// -> INFO / X / Y

		string info;
		char garbage;
		int x;
		int y;

		istringstream sLine(line);

		getline(sLine, info, ';');
		sLine >> x;
		sLine >> garbage;
		sLine >> y;

		grafo.addNode(info, x, y);

		// Add the node to graphViewer
		gv->addNode(id, x/2, y/2); // dividing by 5 to fit on grid
		gv->setVertexLabel(id, info);
		gv->setVertexSize(id, 60);
		gv->rearrange();
		id++;
	}

	file.close();
}

void loadEdges(Graph<string> & grafo, GraphViewer* gv) {

	// -> ID ARESTA / NODE ID INICIO / NODE ID FINAL / TYPE / LINE

	string line;

	ifstream file("arestas.txt");

	if (!file.is_open()) {
		cout << "error opening file...\n";
		exit(1);
	}

	while (getline(file, line)) {

		int edge_id;
		int id_init;
		int id_end;
		string type;
		string lineType;
		char garbage;

		istringstream sLine(line);

		sLine >> edge_id;
		sLine >> garbage;
		sLine >> id_init;
		sLine >> garbage;
		sLine >> id_end;
		sLine >> garbage;
		getline(sLine, type, ';');
		getline(sLine, lineType, ';');

		int x_i = grafo.getNodeByID(id_init)->getX();
		int y_i = grafo.getNodeByID(id_init)->getY();

		int x_f = grafo.getNodeByID(id_end)->getX();
		int y_f = grafo.getNodeByID(id_end)->getY();

		double weight = sqrt(pow((x_f - x_i), 2) + pow((y_f - y_i), 2));

		if(type == BUS) {
			gv->addEdge(edge_id,id_init, id_end, EdgeType::DIRECTED);
			gv->setEdgeColor(edge_id, CYAN);
			gv->setEdgeLabel(edge_id, lineType);
			gv->setEdgeThickness(edge_id, 5);

			grafo.addBusEdge(id_init,id_end,weight,lineType);
		}
		else if(type == SUBWAY) {
			gv->addEdge(edge_id,id_init, id_end, EdgeType::DIRECTED);
			gv->setEdgeColor(edge_id, GREEN);
			gv->setEdgeLabel(edge_id, lineType);
			gv->setEdgeThickness(edge_id, 5);

			grafo.addSubwayEdge(id_init, id_end,weight,lineType);
		}
		else
			grafo.addWalkEdge(id_init, id_end, weight, lineType);
	}
}
