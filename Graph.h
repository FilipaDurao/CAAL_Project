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
	T value;
	vector<Edge<T>> edges;

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

	// ---- DIJKSTRA INFO ----
	double getDistance() const;
	void setDistance(double distance);
	Node* getLastNode();
	void setLastNode(Node* lastNode);
	void clearLastNode();
};

/**
 * @brief Creates a node
 * The node's ID will be its place in the node's vector in graph, for easier access
 *
 * @param value - the node's value
 * @param ID - the node's ID
 *
 */
template<typename T>
Node<T>::Node(const T &value, unsigned int ID) {
	this->value = value;
	this->ID = ID;
	this->distance = DBL_MAX;
	this->lastNode = NULL;
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
 * @brief  Returns the node's value
 *
 * @return Value
 */
template<typename T>
T Node<T>::getValue() const {
	return this->value;
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
	return edges;
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
 * @brief Sets the distance travelled to get to this Node
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
private:
	Node<T>* destiny;
	double weight;

public:
	Edge(Node<T>* destiny, double weight);
	virtual ~Edge();

	Node<T>* getDestiny() const;
	double getWeight() const;
};

/**
 * @brief  Creates an Edge
 *
 * @param destiny - the node of destiny of the edge
 * @param weight - the weight of the edge
 *
 */
template<typename T>
Edge<T>::Edge(Node<T>* destiny, double weight) {
	this->destiny = destiny;
	this->weight = weight;
}

template<typename T>
Edge<T>::~Edge() {
}

template<typename T>
Node<T>* Edge<T>::getDestiny() const {
	return destiny;
}

template<typename T>
double Edge<T>::getWeight() const {
	return weight;
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
	void addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
			double weight);

// TODO Dijkstra algorithm in the graph
	Node<T> * dijsktra(Node<T> * startNode, Node<T> * endNode);

};

/**
 * @brief Creates a Graph
 */
template <typename T>
Graph<T>::Graph(){}

/**
 * @brief Destroys a Graph
 */
template <typename T>
Graph<T>::~Graph(){
	nodes.clear();
}

/**
 * @brief Creates a Node and adds it to the Graph
 *
 * @param nodeData - the data with which we create a Node
 */
template <typename T>
void Graph<T>::addNode(T nodeData){
	this->nodes.push_back(new Node<T> (nodeData, nodes.size()));
}

/**
 * @brief Gets the number of Nodes in the Graph
 *
 * @return The size of the Nodes vector in the Graph
 */
template <typename T>
unsigned int Graph<T>::getNumNodes() const{
	return nodes.size();
}

/**
 * @brief Gets the number of Edges in the Graph
 *
 * @return The sum of all the Edges in all the Nodes in the Graph
 */
template <typename T>
unsigned int Graph<T>::getNumEdges() const{
	unsigned int size = 0;

	for(unsigned int i = 0; i < nodes.size(); i++){
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
 * @brief Creates an Edge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template<typename T>
void Graph<T>::addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
		double weight) {
	Edge<T> edge(nodes.at(destinyNodeID), weight);// Create the edge (the node's ids are their place in the vector)
	nodes.at(sourceNodeID)->addEdge(edge);			// Add the edge to the node
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
Node<T> * Graph<T>::dijsktra(Node<T> * startNode, Node<T> * endNode) {

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

#endif /* GRAPH_H_ */
