#include "menu.h"
#include <vector>

/**
 * @brief Generic function to get input (integers) from the user to navigate through menus
 *
 * @param lower_bound The lower option number
 * @param upper_bound The upper option number
 * @param out_question The question to display to the user
 *
 * @return The value typed by the user
 */
static int getMenuOptionInput(int lower_bound, int upper_bound, string out_question) {
	int opt;
	bool success = false;

	do {
		cout << out_question << " ? ";
		cin >> opt;

		if(cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			success = false;
		}
		else {
			success = true;
			cin.ignore(1000, '\n');
		}

	} while(!success || opt < lower_bound || opt > upper_bound);

	return opt;
}

void menu(Graph<string>& g) {

	cout << "\n\nWELCOME TO TRIP PLANNER! \n\n";
	cout << "Press enter to continue...\n";
	getchar();
	bool exit = false;

	while (!exit) {
		menuStart(g);
		exit = wantToExit();
	}

	cout << "\n\nClosing...";
}

void menuStart(Graph<string>& g) {
	int option;
	cout << "\n\n";
	cout << "Do you want to: \n";
	cout << "[0] - View the full map\n";
	cout << "[1] - Plan the trip\n\n";

	option = getMenuOptionInput(0,1,"Option");

	if(option == 0) {
		showGraphViewer(g);
	}
	else {
		menuChooseStations(g);
	}
}

void menuChooseStations(Graph<string> &g) {
	// List all stations
	showListStation(g);

	// ask for departure station
	int id_origin, id_dest;
	cout << endl;
	id_origin = getMenuOptionInput(0, g.getNumNodes() - 1, "Departure station");
	id_dest = getMenuOptionInput(0, g.getNumNodes() - 1, "Arrival station");

	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), *endNode = g.getNodeByID(id_dest);

	// ask for criterion
	pathCriterion criterion = menuPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);

	vector<Node<string>*> invertedPath = g.getDetailedPath(lastNode);

	g.presentPath(invertedPath);

	vector<string> t = g.getPath(lastNode);

	presentPath(t);

	// Show map
	invertedPath.push_back(startNode);
	
	buildGraphViewerDeatiledPath(g,invertedPath);
}

pathCriterion menuPathCriterion() {
	cout << "\n\nEscolha um criterio\n";
	cout << "[0] - Numero de transbordos\n";
	cout << "[1] - Rotas sem caminhos a pe\n";
	cout << "[2] - Menor preco\n";
	cout << "[3] - Menor tempo de viagem\n\n";

	string option_s;
	int option = getMenuOptionInput(0,3, "Option");

	cout << endl << endl;

	return (pathCriterion) option;
}

Node<string> * run_Dijkstra(Graph<string> &g, Node<string> *startNode,
		Node<string> *endNode, pathCriterion criterion) {

	switch (criterion) {
	case TRANSBORDS: {
		string num_transb_s;
		int num_transb;
		cout << "Numero maximo de transbordos ? ";
		cin >> num_transb_s;
		if (!isNumber(num_transb_s)) {
			while (!isNumber(num_transb_s)) {
				cout << "Numero maximo de transbordos ? ";
				cin >> num_transb_s;
				cin.ignore(1000, '\n');
			}
		}
		num_transb = stoi(num_transb_s);
		return g.dijkstra_queue_TRANSBORDS(startNode, endNode, num_transb);
	}

	case NO_WALK:
		return g.dijkstra_queue_NO_WALK(startNode, endNode);

	case PRICE: {
		double walk_distance;
		string walk_d_s;
		cout << "Distancia maxima que pretende andar a pe? ";
		cin >> walk_d_s;
		if (!isNumber(walk_d_s)) {
			while (!isNumber(walk_d_s)) {
				cout << "Distancia maxima que pretende andar a pe? ? ";
				cin >> walk_d_s;
				cin.ignore(1000, '\n');
			}
		}
		walk_distance = stoi(walk_d_s);
		return g.dijkstra_queue_PRICE(startNode, endNode, walk_distance);
	}

	case DISTANCE:
		return g.dijkstra_queue(startNode, endNode);

	default:
		return NULL;
	}
}


// utility functions
bool wantToExit() {

	cout << "\n\n\nDo you want to: \n";
	cout << "[0] - Continue using TripPlanner\n";
	cout << "[1] - Exit\n";

	int opt = getMenuOptionInput(0,1,"Option");

	return (opt == 0 ? false : true);
}

void showListStation(const Graph<string> &g) {
	vector<Node<string>*> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
		cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

void presentPath(vector<string> t) {
	for (size_t i = 0; i < t.size(); i++) {
		if (i < (t.size() - 1))
			cout << t.at(i) << "->";
		else
			cout << t.at(i);
	}
}

// Graph viewer
void showGraphViewer(Graph<string>& g) {
	GraphViewer *gv = buildGraphViewer(g);

	cout << "Press any key to close window ...\n";
	getchar();
	gv->closeWindow();
}

GraphViewer* buildGraphViewer(Graph<string>& g) {
	GraphViewer *gv = new GraphViewer(2000,2000,false);
	gv->createWindow(1000,1000);

	// edge id's
	int edge_id = 0;
	// Get the nodes
	vector<Node<string>*> nodes = g.getNodes();
	for(size_t i = 0; i < nodes.size(); i++){
		// add the node to graphViewer
		Node<string>* n = nodes.at(i);
		gv->addNode(n->getId(), n->getX()/2, n->getY()/2);
		gv->setVertexSize(n->getId(), 60);
		gv->setVertexLabel(n->getId(), n->getInfo());

		// add  the edges (this might not work because not all nodes are defined yet)
		vector<Edge<string>> edges = nodes.at(i)->getEdges();
		for(size_t j = 0; j < edges.size(); j++) {
			if(edges.at(j).getType() != "walk") {
				gv->addEdge(edge_id, n->getId(), edges.at(j).getDestiny()->getId(), EdgeType::DIRECTED);
				gv->setEdgeLabel(edge_id, edges.at(j).getLineID());
				gv->setEdgeThickness(edge_id, 5);

				setGraphViewerEdgeColor(gv, edge_id, edges.at(j).getLineID());

				edge_id++;
			}
		}

		gv->rearrange();
	}

	gv->rearrange();
	return gv;
}

GraphViewer* buildGraphViewerDeatiledPath(Graph<string>& g, vector<Node<string>*> nodes) {
	// build the whole map
	GraphViewer *gv = buildGraphViewer(g);

	// Change path nodes color
	for(unsigned int i = 0; i < nodes.size(); i++) {
		gv->setVertexColor(nodes.at(i)->getId(), RED);
	}

	return gv;
}

void setGraphViewerEdgeColor(GraphViewer *gv, int edge_id, string lineID) {
	if(lineID == "B")
		gv->setEdgeColor(edge_id, RED);
	else if (lineID == "F")
		gv->setEdgeColor(edge_id, ORANGE);
	else if (lineID == "D")
		gv->setEdgeColor(edge_id, YELLOW);
	else if (lineID == "401")
		gv->setEdgeColor(edge_id, GREEN);
	else if (lineID == "204")
		gv->setEdgeColor(edge_id, CYAN);
	else if (lineID == "803")
		gv->setEdgeColor(edge_id, MAGENTA);

}

/**
 * @param input - any string
 *
 * @brief Checks if the string is a number, with no alphabetic characters
 *
 * @return bool - whether is true or false that the string is a number (true if it is, false otherwise)
 */
bool isNumber(string input) {

	for (unsigned int i = 0; i < input.size(); i++) {
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}



