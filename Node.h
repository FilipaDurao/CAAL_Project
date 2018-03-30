#ifndef NODE_H_
#define NODE_H_

#include "Edge.h"
#include <vector>
#include <cfloat>
#include <cstddef>
#include <string>

using namespace std;

template <typename T>
class Edge; // declaration

//////////////////////////////////////////////////////////////////////////////////
/////								NODE									 /////
//////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Node
{
  private:
    unsigned int ID;
    T info;
    vector<Edge<T>> edges;
    bool visited = false;
    double distance = DBL_MAX;
    Node<T> *lastNode;
    int x;
    int y;

    // ---- Needed for Dijkstra with Transbordos ----
    int numTransbords;
    string lastConnection = "";

  public:
    Node(const T &value, unsigned int ID);
    Node(const T &value, unsigned int ID, int x, int y);

    virtual ~Node();

    void addEdge(Edge<T> edge);
    unsigned int getId() const;
    T getValue() const;
    unsigned int getNumberOfEdges() const;
    const vector<Edge<T>> &getEdges() const;
    T getInfo() const;
    int getX() const;
    int getY() const;

    // ---- Needed for Dijkstra with Transbordos ----
    int getNumTransbords() const;
    void setNumTransbords(int i);
    string getLastConnection() const;
    void setLastConnection(string connect);

    // ---- DIJKSTRA INFO ----
    double getDistance() const;
    void setDistance(double distance);
    Node *getLastNode();
    void setLastNode(Node *lastNode);
    void clearLastNode();
    void setVisited(bool vis);
    bool getVisited() const;

    // ---- Mutable Priority Queue Info ----
    bool operator<(Node<T> &node) const;
    int queueIndex = 0;
};
/**
 * @brief Returns the node's x position
 *
 * @return X position
 */
template <typename T>
int Node<T>::getX() const
{
    return this->x;
}

/**
 * @brief Returns the node's y position
 *
 * @return Y position
 */
template <typename T>
int Node<T>::getY() const
{
    return this->y;
}

/**
 * @brief Gives the information about the last edge that connected to this node
 *
 * This allows us to build a more detailed description of the path
 *
 * @see Edge<T>::getEdgeConnection()
 *
 * @return string containing the information
 */
template <typename T>
string Node<T>::getLastConnection() const
{
    return this->lastConnection;
}

/**
 * @brief Sets the lastConnection attribute with lastConnection passed by parameter
 *
 * @param connect - a information
 */
template <typename T>
void Node<T>::setLastConnection(string connect)
{
    this->lastConnection = connect;
}

/**
 * @brief Gives the number of times a person has to change transports when it reaches this node
 *
 * @return number of transbords
 */
template <typename T>
int Node<T>::getNumTransbords() const
{
    return this->numTransbords;
}

/**
 * @brief Sets the numTransbords attribute with numTransbords passed by parameter
 *
 * @param i - the number of Transbords
 */
template <typename T>
void Node<T>::setNumTransbords(int i)
{
    this->numTransbords = i;
}

/**
 * @brief Creates a node
 * The node's ID will be its place in the node's vector in graph, for easier access
 *
 * @param value - the node's value
 * @param ID - the node's ID
 *
 */
template <typename T>
Node<T>::Node(const T &info, unsigned int ID)
{
    this->info = info;
    this->ID = ID;
    this->distance = DBL_MAX;
    this->lastNode = NULL;
    this->visited = false;
    this->x = 0;
    this->y = 0;
    this->numTransbords = 0;
}

/**
 * @brief Creates a node
 * The node's ID will be its place in the node's vector in graph, for easier access
 *
 * @param value - the node's value
 * @param ID - the node's ID
 * @param x - the node's x position
 * @param y - the node's y position
 */
template <typename T>
Node<T>::Node(const T &info, unsigned int ID, int x, int y)
{
    this->info = info;
    this->ID = ID;
    this->distance = DBL_MAX;
    this->lastNode = NULL;
    this->visited = false;
    this->x = x;
    this->y = y;
    this->numTransbords = 0;
}

/**
 * @brief Destroys a node
 */
template <typename T>
Node<T>::~Node()
{
    edges.clear();
}

/**
 * @brief Adds an edge to a node
 *
 * @param edge - a generic edge to add to the node
 */
template <typename T>
void Node<T>::addEdge(Edge<T> edge)
{
    edges.push_back(edge);
}

/**
 * @brief Returns the node's ID
 *
 * @return ID
 */
template <typename T>
unsigned int Node<T>::getId() const
{
    return ID;
}

/**
 * @brief Returns the number of edges the node has
 *
 * @return Number of edges
 */
template <typename T>
unsigned int Node<T>::getNumberOfEdges() const
{
    return this->edges.size();
}

/**
 * @brief Returns a vector with all the edges of the node
 *
 * @return Vector with the node's edges
 */
template <typename T>
const vector<Edge<T>> &Node<T>::getEdges() const
{
    return this->edges;
}

/**
 * @brief Clears the lastNode (for Dijkstra running)
 */
template <typename T>
void Node<T>::clearLastNode()
{
    this->lastNode = NULL;
}

/**
 * @brief Returns the LastNode info for Dijkstra
 *
 * @return Last Node
 */
template <typename T>
Node<T> *Node<T>::getLastNode()
{
    return this->lastNode;
}

/**
 * @brief Sets the lastNode attribute with lastNode passed by parameter
 *
 * @param lastNode - a Node
 */
template <typename T>
void Node<T>::setLastNode(Node *lastNode)
{
    this->lastNode = lastNode;
}

/**
 * @brief Returns the current path distance to get to this Node
 *
 * @return distance
 */
template <typename T>
double Node<T>::getDistance() const
{
    return this->distance;
}

/**
 * @brief Sets the distance traveled to get to this Node
 *
 * @param distance
 */
template <typename T>
void Node<T>::setDistance(double distance)
{
    this->distance = distance;
}

/**
 * @brief  Returns the node's information
 *
 * @return info
 */
template <typename T>
T Node<T>::getInfo() const
{
    return this->info;
}

/**
 * @brief Sets the visited attribute on the Node
 *
 * @param vis - what to set
 */
template <typename T>
void Node<T>::setVisited(bool vis)
{
    this->visited = vis;
}

/**
 * @brief Gets the information on wether the Node has been visited or not
 *
 * @return true or false
 */
template <typename T>
bool Node<T>::getVisited() const
{
    return this->visited;
}

/**
 * @brief Operator < to be able to compare different Nodes
 *
 * @param node - a Node to compare to the current Node
 *
 * @return true or false wether the Node is minor than the one we are comparing to
 */
template <typename T>
bool Node<T>::operator<(Node<T> &node) const
{
    return this->distance < node.distance;
}

#endif