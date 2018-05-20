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
#include "stringSearch.h"

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
void menuTripPlanning(Graph<string> &g);

/**
 * @brief Menu where the user is asked to choose a station and a Line and receives information whether the line passes or not in the station
 *
 * @param g The graph where this menu operates on
 */
void menuFindLineInStation(Graph<string> &g);

/**
 * @brief Asks the user if he wants to continue using Trip Planner or exit the program
 *
 * @retval True The user wants to close the program
 * @terval False Continue using the application
 */
bool menuWantToExit();

/**
 * @brief Get the Station ID from user input
 * To correctly pick a station, the function uses different string matching algorithms
 * @param g The graph
 * @param initialMessage A message to describe the type of input (e.g. "Enter departure station")
 * @return unsigned int The graph's node id that matches the station user input. If no match is found, returns -1
 */
int getStationInput(Graph<string> &g, string initialMessage);

/**
 * @brief This function lists stations and asks the user to pick one
 * 
 * @param matchedStations A vector of pointers to Nodes (stations)
 * @return int The node ID of the picked station. If the vector is empty, returns -1
 */
int getStationUserChoice(const vector<Node<string> *> &matchedStations);

/**
 * @brief This function lists stations and asks the user to pick one, after an approximate search was done
 * 
 * @param matchedStations A set of Guess pointers 
 * @return int The node ID of the picked station. If the vector is empty, returns -1
 */
int getStationUserApproximateChoice(const set<Guess *, cmpGuess> & approximateGuesses);

/**
 * @brief Valides the user input by tokenizing it and removing all the words from our common dictionary
 * If the resulting vector of tokens if empty, the string is not valid
 * 
 * @param userInput - the string to be validated
 * @return true if valid, false otherwise
 */
bool valideUserInput(string userInput);

/**
 * @brief Menu where the user is asked for a criterion for trip planning
 */
pathCriterion getPathCriterion();

/**
 * @brief 
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool isNumber(string input);

/**
 * @brief Displays the trip path in a short way
 * 
 * @param t 
 */
void showShortTripPath(vector<string> t);

/*
	+-----------------------+
	|                       |
	|        Dijkstra       |
	|                       |
	+-----------------------+
*/

/**
 * @brief Runs the algorithm to find the best trip considering the criterion
 */
Node<string>* run_Dijkstra(Graph<string>& g, Node<string>* startNode, Node<string>* endNode, pathCriterion criterion);


/*
	+-----------------------+
	|                       |
	|      Graph Viewer     |
	|                       |
	+-----------------------+
*/

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

#endif
