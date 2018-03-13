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
	T value;
	vector<Edge<T>> paths;

public:
	Node(const T &value);
	virtual ~Node();

	void addEdge();

};

template <typename T>
class Edge {
private:
	Node<T>* node;
	double weight;

public:
	Edge(Node<T>* node, double weight);
	virtual ~Edge();
};
