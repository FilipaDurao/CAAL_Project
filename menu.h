#ifndef MENU_H_
#define MENU_H_

#include "Graph.h"
#include <string>

enum pathCriterion
{
	TRANSBORDS = 0,
	NO_WALK = 1,
	PRICE = 2,
	DISTANCE = 3
};

void menu(Graph<string>& g);

static void menuListStation(const Graph<string> &g);

static pathCriterion getPathCriterion();

static Node<string>* run_Dijkstra(Graph<string>& g, Node<string>* startNode, Node<string>* endNode, pathCriterion criterion);

#endif