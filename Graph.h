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

	Node<T> getNodeByID(unsigned int ID){

		for(unsigned int i = 0; i < this->nodes.size(); i++){
			if(nodes.at(i).getId() == ID){
				return nodes.at(i);
			}
		}

		// If the node doesn't exist, return NULL
		return NULL;
	}
};

#endif /* GRAPH_H_ */
