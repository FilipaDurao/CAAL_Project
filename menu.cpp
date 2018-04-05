#include "menu.h"
#include <vector>

void menu(Graph<string> &g) {

	cout << "\n\nWELCOME TO TRIP PLANNER! \n\n";
	cout << "Press enter to continue...\n";
	getchar();



	int toExit = 0;

	while(!toExit){

		cout << "\n\n\nHere is a list with all the stops available\n\n";

		menuListStation(g);		// display the stations
		cout << endl;

		makeChoice(g);
		toExit = wantToExit();
	}

	cout << "\n\nClosing...";
}

static int wantToExit(){

	cout << "\n\n\nDo you want to: ";
	cout << "\n[0] - Continue using TripPlanner";
	cout << "\n[1] - Exit";

	int opt;
	string opt_s;

	cout << "\n>> ";
	cin >> opt_s;

	while(opt < 0 || opt > 1){

		if(!isNumber(opt_s)){
			while(!isNumber(opt_s)){
				cout << "Local de partida ? ";
				cin >> opt_s;
				cin.ignore(1000, '\n');
			}
		}

		opt = stoi(opt_s);

		if(opt > 1 || opt < 0){
			opt = -1;
			opt_s = "Invalid input";
		}
	}

	opt = stoi(opt_s);

	return opt;
}

static void menuListStation(const Graph<string> &g) {
	vector<Node<string>*> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
		cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

static void makeChoice(Graph<string> &g){

	// ask for departure station
	string origin_id_s, dest_id_s;
	int id_origin = -1, id_dest = -1;

	cout << "Local de partida ? ";
	cin >> origin_id_s;

	while(id_origin < 0 || id_origin > 36){

		if(!isNumber(origin_id_s)){
			while(!isNumber(origin_id_s)){
				cout << "Local de partida ? ";
				cin >> origin_id_s;
				cin.ignore(1000, '\n');
			}
		}

		id_origin = stoi(origin_id_s);

		if(id_origin > 36 || id_origin < 0){
			id_origin = -1;
			origin_id_s = "Invalid input";
		}
	}


	cout << "Local de destino ? ";
	cin >> dest_id_s;

	while(id_dest < 0 || id_dest > 36){

		if(!isNumber(dest_id_s)){
			while(!isNumber(dest_id_s)){
				cout << "Local de destino ? ";
				cin >> dest_id_s;
				cin.ignore(1000, '\n');
			}
		}

		id_dest = stoi(dest_id_s);

		if(id_dest > 36 || id_dest < 0){
			id_dest = -1;
			dest_id_s = "Invalid input";
		}
	}


	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), *endNode =
			g.getNodeByID(id_dest);

	// ask for criterion
	cout << endl;
	pathCriterion criterion = getPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);

	cout << g.getDetailedPath(lastNode) << endl;

	vector<string> t = g.getPath(lastNode);

	presentPath(t);
}

static void presentPath(vector<string> t){
	for (size_t i = 0; i < t.size(); i++) {
		if (i < (t.size() - 1))
			cout << t.at(i) << "->";
		else
			cout << t.at(i);
	}
}

static pathCriterion getPathCriterion() {
	cout << "Escolha um criterio\n";
	cout << "[0] - Numero de transbordos\n";
	cout << "[1] - Rotas sem caminhos a pe\n";
	cout << "[2] - Menor preco\n";
	cout << "[3] - Menor tempo de viagem\n\n";


	string option_s;
	int option = -1;

	cout << "Criterio ? ";
	cin >> option_s;

	while(option < 0 || option > 3){

		if(!isNumber(option_s)){
			cout << "Invalid input" << endl;

			while(!isNumber(option_s)){
				option_s.clear();
				cout << "Criterio ? ";
				cin >> option_s;
				cin.ignore(1000, '\n');
			}
		}

		option = stoi(option_s);

		if(option > 3 || option < 0){
			option = -1;
			option_s = "Invalid input";
		}
	}

	cout << endl << endl;

	return (pathCriterion) option;
}

static Node<string> * run_Dijkstra(Graph<string> &g,
								   Node<string> *startNode,
								   Node<string> *endNode,
								   pathCriterion criterion) {

	switch (criterion) {
	case TRANSBORDS:{
		string num_transb_s;
		int num_transb;
		cout << "Numero maximo de transbordos ? ";
		cin >> num_transb_s;
		if(!isNumber(num_transb_s)){
			while(!isNumber(num_transb_s)){
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

	case PRICE:{
		double walk_distance;
		string walk_d_s;
		cout << "Distancia maxima que pretende andar a pe? ";
		cin >> walk_d_s;
		if(!isNumber(walk_d_s)){
			while(!isNumber(walk_d_s)){
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

/**
 * @param input - any string
 *
 * @brief Checks if the string is a number, with no alphabetic characters
 *
 * @return bool - whether is true or false that the string is a number (true if it is, false otherwise)
 */
bool isNumber(string input){

	for (unsigned int i = 0; i < input.size(); i++){
		if(input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}
