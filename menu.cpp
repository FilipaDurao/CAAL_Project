/**
 * @brief This file contains the functions, representing menus, to interact with the user
 * 
 * @file menu.cpp
 */
#include "menu.h"
#include <vector>
#include "stringSearch.h"
#include <cmath>

/*
	+-----------------------+
	|                       |
	|         Menus         |
	|                       |
	+-----------------------+
*/

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
		exit = menuWantToExit();
	}

	cout << "\n\nClosing...\n";
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
		menuTripPlanning(g);
	}
	else{
		menuFindLineInStation(g);
	}

}

void menuTripPlanning(Graph<string> &g)
{
	// ask for departure station
	int id_origin, id_dest;

	do
	{
		id_origin = getStationInput(g, "Departure Station");
	} while (id_origin == -1);

	do
	{
		id_dest = getStationInput(g, "Arrival station");
	} while (id_dest == -1);

	// Get node pointers
	Node<string> *startNode = g.getNodeByID(id_origin), 
		*endNode = g.getNodeByID(id_dest);

	// ask for criterion
	pathCriterion criterion = getPathCriterion();

	// run Dijkstra based on criterion
	Node<string> *lastNode = run_Dijkstra(g, startNode, endNode, criterion);
	vector<Node<string> *> invertedPath = g.getDetailedPath(lastNode);

	// 
	g.presentPath(invertedPath);

	vector<string> t = g.getPath(lastNode);

	showShortTripPath(t);

	// Show map (Graph Viewer)
	if (invertedPath.at(0)->getLastNode() != NULL)
	{
		invertedPath.push_back(startNode);
		GraphViewer *gv = buildGraphViewerDeatiledPath(g, invertedPath);

		cout << "\nPress any key to close window ...\n";
		cin.ignore(1000, '\n');
		getchar();

		gv->closeWindow();
	}
}

void menuFindLineInStation(Graph<string> &g){

	int stationID;
	string lineID;

	// ask for station's name
	do{
		stationID = getStationInput(g, "Station");
	} while (stationID == -1);

	// ask for line's name
	cout << "\nLine? ";
	getline(cin, lineID);

	// find the station in specified line
	map<string, set<unsigned int>> stationsByLine = g.getStationsByLine();
	auto lineIt = stationsByLine.find(lineID);

	if(lineIt == stationsByLine.end()) {
		cout << "The line " << lineID << " does not exist!\n";
	} else {
		// found line, get the iterator for stations of that line
		bool found = false;
		for(auto stationIt = lineIt->second.begin(); stationIt != lineIt->second.end() && !found; stationIt++) {
			if(*stationIt == (unsigned int)stationID) // at this point, stationID is > 0
				found = true;
		}

		// display message
		if(found){
		cout << "The line " << lineID << " passes in this station";
		}
		else{
			cout << "The line " << lineID << " doesn't pass in this station";
		}
	}
}

bool menuWantToExit()
{

	cout << "\n\n\nDo you want to: \n";
	cout << "[0] - Continue using TripPlanner\n";
	cout << "[1] - Exit\n";

	int opt = getMenuOptionInput(0, 1, "Option ? ");

	return (opt == 0 ? false : true);
}

int getStationInput(Graph<string> &g, string initialMessage) {
	// get user station input
	string stationInput;
	cout << initialMessage << ": ";
	getline(cin, stationInput);

	// containers initialization
	vector<Node<string> *> stations = g.getNodes();
	vector<Node<string> *> matchedStations;

	/**
	 * Exact Search
	 */

	for(Node<string>* station : stations) {
		if(kmpMatcher(station->getInfo(), stationInput))
			matchedStations.push_back(station);
	}

	// call getStationUserChoice here
	int userChoice;

	if((userChoice = getStationUserChoice(matchedStations)) != -1)
		return userChoice; // user could pick a station

	// assuming match string failed, try aproximate search

	/**
	 * Approximate Search
	 */


	// set the maximum distance between map stations name and user input
	int maxDiff = stationInput.length() * 0.60;

	matchedStations.clear();
	for(Node<string>* station : stations) {
		if(editDistance(station->getInfo(), stationInput) <= maxDiff)
			matchedStations.push_back(station);
	}

	if((userChoice = getStationUserChoice(matchedStations)) != -1)
		return userChoice; // user could pick a station


	/**
	 * Token Search
	 */

	//If we couldn't find it using the normal, try to tokenize it
	matchedStations.clear();
	for(Node<string>* station : stations) {
		if(tokenizeAndSearch(station->getInfo(), stationInput) == 0)
			matchedStations.push_back(station);
	}
	return getStationUserChoice(matchedStations);
}

int getStationUserChoice(const vector<Node<string> *> &matchedStations)
{

	if(matchedStations.size() == 1) {
		cout << "Departure Station acknowledge: " << matchedStations.front()->getInfo() << "\n";
		return matchedStations.front()->getId(); 
	}
	else if(matchedStations.size() > 1) {
		cout << "We could't find your station. Did you mean:\n";
		int i = 0;
		for (auto it = matchedStations.begin(); it != matchedStations.end() && i < 4; it++, i++){
				cout << "[" << i << "]"
					 << " - " << (*it)->getInfo() << endl;
		}

		int option = getMenuOptionInput(0, i, " -->Select your choice:");

		return (*(matchedStations.begin() + option))->getId();
	}
	else 
		return -1;
}

pathCriterion getPathCriterion()
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


void showShortTripPath(vector<string> t)
{
	for (size_t i = 0; i < t.size(); i++)
	{
		if (i < (t.size() - 1))
			cout << t.at(i) << "->";
		else
			cout << t.at(i);
	}
}

bool isNumber(string input)
{

	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

/*
	+-----------------------+
	|                       |
	|        Dijkstra       |
	|                       |
	+-----------------------+
*/

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

/*
	+-----------------------+
	|                       |
	|      Graph Viewer     |
	|                       |
	+-----------------------+
*/

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