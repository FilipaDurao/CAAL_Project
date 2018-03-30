#ifndef EDGE_H_
#define EDGE_H_

#include "Node.h"
#include <string>

using namespace std;

const constexpr double BUS_MULTIPLIER = 2.5;
const constexpr double SUBWAY_MULTIPLIER = 2.0;
const constexpr double WALK_MULTIPLIER = 10.0;

const string BUS = "bus";
const string WALK = "walk";
const string SUBWAY = "subway";

template <typename T>
class Node;
//////////////////////////////////////////////////////////////////////////////////
/////								EDGE									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Edge
{
  protected:
	Node<T> *destiny;
	double weight;
	string type;
	string lineID;

  public:
	Edge(Node<T> *destiny, double weight, string type, string lineID);

	virtual ~Edge();

	Node<T> *getDestiny() const;

	double getWeight() const;

	string getType() const;

	string getEdgeConnection() const;
};

/**
 * @brief Returns a string containing information about the edge
 *
 * The information about a edge is its type, i.e. bus, subway or walk, and the line associated with it, e.g line 204.
 *
 * @return string containing the information
 *
 */
template <typename T>
string Edge<T>::getEdgeConnection() const
{
	string result = this->type + " " + this->lineID;

	return result;
}

/**
 * @brief  Creates an Edge
 *
 * @param destiny - the node of destiny of the Edge
 * @param weight - the weight of the Edge
 * @param type - the type of Edge
 *
 */
template <typename T>
Edge<T>::Edge(Node<T> *destiny, double weight, string type, string lineID)
{
	this->destiny = destiny;
	this->weight = weight;
	this->type = type;
	this->lineID = lineID;
}

/**
 * @brief Destroys an Edge
 */
template <typename T>
Edge<T>::~Edge()
{
}

/**
 * @brief Returns the destiny of an Edge
 *
 * @return the Node that is in the end of the Edge
 */
template <typename T>
Node<T> *Edge<T>::getDestiny() const
{
	return destiny;
}

/**
 * @brief Returns the weight of an Edge
 *
 * @return the weigth of the Edge
 */
template <typename T>
string Edge<T>::getType() const
{
	return this->type;
}

/**
 * @brief Returns the weight of the Edge and counts in the multiplier considering which type of transportation is
 *
 * @return the weight of the Edge with the correct multiplier
 */
template <typename T>
double Edge<T>::getWeight() const
{
	if (this->type == SUBWAY)
		return this->weight * SUBWAY_MULTIPLIER;
	else if (this->type == BUS)
		return this->weight * BUS_MULTIPLIER;
	else
		return this->weight * WALK_MULTIPLIER;
}

#endif