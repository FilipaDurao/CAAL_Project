/**
 * @brief This file contains the functions, representing menus, to interact with the user
 * 
 * @file menu.cpp
 */
#include "menu.h"
#include <vector>
#include "stringSearch.h"

/**
 * @brief Generic function to get input (integers) from the user to navigate through menus
 *
 * @param lower_bound The lower option number
 * @param upper_bound The upper option number
 * @param out_question The question to display to the user
 *
 * @return The value typed by the user
 */
static int getMenuOptionInput(int lower_bound, int upper_bound, string out_question)
{
	int opt;
	bool success = false;

	do
	{
		cout << out_question;
		cin >> opt;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			success = false;
		}
		else
		{
			success = true;
			cin.ignore(1000, '\n');
		}

	} while (!success || opt < lower_bound || opt > upper_bound);

	return opt;
}

void menu(Graph<string> &g)
{

	cout << "\n\nWELCOME TO TRIP PLANNER! \n\n";
	cout << "Press enter to continue...\n";
	getchar();
	bool exit = false;

	while (!exit)
	{
		menuStart(g);
		exit = wantToExit();
	}

	cout << "\n\nClosing...\n";
}

void fillStationsName(Graph<string> &g, vector<Guess *> &names)
{

	vector<Node<string> *> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
	{

		Guess *newGuess = new Guess();

		newGuess->stationName = nodes.at(i)->getInfo();
		newGuess->index = i;
		newGuess->editDistance = -1;

		names.push_back(newGuess);
	}
}

void menuStart(Graph<string> &g)
{
	int option;
	cout << "\n\n";
	cout << "Do you want to: \n";
	cout << "[0] - View the full map\n";
	cout << "[1] - Plan the trip\n";
	cout << "[2] - View information of a stop\n\n";

	option = getMenuOptionInput(0, 2, "Option ? ");

	if (option == 0){
		showGraphViewer(g);
	}
	else if(option == 1){
		menuChooseStations(g);
	}
	else{
		menuFindLineInStation(g);
	}
}

int kmpExactSearch(string stop, vector<Guess *> &names)
{

	vector<Guess *> partialGuesses;

	//Trying to find it exactly, or at least partially in a stop
	for (Guess *g : names)
	{

		int result = kmpMatcher(g->stationName, stop);

		if (result != 0)
		{
			partialGuesses.push_back(g);
		}
	}

	int partialSize = partialGuesses.size();

	if (partialSize != 0)
	{

		//if we only found one, display it
		if (partialSize == 1)
		{

			cout << "Departure Station acknowledge: " << partialGuesses.at(0)->stationName << "\n";
			return partialGuesses.at(0)->index;
		}
		else
		{
			cout << "We found that name in several stops. Which one of these do you mean: \n";

			for (int i = 0; i < partialSize; i++)
			{

				cout << "[" << i << "]"
					 << " - " << partialGuesses.at(i)->stationName << endl;
			}

			int option = getMenuOptionInput(0, partialSize - 1, " -->Select your choice:");

			return partialGuesses.at(option)->index;
		}
	}

	return -1;
}

int getStringOption(vector<Guess *> &names, string initialMessage)
{

	set<Guess *, cmpGuess> guessAttempts;

	string stop;

	cout << initialMessage << ": ";

	getline(cin, stop);

	//Exact Search
	int index = kmpExactSearch(stop, names);

	if (index != -1)
		return index;

	//Approximante Search
	for (Guess *g : names)
	{
		g->editDistance = editDistance(stop, g->stationName);
		guessAttempts.insert(g);
	}

	auto it = guessAttempts.begin();

	int maxDiff = stop.length() * 0.70;

	if ((*it)->editDistance > maxDiff)
	{
		cout << "We couldn't find any stop with a similar name. Try Again!\n";
		return -1;
	}

	int i = 0;

	cout << "We could't find your station. Did you mean:\n";

	for (; i < 3 && it != guessAttempts.end(); i++, it++)
	{
		if ((*it)->editDistance > maxDiff)
			break;
		cout << "[" << i << "]"
			 << " - " << (*it)->stationName << endl;
	}

	int option = getMenuOptionInput(0, i, " -->Select your choice:");

	auto result = next(guessAttempts.begin(), option);

	return (*result)->index;
}

void menuFindLineInStation(Graph<string> &g){

	vector<Guess *> stationsName;

	fillStationsName(g, stationsName);

	// ask for departure station
	int id_origin;
	string id_line;

	do{
		id_origin = getStringOption(stationsName, "\nDeparture Station");
	} while (id_origin == -1);

	cout << "\nLine? ";
	getline(cin, id_line);

	Node<string> *node = g.getNodeByID(id_origin);
	vector<Edge<string>> edgesOfNode = node->getEdges();
	bool passes = false;

	for(unsigned int i = 0; i < edgesOfNode.size(); i++){
		if(edgesOfNode.at(i).getLineID() == id_line){
			passes = true;
			break;
		}
	}

	if(passes){
		cout << "The line " << id_line << " passes in this station";
	}
	else{
		cout << "The line " << id_line << " doesn't pass in this station";
	}

}

void menuChooseStations(Graph<string> &g)
{

	vector<Guess *> stationsName;

	fillStationsName(g, stationsName);

	// ask for departure station
	int id_origin, id_dest;

	do
	{
		id_origin = getStringOption(stationsName, "Departure Station");
	} while (id_origin == -1);

	do
	{
		id_dest = getStringOption(stationsName, "Arrival station");
	} while (id_dest == -1);

	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), *endNode = g.getNodeByID(id_dest);

	// ask for criterion
	pathCriterion criterion = menuPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);

	vector<Node<string> *> invertedPath = g.getDetailedPath(lastNode);

	g.presentPath(invertedPath);

	vector<string> t = g.getPath(lastNode);

	presentPath(t);

	// Show map
	if (invertedPath.at(0)->getLastNode() != NULL)
	{
		invertedPath.push_back(startNode);
		GraphViewer *gv = buildGraphViewerDeatiledPath(g, invertedPath);

		cout << "\nPress any key to close window ...\n";
		cin.ignore(1000, '\n');
		getchar();

		gv->closeWindow();
	}

	for (Guess *g : stationsName)
		free(g);

	stationsName.clear();
}

pathCriterion menuPathCriterion()
{
	cout << "\n\nChoose a criterion\n";
	cout << "[0] - Number of transfers\n";
	cout << "[1] - Routes without walking\n";
	cout << "[2] - Lowest price\n";
	cout << "[3] - Travelling time\n\n";

	string option_s;
	int option = getMenuOptionInput(0, 3, "Option ? ");

	cout << endl
		 << endl;

	return (pathCriterion)option;
}

Node<string> *run_Dijkstra(Graph<string> &g, Node<string> *startNode,
						   Node<string> *endNode, pathCriterion criterion)
{

	switch (criterion)
	{
	case TRANSBORDS:
	{
		string num_transb_s;
		int num_transb;
		cout << "Maximum number of transfers ? ";
		cin >> num_transb_s;
		if (!isNumber(num_transb_s))
		{
			while (!isNumber(num_transb_s))
			{
				cout << "Maximum number of transfers ? ";
				cin >> num_transb_s;
				cin.ignore(1000, '\n');
			}
		}
		num_transb = stoi(num_transb_s);
		return g.dijkstra_queue_TRANSBORDS(startNode, endNode, num_transb);
	}

	case NO_WALK:
		return g.dijkstra_queue_NO_WALK(startNode, endNode);

	case PRICE:
	{
		double walk_distance;
		string walk_d_s;
		cout << "Maximum distance you pretend to walk ? ";
		cin >> walk_d_s;
		if (!isNumber(walk_d_s))
		{
			while (!isNumber(walk_d_s))
			{
				cout << "Maximum distance you pretend to walk ? ";
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
bool wantToExit()
{

	cout << "\n\n\nDo you want to: \n";
	cout << "[0] - Continue using TripPlanner\n";
	cout << "[1] - Exit\n";

	int opt = getMenuOptionInput(0, 1, "Option ? ");

	return (opt == 0 ? false : true);
}

void showListStation(const Graph<string> &g)
{
	vector<Node<string> *> nodes = g.getNodes();

	for (size_t i = 0; i < nodes.size(); i++)
		cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

void presentPath(vector<string> t)
{
	for (size_t i = 0; i < t.size(); i++)
	{
		if (i < (t.size() - 1))
			cout << t.at(i) << "->";
		else
			cout << t.at(i);
	}
}

// Graph viewer
void showGraphViewer(Graph<string> &g)
{
	GraphViewer *gv = buildGraphViewer(g);

	cout << "Press any key to close window ...\n";
	getchar();
	gv->closeWindow();
}

GraphViewer *buildGraphViewer(Graph<string> &g)
{
	GraphViewer *gv = new GraphViewer(2000, 2000, false);
	gv->createWindow(1000, 1000);

	// edge id's
	int edge_id = 0;
	// Get the nodes
	vector<Node<string> *> nodes = g.getNodes();
	for (size_t i = 0; i < nodes.size(); i++)
	{
		// add the node to graphViewer
		Node<string> *n = nodes.at(i);
		gv->addNode(n->getId(), n->getX() / 2, n->getY() / 2);
		gv->setVertexSize(n->getId(), 60);
		gv->setVertexLabel(n->getId(), n->getInfo());

		// add  the edges (this might not work because not all nodes are defined yet)
		vector<Edge<string>> edges = nodes.at(i)->getEdges();
		for (size_t j = 0; j < edges.size(); j++)
		{
			if (edges.at(j).getType() != "walk")
			{
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

GraphViewer *buildGraphViewerDeatiledPath(Graph<string> &g, vector<Node<string> *> nodes)
{
	// build the whole map
	GraphViewer *gv = buildGraphViewer(g);

	// Change path nodes color
	for (size_t i = 0; i < nodes.size(); i++)
	{
		gv->setVertexColor(nodes.at(i)->getId(), RED);
	}

	return gv;
}

void setGraphViewerEdgeColor(GraphViewer *gv, int edge_id, string lineID)
{
	if (lineID == "B")
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
bool isNumber(string input)
{

	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}
