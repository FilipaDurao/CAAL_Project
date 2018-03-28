#include "InfoLoader.h"
#include <cmath>

void loadNodes(Graph<string> & grafo) {

	string line;

	ifstream file("nos.txt");

	if (!file.is_open()) {
		cout << "error opening file...\n";
		exit(1);
	}

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

//		cout << info << x << "|" << y << endl;

		grafo.addNode(info, x, y);

	}

	file.close();

}

void loadEdges(Graph<string> & grafo) {

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

//		cout << edge_id << "|" << id_init << "|" << id_end << "|" << type << "|"
//				<< lineType << endl;

		int x_i = grafo.getNodeByID(id_init)->getX();
		int y_i = grafo.getNodeByID(id_init)->getY();

		int x_f = grafo.getNodeByID(id_end)->getX();
		int y_f = grafo.getNodeByID(id_end)->getY();

		double weight = sqrt(pow((x_f - x_i), 2) + pow((y_f - y_i), 2));

		if(type == BUS)
			grafo.addBusEdge(id_init,id_end,weight,lineType);
		else if(type == METRO)
			grafo.addMetroEdge(id_init, id_end,weight,lineType);
		else
			grafo.addWalkEdge(id_init, id_end, weight, lineType);
	}
}
