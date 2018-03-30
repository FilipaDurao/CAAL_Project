/*
 * Graph.h
 *
 *  Created on: 12/03/2018
 *      Author: filipa
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "MutablePriorityQueue.h"
#include "Node.h"

#include <set>
#include <cfloat>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <climits>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
/////								GRAPH									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Graph
{
  private:
	vector<Node<T> *> nodes;

  public:
	Graph();

	virtual ~Graph();

	void addNode(T nodeData, int x, int y);
	unsigned int getNumNodes() const;			 //Get the number of nodes in the graph
	Node<T> *getNodeByID(unsigned int ID) const; //Get one node of the graph by its ID
	unsigned int getNumEdges() const;			 // Get the number of edges in the graph
	vector<Node<T> *> getNodes() const;

	// ---- Edges Types ----
	void addBusEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
					double weight, string lineID);
	void addSubwayEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
					   double weight, string lineID);
	void addWalkEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
					 double weight, string lineID);

	vector<T> getPath(Node<T> *dest) const;

	string getDetailedPath(Node<T> *dest) const;

	// ---- Dijkstra Algorithms ----
	Node<T> *dijkstra_heap(Node<T> *startNode, Node<T> *endNode);
	Node<T> *dijkstra_queue(Node<T> *startNode, Node<T> *endNode);
	Node<T> *dijkstra_queue_NO_WALK(Node<T> *startNode, Node<T> *endNode);
	Node<T> *dijkstra_queue_TRANSBORDS(Node<T> *startNode, Node<T> *endNode,
									   int maxNum);
};

/**
 * @brief Returns a node by its ID
 * 
 * @tparam T 
 * @param ID Node ID
 * @return Node<T>* A pointer to the node
 * @throw out_of_range If the node doesn't exist
 */
template <typename T>
Node<T> *Graph<T>::getNodeByID(unsigned int ID) const
{
	return this->nodes.at(ID);
}

/**
 * @brief Creates a Graph
 */
template <typename T>
Graph<T>::Graph()
{
}

/**
 * @brief Destroys a Graph
 */
template <typename T>
Graph<T>::~Graph()
{
	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
		delete (*it);
	nodes.clear();
}

/**
 * @brief Creates a Node and adds it to the Graph
 *
 * @param nodeData - the data with which we create a Node
 */
template <typename T>
void Graph<T>::addNode(T nodeData, int x, int y)
{
	this->nodes.push_back(new Node<T>(nodeData, nodes.size(), x, y));
}

/**
 * @brief Gets the number of Nodes in the Graph
 *
 * @return The size of the Nodes vector in the Graph
 */
template <typename T>
unsigned int Graph<T>::getNumNodes() const
{
	return nodes.size();
}

/**
 * @brief Gets the number of Edges in the Graph
 *
 * @return The sum of all the Edges in all the Nodes in the Graph
 */
template <typename T>
unsigned int Graph<T>::getNumEdges() const
{
	unsigned int size = 0;

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		size += nodes.at(i)->getNumberOfEdges();
	}
	return size;
}

/**
 * @brief Returns all the Nodes in the Graph
 *
 * @return a vector equal to the Nodes vector in Graph
 */
template <typename T>
vector<Node<T> *> Graph<T>::getNodes() const
{
	return this->nodes;
}

/**
 * @brief Creates an BusEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template <typename T>
void Graph<T>::addBusEdge(unsigned int sourceNodeID, unsigned int destinyNodeID,
						  double weight, string lineID)
{
	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, BUS, lineID);
	this->nodes.at(sourceNodeID)->addEdge(edge);
}

/**
 * @brief Creates an SubwayEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template <typename T>
void Graph<T>::addSubwayEdge(unsigned int sourceNodeID,
							 unsigned int destinyNodeID, double weight, string lineID)
{
	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, SUBWAY, lineID);
	this->nodes.at(sourceNodeID)->addEdge(edge);
}

/**
 * @brief Creates an WalkEdge and adds it to a certain existing Node
 *
 * @param sourceNodeID - the ID of the source Node of the Edge
 * @param destinyNodeID - the ID of the destiny Node of the Edge
 * @param weight - the weight of the Edge
 */
template <typename T>
void Graph<T>::addWalkEdge(unsigned int sourceNodeID,
						   unsigned int destinyNodeID, double weight, string lineID)
{

	Edge<T> edge = Edge<T>(nodes.at(destinyNodeID), weight, WALK, lineID);
	this->nodes.at(sourceNodeID)->addEdge(edge);
}

/*
 * Max heap by default has the highest value on the top of the heap
 * Since we want the minimum, in terms of distance, we must define the operator in the reverse orded
 *
 */
template <typename T>
struct compareDistance
{
	bool operator()(Node<T> *rhs, Node<T> *lhs) const
	{
		return rhs->getDistance() > lhs->getDistance();
	}
};

/**
 * @brief Returns a vector with the path with the "smallest" distance from the startNode to the endNode, using a heap
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 *
 * @return Node * - the final Node of the path, so we can walk it back to get the best path
 */
template <typename T>
Node<T> *Graph<T>::dijkstra_heap(Node<T> *startNode, Node<T> *endNode)
{

	vector<Node<T> *> path = {};

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
	}

	startNode->setDistance(0);
	path.push_back(startNode);

	//making the heap, since it only has one element does not need the function
	make_heap(path.begin(), path.end());

	Node<T> *v;
	Node<T> *w;
	double new_distance;
	double old_distance;

	while (!path.empty())
	{

		//the miminum value is always in the top
		v = path.front();

		//putting the min value (considered the max since we swap the operator) in the back
		pop_heap(path.begin(), path.end());

		//removing it
		path.pop_back();

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++)
		{

			w = it->getDestiny();
			new_distance = v->getDistance() + it->getWeight();
			old_distance = w->getDistance();

			if (old_distance > new_distance)
			{

				w->setDistance(new_distance);
				w->setLastNode(v);

				if (old_distance == DBL_MAX)
				{ //aka is not in the path
					path.push_back(w);
				}

				make_heap(path.begin(), path.end(), compareDistance<T>());
			}
		}
	}

	return endNode;
}

/**
 * @brief Calculates the path with the "smallest" distance from the startNode to the endNode, using a mutable priority queue
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 *
 * @return Node * - the final Node of the path, so we can walk it back to get the best path
 */
template <class T>
Node<T> *Graph<T>::dijkstra_queue(Node<T> *startNode, Node<T> *endNode)
{

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
		(*it)->setVisited(false);
		(*it)->setLastConnection("NOT");
	}

	startNode->setDistance(0);
	startNode->setLastConnection("FIRST");
	MutablePriorityQueue<Node<T>> q;
	q.insert(startNode);

	Node<T> *v;
	Node<T> *w;
	double old_distance;
	double new_distance;

	while (!q.empty())
	{

		v = q.extractMin();

		if (v->getId() == endNode->getId())
			break;

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++)
		{

			w = it->getDestiny();
			old_distance = w->getDistance();
			new_distance = v->getDistance() + it->getWeight();

			if (old_distance > new_distance)
			{

				w->setDistance(new_distance);
				w->setLastNode(v);
				w->setLastConnection(it->getEdgeConnection());
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

/**
 * @brief Calculates the path with the "smallest" distance from the startNode to the endNode, without walking, using a mutable priority queue
 *
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 *
 * @return Node * - the final Node of the path, so we can walk it back to get the best path
 */
template <class T>
Node<T> *Graph<T>::dijkstra_queue_NO_WALK(Node<T> *startNode,
										  Node<T> *endNode)
{

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
		(*it)->setVisited(false);
		(*it)->setLastConnection("NOT");
	}

	startNode->setDistance(0);
	startNode->setLastConnection("FIRST");
	MutablePriorityQueue<Node<T>> q;
	q.insert(startNode);

	Node<T> *v;
	Node<T> *w;
	double old_distance;
	double new_distance;

	while (!q.empty())
	{

		v = q.extractMin();

		if (v->getId() == endNode->getId())
			break;

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++)
		{

			if (it->getType() == WALK)
				continue;

			w = it->getDestiny();
			old_distance = w->getDistance();
			new_distance = v->getDistance() + it->getWeight();

			if (old_distance > new_distance)
			{

				w->setDistance(new_distance);
				w->setLastNode(v);
				w->setLastConnection(it->getEdgeConnection());

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

/**
 * @brief Calculates the path with the "smallest" distance from the startNode to the endNode, using a mutable priority queue, and allowing
 * only some exchanges between transports
 *
 *
 *
 * @param startNode - the beginning Node of the path
 * @param endNode - the end Node of the path
 * @param maxNum - the maximum allowed number of transports exchanges
 *
 * @return Node * - the final Node of the path, so we can walk it back to get the best path
 */
template <class T>
Node<T> *Graph<T>::dijkstra_queue_TRANSBORDS(Node<T> *startNode,
											 Node<T> *endNode,
											 int maxNum)
{

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++)
	{
		(*it)->setDistance(DBL_MAX);
		(*it)->clearLastNode();
		(*it)->setVisited(false);
		(*it)->setNumTransbords(INT_MAX);
		(*it)->setLastConnection("NOT");
	}

	startNode->setDistance(0);
	startNode->setNumTransbords(-1);
	startNode->setLastConnection("FIRST");

	MutablePriorityQueue<Node<T>> q;
	q.insert(startNode);

	Node<T> *v;
	Node<T> *w;
	double old_distance;
	double new_distance;

	while (!q.empty())
	{

		v = q.extractMin();

		for (auto it = v->getEdges().begin(); it != v->getEdges().end(); it++)
		{

			int currentTransbords = v->getNumTransbords();

			/*if the method of transport used or the line has changed
			 * must add another "transbordo"
			 */
			if (v->getLastConnection() != it->getEdgeConnection())
			{

				currentTransbords++;
			}

			if (currentTransbords > maxNum)
			{
				continue;
			}

			w = it->getDestiny();
			old_distance = w->getDistance();
			new_distance = v->getDistance() + it->getWeight();

			if (old_distance > new_distance)
			{

				w->setDistance(new_distance);
				w->setLastNode(v);
				w->setLastConnection(it->getEdgeConnection());
				w->setNumTransbords(currentTransbords);

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

/**
 * @brief get the path to a certain Node
 *
 * @param dest - the destiny Node
 *
 * @return the vector with the full path, ordered
 */
template <class T>
vector<T> Graph<T>::getPath(Node<T> *dest) const
{

	vector<T> res;

	while (dest->getLastNode() != NULL)
	{
		res.push_back(dest->getInfo());
		dest = dest->getLastNode();
	}

	res.push_back(dest->getInfo());
	reverse(res.begin(), res.end());
	return res;
}
/**
 * @brief Gives detailed Information about the path to take
 *
 * @param dest - the destiny Node
 *
 *
 * @return string containing the information
 */
template <class T>
string Graph<T>::getDetailedPath(Node<T> *dest) const
{
	string result = "";

	queue<string> queue;

	double total_distance = dest->getDistance();

	if (dest->getLastNode() == NULL)
	{
		string oops = "It is impossible to travel to ";
		oops += dest->getInfo();
		oops += " with those constrains!\n";
		return oops;
	}

	while (dest->getLastNode() != NULL)
	{
		string one_stop = "At ";
		one_stop += dest->getLastNode()->getInfo() + " catch the ";
		one_stop += dest->getLastConnection() + " to " + dest->getInfo() + "\n";
		queue.push(one_stop);
		dest = dest->getLastNode();
	}

	while (!queue.empty())
	{
		result = queue.front() + result;
		queue.pop();
	}

	result += "Total Distance: " + to_string(round(total_distance * 100) / 100).substr(0, 5) + " meters";

	return result;
}

#endif /* GRAPH_H_ */
