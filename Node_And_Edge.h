/*
 * Node_And_Edge.h
 *
 *  Created on: 12/03/2018
 *      Author: filipa
 */

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Edge;

template <typename T>
class Node {
private:
	unsigned int ID;
	T value;
	vector<Edge<T>> edges;

public:
	Node(const T &value, unsigned int ID){
		this->value = value;
		this->ID = ID;
	}

	virtual ~Node();

	void addEdge(Edge<T> edge){
		edges.push_back(edge);
	}

	unsigned int getId() const {
		return ID;
	}

};

template <typename T>
class Edge {
private:
	Node<T>* node;
	double weight;

public:
	Edge(Node<T>* node, double weight){
		this->node = node;
		this->weight = weight;
	}

	virtual ~Edge();
};
