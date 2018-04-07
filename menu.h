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

void menu(Graph<string>& g);
void menuStart(Graph<string>& g);
static void menuListStation(const Graph<string> &g);
static void menuChooseStations(Graph<string> &g);
static bool wantToExit();
static void presentPath(vector<string> t);
static pathCriterion getPathCriterion();

static Node<string>* run_Dijkstra(Graph<string>& g, Node<string>* startNode, Node<string>* endNode, pathCriterion criterion);

static bool isNumber(string input);

static int getMenuOptionInput(int lower_bound, int upper_bound, string out_question);

void menuShowGraphViewer(Graph<string>& g);
GraphViewer* buildGraphViewer(Graph<string>& g);
GraphViewer* buildGraphViewerDeatiledPath(Graph<string>& g, vector<Node<string>*> nodes);

#endif
