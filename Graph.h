/*
 * Graph.h
 *
 *  Created on: 12/03/2018
 *      Author: filipa
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node_And_Edge.h"

template <typename T>
class Graph {
private:
	vector<Node<T>> nodes;

public:
	Graph(){};

	virtual ~Graph();

	void addNode(T nodeData){
		nodes.push_back(Node<T>(nodeData , nodes.size()));
	}

	Node<T> getNodeByID(){
		//TODO getNodeByID
	}
};

#endif /* GRAPH_H_ */
