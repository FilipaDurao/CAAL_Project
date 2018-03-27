/*
 * Graph.h
 *
 *  Created on: 12/03/2018
 *      Author: filipa
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <cfloat>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <queue>
#include "MutablePriorityQueue.h"

constexpr const double BUS_MULTIPLIER = 1.8;
constexpr const double METRO_MULTIPLIER = 0.7;
constexpr const double WALK_MULTIPLIER = 2.7;

using namespace std;

template<typename T>
class Edge;

//////////////////////////////////////////////////////////////////////////////////
/////								NODE									 /////
//////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Node {
private:
	unsigned int ID;
	T info;
	vector<Edge<T>> edges;
	bool visited;
	double distance;
	Node<T> * lastNode;

public:
	Node(const T &value, unsigned int ID);

	virtual ~Node();

	void addEdge(Edge<T> edge);
	unsigned int getId() const;
	T getValue() const;
	unsigned int getNumberOfEdges() const;
	vector<Edge<T>> getEdges() const;

	void setInfo(T info);
	T getInfo() const;

	// ---- DIJKSTRA INFO ----
	double getDistance() const;
	void setDistance(double distance);
	Node* getLastNode();
	void setLastNode(Node* lastNode);
	void clearLastNode();
	void setVisited(bool vis);
	bool getVisited() const;

	// ---- Mutable Priority Queue Info ----
	bool operator<(Node<T> & node) const;
	int queueIndex = 0;
};

template<typename T>
void Node<T>::setInfo(T info) {
	this->info = info;
}

/**
 * @brief  Returns the node's information
 *
 * @return info
 */
template<typename T>
T Node<T>::getInfo() const {
	return this->info;
}

template<typename T>
void Node<T>::setVisited(bool vis) {
	this->visited = vis;
}

template<typename T>
bool Node<T>::getVisited() const {
	return this->visited;
}

template<typename T>
bool Node<T>::operator<(Node<T> & node) const {
	return this->distance < node.distance;
}

/**
 * @brief Creates a node
 * The node's ID will be its place in the node's vector in graph, for easier access
 *
 * @param value - the node's value
 * @param ID - the node's ID
 *
 */
template<typename T>
Node<T>::Node(const T &info, unsigned int ID) {
	this->info = info;
	this->ID = ID;
	this->distance = DBL_MAX;
	this->lastNode = NULL;
	this->visited = false;
}

/**
 * @brief Destroys a node
 */
template<typename T>
Node<T>::~Node() {
	edges.clear();
}

/**
 * @brief Adds an edge to a node
 *
 * @param edge - a generic edge to add to the node
 */
template<typename T>
void Node<T>::addEdge(Edge<T> edge) {
	edges.push_back(edge);
}

/**
 * @brief Returns the node's ID
 *
 * @return ID
 */
template<typename T>
unsigned int Node<T>::getId() const {
	return ID;
}

/**
 * @brief Returns the number of edges the node has
 *
 * @return Number of edges
 */
template<typename T>
unsigned int Node<T>::getNumberOfEdges() const {
	return this->edges.size();
}

/**
 * @brief Returns a vector with all the edges of the node
 *
 * @return Vector with the node's edges
 */
template<typename T>
vector<Edge<T>> Node<T>::getEdges() const {
	return this->edges;
}

/**
 * @brief Clears the lastNode (for Dijkstra running)
 */
template<typename T>
void Node<T>::clearLastNode() {
	this->lastNode = NULL;
}

/**
 * @brief Returns the LastNode info for Dijkstra
 *
 * @return Last Node
 */
template<typename T>
Node<T>* Node<T>::getLastNode() {
	return this->lastNode;
}

/**
 * @brief Sets the lastNode atributte with lastNode passed by parameter
 *
 * @param lastNode - a Node
 */
template<typename T>
void Node<T>::setLastNode(Node* lastNode) {
	this->lastNode = lastNode;
}

/**
 * @brief Returns the current path distance to get to this Node
 *
 * @return distance
 */
template<typename T>
double Node<T>::getDistance() const {
	return this->distance;
}

/**
 * @brief Sets the distance traveled to get to this Node
 *
 * @param distance
 */
template<typename T>
void Node<T>::setDistance(double distance) {
	this->distance = distance;
}

//////////////////////////////////////////////////////////////////////////////////
/////								EDGE									 /////
//////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Edge {
protected:
	Node<T>* destiny;
	double weight;
	string type;

public:

	Edge(Node<T> * destiny, double weight, string type);

	virtual ~Edge();

	Node<T>* getDestiny() const;

	double getWeight() const;

	string getType() const;
};

//// ---- BUS EDGE ----
//
//template<typename T>
//class BusEdge: public Edge<T> {
//
//public:
//	double getWeight();
//
//	BusEdge(Node<T> * destiny, double weight, string type);
//
//	string getType() const;
//
//};
//template<typename T>
//BusEdge<T>::BusEdge(Node<T> * destiny, double weight, string type) {
//	this->destiny = destiny;
//	this->weight = weight;
//	this->type = type;
//}
//template<typename T>
//double BusEdge<T>::getWeight() {
//	return this->weight * BUS_MULTIPLIER;
//}
//
//template<typename T>
//string BusEdge<T>::getType() const {
//	return this->type;
//}
//
//// ---- Metro EDGE ----
//
//template<typename T>
//class MetroEdge: public virtual Edge<T> {
//
//public:
//	double getWeight();
//
//	MetroEdge(Node<T> * destiny, double weight, string type);
//
//	string getType() const;
//
//};
//
//template<typename T>
//MetroEdge<T>::MetroEdge(Node<T> * destiny, double weight, string type) {
//	this->destiny = destiny;
//	this->weight = weight;
//	this->type = type;
//}
//
//template<typename T>
//double MetroEdge<T>::getWeight() {
//	return this->weight * METRO_MULTIPLIER;
//}
//
//template<typename T>
//string MetroEdge<T>::getType() const {
//	return this->type;
//}
//
//// ---- Walk EDGE ----
//
//template<typename T>
//class WalkEdge: public Edge<T> {
//
//public:
//	double getWeight();
//
//	WalkEdge(Node<T> * destiny, double weight, string type);
//
//	string getType() const;
//
//};
//template<typename T>
//WalkEdge<T>::WalkEdge(Node<T> * destiny, double weight, string type) {
//	this->destiny = destiny;
//	this->weight = weight;
//	this->type = type;
//}
//
//template<typename T>
//double WalkEdge<T>::getWeight() {
//	return this->weight * WALK_MULTIPLIER;
//}
//
//template<typename T>
//string WalkEdge<T>::getType() const {
//	return this->type;
//}

template<typename T>
Edge<T>::Edge(Node<T> * destiny, double weight, string type) {
	this->destiny = destiny;
	this->weight = weight;
	this->type = type;
}

/**
 * @brief Destroys an Edge
 */
template<typename T>
Edge<T>::~Edge() {
}

/**
 * @brief Returns the destiny of an Edge
 *
 * @return the Node that is in the end of the Edge
 */
template<typename T>
Node<T>* Edge<T>::getDestiny() const {
	return destiny;
}

/**
 * @brief Returns the weight of an Edge
 *
 * @return the weigth of the Edge
 */
template<typename T>
string Edge<T>::getType() const {
	return this->type;
}

template<typename T>
double Edge<T>::getWeight() const {

	if (this->type == "metro")
		return this->weight * METRO_MULTIPLIER;
	else if (this->type == "bus")
		return this->weight * BUS_MULTIPLIER;
	else
		return this->weight * WALK_MULTIPLIER;
}

//////////////////////////////////////////////////////////////////////////////////
/////								GRAPH									 /////
//////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Graph {
private:
	vector<Node<T> *> nodes;

public:
	Graph();

	virtual ~Graph();

	void addNode(T nodeData);
	unsigned int getNumNodes() const;	//Get the number of nodes in the graph
	// TODO Node<T> getNodeByID(unsigned int ID) const;		//Get one node of the graph by its ID
	unsigned int getNumEdges() const; 	// Get the number of edges in the graph
	vector<Node<T> *> getNodes() const;

	// ---- Edges Types ----
	void addBusEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
			double weight);
	void addMetroEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
			double weight);
	void addWalkEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
			double weight);

	vector<T> getPath(Node<T> * dest) const;

// TODO Dijkstra algorithm in the graph
	Node<T> * dijkstra_heap(Node<T> * startNode, Node<T> * endNode);
	Node<T> * dijkstra_queue(Node<T> * startNode, Node<T> * endNode);
};

/**
 * @brief Creates a Graph
 */
template<typename T>
Graph<T>::Graph() {
}

/**
 * @brief Destroys a Graph
 */
template<typename T>
Graph<T>::~Graph() {
	nodes.clear();
}

/**
 * @brief Creates a Node and adds it to the Graph
 *
 * @param nodeData - the data with which we create a Node
 */
template<typename T>
void Graph<T>::addNode(T nodeData) {
	this->nodes.push_back(new Node<T>(nodeData, nodes.size()));
}

/**
 * @brief Gets the number of Nodes in the Graph
 *
 * @return The size of the Nodes vector in the Graph
 */
template<typename T>
unsigned int Graph<T>::getNumNodes() const {
	return nodes.size();
}

/**
 * @brief Gets the number of Edges in the Graph
 *
 * @return The sum of all the Edges in all the Nodes in the Graph
 */
template<typename T>
unsigned int Graph<T>::getNumEdges() const {
	unsigned int size = 0;

	for (unsigned int i = 0; i < nodes.size(); i++) {
		size += nodes.at(i).getNumberOfEdges();
	}
	return size;
}

/**
 * @brief Returns all the Nodes in the Graph
 *
 * @return a vector equal to the Nodes vector in Graph
 */
template<typename T>
vector<Node<T> *> Graph<T>::getNodes() const {
	return this->nodes;
}

/**
 * @brief Creates an BusEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template<typename T>
void Graph<T>::addBusEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
		double weight) {
	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, "bus");
	this->nodes.at(sourceNodeID)->addEdge(edge);

}

/**
 * @brief Creates an MetroEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template<typename T>
void Graph<T>::addMetroEdge(unsigned int sourceNodeID,
		unsigned int destinyNodeID, double weight) {
	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, "metro");
	this->nodes.at(sourceNodeID)->addEdge(edge);

}

/**
 * @brief Creates an WalkEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template<typename T>
void Graph<T>::addWalkEdge(unsigned int sourceNodeID,
		unsigned int destinyNodeID, double weight) {

	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, "walk");
	this->nodes.at(sourceNodeID)->addEdge(edge);
}

/*
 * Max heap by default has the highest value on the top of the heap
 * Since we want the minimum, in terms of distance, we must define the operator in the reverse orded
 *
 */
template<typename T>
struct compareDistance {
	bool operator()(Node<T> * rhs, Node<T> * lhs) const {
		return rhs->getDistance() > lhs->getDistance();
	}
};

/**
 * @brief Returns a vector with the path with the "smallest" distance from the startNode to the endNode
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 *
 * @return
 */
template<typename T>
Node<T> * Graph<T>::dijkstra_heap(Node<T> * startNode, Node<T> * endNode) {

	vector<Node<T> *> path = {};

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
	}

	startNode->setDistance(0);
	path.push_back(startNode);

	//making the heap, since it only has one element does not need the function
	make_heap(path.begin(), path.end());

	Node<T> * v;
	Node<T> * w;
	double new_distance;
	double old_distance;

	while (!path.empty()) {

		//the miminum value is always in the top
		v = path.front();

		//putting the min value (considered the max since we swap the operator) in the back
		pop_heap(path.begin(), path.end());

		//removing it
		path.pop_back();

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++) {

			w = it->getDestiny();
			new_distance = v->getDistance() + it->getWeight();
			old_distance = w->getDistance();

			if (old_distance > new_distance) {

				w->setDistance(new_distance);
				w->setLastNode(v);

				if (old_distance == DBL_MAX) {  //aka is not in the path
					path.push_back(w);
				}

				make_heap(path.begin(), path.end(), compareDistance<T>());

			}
		}
	}

	return endNode;
}

template<class T>
Node<T> * Graph<T>::dijkstra_queue(Node<T> * startNode, Node<T> * endNode) {

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
		(*it)->setVisited(false);
	}

	startNode->setDistance(0);

	MutablePriorityQueue<Node<T> > q;

	q.insert(startNode);

	while (!q.empty()) {

		Node<T> * v = q.extractMin();

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++) {

			Node<T> * w = it->getDestiny();

			double old_distance = w->getDistance();

			double new_distance = v->getDistance() + it->getWeight();

			if (old_distance > new_distance) {

				w->setDistance(new_distance);

				w->setLastNode(v);

				if (!w->getVisited())
					q.insert(w);
				else
					q.decreaseKey(w);

				w->setVisited(true);
			}

		}

	}

	return endNode;

}

template<class T>
vector<T> Graph<T>::getPath(Node<T> * dest) const {

	vector<T> res;

	while (dest->getLastNode() != NULL) {

		res.push_back(dest->getInfo());

		dest = dest->getLastNode();

	}

	res.push_back(dest->getInfo());

	reverse(res.begin(), res.end());

	return res;
}

#endif /* GRAPH_H_ */
