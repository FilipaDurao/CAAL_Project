#include "menu.h"
#include <vector>

void menu(Graph<string> &g) {
	// display the stations
	menuListStation(g);
	cout << endl;
	// ask for departure station
	unsigned int id_origin, id_dest;

	cout << "Local de partida ? ";
	cin >> id_origin;
	// TODO, validate
	cout << "Local de destino ? ";
	cin >> id_dest;
	// TODO, validate

	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), *endNode =
			g.getNodeByID(id_dest);

	// ask for criterion
	cout << endl;
	pathCriterion criterion = getPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);

//	if (criterion == DISTANCE) {
//		cout << g.getDetailedPath(lastNode, TIME_MODE) << endl;
//	}
//	else {
//		// TODO
//		cout << g.getDetailedPath(lastNode, PRICE_MODE) << endl;
//	}

	cout << g.getDetailedPath(lastNode) << endl;

	vector<string> t = g.getPath(lastNode);

	for (size_t i = 0; i < t.size(); i++) {
		if (i < (t.size() - 1))
			cout << t.at(i) << "->";
		else
			cout << t.at(i);
	}
}

static void menuListStation(const Graph<string> &g) {
	vector<Node<string>*> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
		cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

static pathCriterion getPathCriterion() {
	cout << "Escolha um criterio\n";
	cout << "[0] - Numero de transbordos\n";
	cout << "[1] - Rotas sem caminhos a p�\n";
	cout << "[2] - Menor pre�o\n";
	cout << "[3] - Menor tempo de viagem\n\n";

	// TODO validate input
	cout << "Criterio ? ";
	unsigned int option;
	cin >> option;

	return (pathCriterion) option;
}

static Node<string> * run_Dijkstra(Graph<string> &g, Node<string> *startNode,
		Node<string> *endNode, pathCriterion criterion) {

	switch (criterion) {
	case TRANSBORDS:
		int n;
		cout << "Numero m�ximo de transbordos ? ";
		cin >> n; // TODO validate input
		return g.dijkstra_queue_TRANSBORDS(startNode, endNode, n);

	case NO_WALK:
		return g.dijkstra_queue_NO_WALK(startNode, endNode);

	case PRICE:
		double walk_distance;
		cout << "Distancia maxima que pretende andar a pe? ";
		cin >> walk_distance;
		return g.dijkstra_queue_PRICE(startNode, endNode, walk_distance);

	case DISTANCE:
		return g.dijkstra_queue(startNode, endNode);

	default:
		return NULL;
	}

}
