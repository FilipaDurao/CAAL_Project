#include "menu.h"
#include <vector>


void menu(Graph<string> &g) {
	// display the stations
	menuListStation(g);

	// ask for departure station
	unsigned int id_origin, id_dest;

	cout << "Local de partida ? ";
	cin >> id_origin;
	// TODO, validate
	cout << "Local de destino ? ";
	cin >> id_dest;
	// TODO, validate

	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), 
		*endNode = g.getNodeByID(id_dest);

	// ask for criterion
	pathCriterion criterion = getPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);

	// show the path
	//g.showpa
}

static void menuListStation(const Graph<string> &g) {
	vector<Node<string>*> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
		cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

static pathCriterion getPathCriterion() {
	cout << "Escolha um criterio\n";
	cout << "[0] - Numero de transbordos\n";
	cout << "[1] - Rotas sem caminhos a pé\n";
	cout << "[2] - Menor preço\n";
	cout << "[3] - Menor tempo de viagem\n";

	// TODO validate input
	unsigned int option;
	cin >> option;

	return (pathCriterion)option;
}

static Node<string> * run_Dijkstra(Graph<string> &g, Node<string> *startNode, Node<string> *endNode, pathCriterion criterion) {
	
	switch (criterion)
	{
	case TRANSBORDS:
		int n;
		cout << "Numero máximo de transbordos ? ";
		cin >> n; // TODO validate input
		return g.dijkstra_queue_TRANSBORDS(startNode, endNode, n);

	case NO_WALK:
		return g.dijkstra_queue_NO_WALK(startNode, endNode);

	case PRICE:
		return g.dijkstra_queue_PRICE(startNode, endNode);

	case DISTANCE:
		return g.dijkstra_queue(startNode, endNode);

	default:
		return NULL;
	}

}