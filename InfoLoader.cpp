#include "InfoLoader.h"

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

		cout << info << x << "|" << y << endl;

		grafo.addNode(info, x, y);

	}

	file.close();

}
