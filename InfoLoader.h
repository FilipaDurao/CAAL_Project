#include "Graph.h"
#include "GraphViewer/graphviewer.h"
#include <string>

using namespace std;

/**
 * @brief Loads all the Node information from the file into the graph
 *
 * @param grafo - the Graph into which the information will be loaded to
 */
void loadNodes(Graph<string> & grafo);

/**
 * @brief Loads all the Edge information from the file into the graph Nodes
 *
 * @param grafo - the Graph into which the information will be loaded to
 */
void loadEdges(Graph<string> & grafo);
