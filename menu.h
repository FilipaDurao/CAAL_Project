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

#endif
