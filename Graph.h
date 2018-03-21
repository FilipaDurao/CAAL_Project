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

using namespace std;

template <typename T>
class Edge;


//////////////////////////////////////////////////////////////////////////////////
/////								NODE									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Node {
private:
	unsigned int ID;
	T value;
	vector<Edge<T>> edges;

	// Dijkstra values
	unsigned int pathSize = DBL_MAX;
	vector<Node<T>> path;

public:
	Node(const T &value, unsigned int ID);

	virtual ~Node();

	void addEdge(Edge<T> edge);
	unsigned int getId() const;
	T getValue() const;
	unsigned int getNumberOfEdges() const;
	vector<Edge<T>> getEdges() const;

	void setPathSize(double value);
	void addToPath(Node<T> node);

	bool operator < (Node<T> n1);

};

/**
 * @brief Creates a node
 * The node's ID will be its place in the node's vector in graph, for easier access
 *
 * @param value - the node's value
 * @param ID - the node's ID
 *
 */
template <typename T>
Node<T>::Node(const T &value, unsigned int ID){
		this->value = value;
		this->ID = ID;
}

/**
 * @brief Destroys a node
 */
template <typename T>
Node<T>::~Node(){
	edges.clear();
}

/**
 * @brief Adds an edge to a node
 *
 * @param edge - a generic edge to add to the node
 */
template <typename T>
void Node<T>::addEdge(Edge<T> edge){
	edges.push_back(edge);
}

/**
 * @brief Returns the node's ID
 *
 * @return ID
 */
template <typename T>
unsigned int Node<T>::getId() const {
	return ID;
}

/**
 * @brief  Returns the node's value
 *
 * @return Value
 */
template <typename T>
T Node<T>::getValue() const{
	return this->value;
}

/**
 * @brief Returns the number of edges the node has
 *
 * @return Number of edges
 */
template <typename T>
unsigned int Node<T>::getNumberOfEdges() const{
	return this->edges.size();
}

/**
 * @brief Returns a vector with all the edges of the node
 *
 * @return Vector with the node's edges
 */
template <typename T>
vector<Edge<T>> Node<T>::getEdges() const{
	return edges;
}

/**
 * @brief Overload for the operator <
 *
 * @param n1 - Node to be compared to the current node
 *
 * @return True if the current node is less than the node passed by parameter, false otherwise
 */
template <typename T>
bool Node<T>::operator < (Node<T> n1){
	return (this->pathSize < n1.pathSize);
}

/**
 * @brief Adds a certain distance to the distance of the node
 */
template <typename T>
void Node<T>::setPathSize(double value){
	this->pathSize = value;
}

/**
 * @brief Adds a Node to the path walked to get to the Node we are in
 */
template <typename T>
void Node<T>::addToPath(Node<T> node){
	this->path.push_back(node);
}




//////////////////////////////////////////////////////////////////////////////////
/////								EDGE									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
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
template <typename T>
Edge<T>::Edge(Node<T>* destiny, double weight){
	this->destiny = destiny;
	this->weight = weight;
}

/**
 * @brief Destroys an Edge
 */
template <typename T>
Edge<T>::~Edge(){}

/**
 * @brief Returns the Node to which the Edge points to
 *
 * @return Node at the end of the Edge
 */
template <typename T>
Node<T>* Edge<T>::getDestiny() const{
	return destiny;
}

/**
 * @brief Returns the weight of the Edge
 *
 * @return The weight of the Edge
 */
template <typename T>
double Edge<T>::getWeight() const{
	return weight;
}




//////////////////////////////////////////////////////////////////////////////////
/////								GRAPH									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Graph {
private:
	vector<Node<T>> nodes;

public:
	Graph();

	virtual ~Graph();

	void addNode(T nodeData);
	unsigned int getNumNodes() const;				//Get the number of nodes in the graph
	// TODO Node<T> getNodeByID(unsigned int ID) const;		//Get one node of the graph by its ID
	unsigned int getNumEdges() const; 				// Get the number of edges in the graph
	vector<Node<T>> getNodes() const;
	void addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID, double weight);

	vector<Node<T>> dijkstra(Node<T> startNode, Node<T> endNode);
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
	nodes.push_back(Node<T>(nodeData , nodes.size()));
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
template <typename T>
vector<Node<T>> Graph<T>::getNodes() const{
	return this->nodes;
}

/**
 * @brief Creates an Edge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template <typename T>
void Graph<T>::addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID, double weight){
	Edge<T> edge(&nodes.at(destinyNodeID), weight);		// Create the edge (the node's ids are their place in the vector)
	nodes.at(sourceNodeID).addEdge(edge);				// Add the edge to the node
}

//Get one node of the graph by its ID
//template <typename T>
// TODO Node<T> Graph<T>::getNodeByID(unsigned int ID) const{
//	// Running all nodes
//	for(unsigned int i = 0; i < this->nodes.size(); i++){
//		if(nodes.at(i).getId() == ID){
//			return nodes.at(i);
//		}
//	}

//
//	// If the node doesn't exist, return an empty node
//	return NULL;
//}

/**
 * @brief Returns a vector with the path with the "smallest" distance from the startNode to the endNode
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 *
 * @return
 */
//TODO finish dijkstra function
template <typename T>
vector<Node<T>> Graph<T>::dijkstra(Node<T> startNode, Node<T> endNode){

//	set<Node<T>> path;
//	Node<T> currentNode;
//
//	// Put the startNode in the set
//	for(unsigned int i = 0; i < nodes.size(); i++){
//		if(nodes.at(i) == startNode){			// If it is the start node
//			currentNode.node = nodes.at(i);
//			currentNode.pathSize = 0;			// The path walked until there was none
//			path.insert(currentNode);			// Save it in the set
//		}
//	}
//
//	while(!path.empty()){
//		Node<T> minNode = path.begin();
//
//		for(unsigned int i = 0; i < minNode.getNumberOfEdges(); i++){
//			// If the path that the node already has is bigger than the one we are running, update
//			int oldDist = minNode.getEdges().at(i).destiny->pathSize;
//			if(oldDist > minNode.pathSize + minNode.getEdges().at(i).getWeight()){
//				minNode.getEdges().at(i).destiny->setPathSize(minNode.pathSize + minNode.getEdges().at(i).getWeight());
//				minNode.addToPath()
//			}
//		}
//
//
//	}



}






#endif /* GRAPH_H_ */
