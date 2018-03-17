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

public:
	Node(const T &value, unsigned int ID);

	virtual ~Node();

	void addEdge(Edge<T> edge);
	unsigned int getId() const;
	T getValue() const;
	unsigned int getNumberOfEdges() const;
	vector<Edge<T>> getEdges() const;

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
 */
template <typename T>
Edge<T>::Edge(Node<T>* destiny, double weight){
	this->destiny = destiny;
	this->weight = weight;
}

template <typename T>
Edge<T>::~Edge(){}

template <typename T>
Node<T>* Edge<T>::getDestiny() const{
	return destiny;
}

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

//	TODO Information to save during dijkstra run
struct dijkstra_info {
	Node<T> node;
	unsigned int pathSize;
	Node<T> lastNode;

	bool operator < (struct dijkstra_info dNode){
		return (this->pathSize < dNode.pathSize);
	}
};

// TODO Dijkstra algorithm in the graph
vector<Node<T>> dijsktra(Node<T> startNode, Node<T> endNode);

};

template <typename T>
Graph<T>::Graph(){}

template <typename T>
Graph<T>::~Graph(){
	nodes.clear();
}

template <typename T>
void Graph<T>::addNode(T nodeData){
	nodes.push_back(Node<T>(nodeData , nodes.size()));
}

//Get the number of nodes in the graph
template <typename T>
unsigned int Graph<T>::getNumNodes() const{
	return nodes.size();
}

// Get the number of edges in the graph
template <typename T>
unsigned int Graph<T>::getNumEdges() const{
	unsigned int size = 0;

	for(unsigned int i = 0; i < nodes.size(); i++){
		size += nodes.at(i).getNumberOfEdges();
	}
	return size;
}

//Return all the nodes in the graph
template <typename T>
vector<Node<T>> Graph<T>::getNodes() const{
	return this->nodes;
}

//Add an edge
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

template <typename T>
dijkstra_info<T> operator<(){

}

template <typename T>
vector<Node<T>> Graph<T>::dijsktra(Node<T> startNode, Node<T> endNode){

	set<dijkstra_info> path;
	dijkstra_info currentNode;

	// Put the startNode in the set
	for(unsigned int i = 0; i < nodes.size(); i++){
		if(nodes.at(i) == startNode){			// If it is the start node
			currentNode.node = nodes.at(i);		// Save it in the set
			currentNode.pathSize = 0;			// The path walked until there was none
			currentNode.lastNode = -1;			// It has no previous node

			path.insert(currentNode);
		}
	}



	for(unsigned int i = 0; i < path.begin().pointer->node.getNumberOfEdges(); i++){




	}


}


#endif /* GRAPH_H_ */
