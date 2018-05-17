/**
 * @brief This file contains the functions, representing menus, to interact with the user
 * 
 * @file menu.h
 */
#ifndef MENU_H_
#define MENU_H_

#include "Graph.h"
#include "GraphViewer/graphviewer.h"
#include <string>

enum pathCriterion
{
	TRANSBORDS = 0,
	NO_WALK = 1,
	PRICE = 2,
	DISTANCE = 3
};

/**
* Struct containing the essential info for the string searching algorithmns
*/
typedef struct{
	string stationName; ///< the stop name
	int index;         ///< the stop index in the Graph's vector
	int editDistance;  ///< it's current editDistance
} Guess;

struct cmpGuess{
	 bool operator()(Guess * a,  Guess * b) const {
        return a->editDistance < b->editDistance;
    }
};

/**
 * @brief The main menu
 *
 * @param g The graph where this menu operates on
 */
void menu(Graph<string>& g);

/**
 * @brief Menu that allows to view the map, or plan a trip
 *
 * @param g The graph where this menu operates on
 */
void menuStart(Graph<string>& g);

/**
 * @brief Menu where the user is asked to choose the departure/arrival stations
 *
 * @param g The graph where this menu operates on
 */
void menuChooseStations(Graph<string> &g);

/**
 * TODO
 */
void menuFindLineInStation(Graph<string> &g);

/**
 * @brief Menu where the user is asked for a criterion for trip planning
 */
pathCriterion menuPathCriterion();

/**
 * @brief Asks the user if he wants to continue using Trip Planner or exit the program
 *
 * @retval True The user wants to close the program
 * @terval False Continue using the application
 */
bool wantToExit();

/**
 * @brief For a map, lists all stations
 *
 * @param g The map (graph)
 */
void showListStation(const Graph<string> &g);


void presentPath(vector<string> t);

/**
 * @brief Runs the algorithm to find the best trip considering the criterion
 */
Node<string>* run_Dijkstra(Graph<string>& g, Node<string>* startNode, Node<string>* endNode, pathCriterion criterion);

/**
 * @brief Shows a graphViewer map showing all stations and connections in between
 */
void showGraphViewer(Graph<string>& g);

/**
 * @brief Builds and returns a GraphViewer with all stations and connections
 */
GraphViewer* buildGraphViewer(Graph<string>& g);

/**
 * @brief Builds and returns a GraphViewer with all stations and connections, but highlighting some path
 */
GraphViewer* buildGraphViewerDeatiledPath(Graph<string>& g, vector<Node<string>*> nodes);

/**
 * @brief Determines GraphViewer edge's colors based on it's lineID
 */
void setGraphViewerEdgeColor(GraphViewer *gv, int edge_id, string lineID);

bool isNumber(string input);


/**
* @brief Perfoms kmpMatcher on a vector containing all the names of the stops with a pattern given by the user.
*		If it only finds one occurrence of the pattern in a single element in the vector, it returns the stop's index in the Graph's stop vector. 
*		If it finds variable occurences (e.g. "Faculdade" in "Faculdade de Engenharia" and "Faculdade de Economia") it asks the user to pick one.
*		Otherwise it returns -1;
* @param stop - the pattern to search
* @param names - the vector containing all the strings to look for the pattern
* @return Positive integer in success, -1 otherwise
*/
int kmpExactSearch(string stop, vector< Guess * > &names);

/**
* @brief Utilitary funcion that fill the vector names with all the Graph's stop name and index (by creating a special structure to hold that information)
* @param g - the graph
* @param names - the vector to be filled
*/
void fillStationsName(Graph<string> &g, vector<Guess *> &names);

/**
 * @brief Asks the user for a Departure/Arrival Station and tries to find it in the existing ones.
 * Used kmpMatcher and editDistance to try to find them.
 * @param names - the vector containing all the stops available
 * @param initialMessage - the message to be presented -> Departure/Arrival
 * @return On success, the index of the stop on the Graph's stops vector, -1 otherwise
 */
int getStringOption(vector<Guess *> &names, string initialMessage);

#endif
