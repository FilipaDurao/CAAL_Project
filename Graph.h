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
	unsigned int getNumberOfEdges();
	vector<Edge<T>> getEdges();

};

template <typename T>
Node<T>::Node(const T &value, unsigned int ID){
		this->value = value;
		this->ID = ID;
}

template <typename T>
Node<T>::~Node(){
	edges.clear();
}

template <typename T>
void Node<T>::addEdge(Edge<T> edge){
	edges.push_back(edge);
}

template <typename T>
unsigned int Node<T>::getId() const {
	return ID;
}

template <typename T>
T Node<T>::getValue() const{
	return this->value;
}

template <typename T>
unsigned int Node<T>::getNumberOfEdges(){
	return this->edges.size();
}

template <typename T>
vector<Edge<T>> Node<T>::getEdges(){
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

	Node<T>* getDestiny();
	double getWeight();
};

template <typename T>
Edge<T>::Edge(Node<T>* destiny, double weight){
	this->destiny = destiny;
	this->weight = weight;
}

template <typename T>
Edge<T>::~Edge(){}

template <typename T>
Node<T>* Edge<T>::getDestiny(){
	return destiny;
}

template <typename T>
double Edge<T>::getWeight(){
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
	unsigned int getNumNodes();				//Get the number of nodes in the graph
	Node<T> getNodeByID(unsigned int ID);	//Get one node of the graph by its ID
	unsigned int getNumEdges();				// Get the number of edges in the graph
	vector<Node<T>> getNodes();
	void addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID, double weight);

//	TODO Information to save during dijkstra run
struct dijkstra_info {
	Node<T> node;
	unsigned int pathSize;
	Node<T> lastNode;
};

// TODO Dijkstra algorithm in the graph
vector<Node<T>> dijsktra(Node<T> startNode);

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
unsigned int Graph<T>::getNumNodes(){
	return nodes.size();
}

// Get the number of edges in the graph
template <typename T>
unsigned int Graph<T>::getNumEdges(){
	unsigned int size = 0;

	for(unsigned int i = 0; i < nodes.size(); i++){
		size += nodes.at(i).getNumberOfEdges();
	}
	return size;
}

//Return all the nodes in the graph
template <typename T>
vector<Node<T>> Graph<T>::getNodes(){
	return this->nodes;
}

template <typename T>
void Graph<T>::addEdge(unsigned int sourceNodeID, unsigned int destinyNodeID, double weight){
	Edge<T> edge(&nodes.at(destinyNodeID), weight);		// Create the edge (the node's ids are their place in the vector)
	nodes.at(sourceNodeID).addEdge(edge);				// Add the edge to the node
}

//Get one node of the graph by its ID
template <typename T>
Node<T> Graph<T>::getNodeByID(unsigned int ID){
	// Running all nodes
	for(unsigned int i = 0; i < this->nodes.size(); i++){
		if(nodes.at(i).getId() == ID){
			return nodes.at(i);
		}
	}

	// If the node doesn't exist, return NULL
	return NULL;
}

template <typename T>
vector<Node<T>> Graph<T>::dijsktra(Node<T> startNode){

	set<dijkstra_info> path;
	dijkstra_info currentNode;

	// Fill the set with all the node information needed
	for(unsigned int i = 0; i < nodes.size(); i++){
		if(nodes.at(i) == startNode){			// If it is the start node
			currentNode.node = nodes.at(i);		// Save it in the set
			currentNode.pathSize = 0;			// The path walked until there was none
			currentNode.lastNode = -1;			// It has no previous node

			path.insert(currentNode);
		}

		else{									// If it's not the start node
			currentNode.node = nodes.at(i);		// Save it in the set
			currentNode.pathSize = DBL_MAX;		// With "infinite" path until there
			currentNode.lastNode = NULL;		// With no previous node

			path.insert(currentNode);
		}
	}


}


#endif /* GRAPH_H_ */
