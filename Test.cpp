#include "Test.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Node;

const constexpr double BUS_TIME_MULTIPLIER = 0.025;
const constexpr double SUBWAY_TIME_MULTIPLIER = 0.02;
const constexpr double WALK_TIME_MULTIPLIER = 0.1;

#define INF std::numeric_limits<double>::max()

/************************* Node  **************************/

template<class T>
class Node {
	T info;                // contents
	vector<Edge<T> > adj;                // outgoing edges
	bool visited;                // auxiliary field
	double dist = 0;
	Node<T> *path = NULL;
	int queueIndex = 0;                // required by MutablePriorityQueue
	int x;
	int y;
	bool processing = false;
	void addEdge(Node<T> *dest, double w);

public:
	Node(T in);
	Node(T in, int x, int y);
	bool operator<(Node<T> & node) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Node *getPath() const;
	friend class Graph<T> ;
	friend class MutablePriorityQueue<Node<T>> ;

	void setDist(double dist);
	void setPath(Node<T> * path);
	double euclidianDistance(Node<T> * w);
};

template<class T>
Node<T>::Node(T in, int x, int y) {
	this->x = x;
	this->y = y;
	this->info = in;
	this->visited = false;

}

template<class T>
double Node<T>::euclidianDistance(Node<T> * w) {

	return WALK_TIME_MULTIPLIER
			* sqrt(pow(this->x - w->x, 2) + pow(this->y - w->y, 2));

}

template<class T>
void Node<T>::setDist(double dist) {
	this->dist = dist;
}

template<class T>
void Node<T>::setPath(Node<T> * path) {
	this->path = path;
}

template<class T>
Node<T>::Node(T in) :
		info(in) {
	this->x = x;
	this->y = y;
	this->visited = false;
}

/*
 * Auxiliary function to add an outgoing edge to a node (this),
 * with a given destination node (d) and edge weight (w).
 */
template<class T>
void Node<T>::addEdge(Node<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template<class T>
bool Node<T>::operator<(Node<T> & node) const {
	return this->dist < node.dist;
}

template<class T>
T Node<T>::getInfo() const {
	return this->info;
}

template<class T>
double Node<T>::getDist() const {
	return this->dist;
}

template<class T>
Node<T> *Node<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
	Node<T> * dest;      // destination node
	double weight;      // edge weight
	int edge_type;
public:
	Edge(Node<T> *d, double w);
	friend class Graph<T> ;
	friend class Node<T> ;
	double getWeight();

};

template<class T>
double Edge<T>::getWeight() {
	if (this->edge_type == 0) {
		return this->weight * BUS_TIME_MULTIPLIER;
	} else if (this->edge_type == 1) {
		return this->weight * SUBWAY_TIME_MULTIPLIER;
	} else
		return this->weight * WALK_TIME_MULTIPLIER;
}

template<class T>
Edge<T>::Edge(Node<T> *d, double w) :
		dest(d), weight(w) {

	this->edge_type = rand() % 3;
}

/*************************** Graph  **************************/

template<class T>
class Graph {
	vector<Node<T> *> nodes;    // node set

public:
	Node<T> *findNode(const T &in) const;
	bool addNode(const T &in);
	bool addNode(const T &in, int x, int y);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addEdge(const T &sourc, const T &dest);
	int getNumNodes() const;
	vector<Node<T> *> getNodes() const;
	int getNumEdges();
	void listNodes();

	// ---- COMPARING DATA STRUCTURE ----
	void dijkstra_queue(const T &s);
	void dijkstra_heap(const T &s);

	// ---- COMPARING DIFFERENT ALGORITHMS ----
	void A_Star(const T &s, const T &endNode);
	void dijkstra_queue_end(const T &s, const T &endNode);

	vector<T> getPath(const T &origin, const T &dest) const;

};

template<class T>
void Graph<T>::listNodes() {

	int counter = 0;

	for (auto t : nodes) {
		for (auto i : t->adj) {
			cout << "weight: " << i.weight << endl;
		}
	}
}

template<class T>
int Graph<T>::getNumEdges() {
	int counter = 0;
	for (auto t : nodes)
		counter += t->adj.size();
	return counter;
}

template<class T>
bool Graph<T>::addNode(const T &in, int x, int y) {
	if (findNode(in) != NULL)
		return false;
	nodes.push_back(new Node<T>(in, x, y));
	return true;
}

template<class T>
int Graph<T>::getNumNodes() const {
	return nodes.size();
}

template<class T>
vector<Node<T> *> Graph<T>::getNodes() const {
	return nodes;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Node<T> * Graph<T>::findNode(const T &in) const {
	for (auto v : nodes)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addNode(const T &in) {
	if (findNode(in) != NULL)
		return false;
	nodes.push_back(new Node<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findNode(sourc);
	auto v2 = findNode(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2, w);
	return true;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest) {
	auto v1 = findNode(sourc);
	auto v2 = findNode(dest);
	if (v1 == NULL || v2 == NULL)
		return false;

	double w = v1->euclidianDistance(v2);

	w *= 100;

	v1->addEdge(v2, w);
	return true;
}

template<class T>
void Graph<T>::dijkstra_queue(const T &origin) {

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {

		(*it)->setDist(DBL_MAX);
		(*it)->setPath(NULL);
		(*it)->visited = false;

	}

	Node<T> * startNode = this->findNode(origin);

	startNode->setDist(0);

	MutablePriorityQueue<Node<T> > q;

	q.insert(startNode);

	while (!q.empty()) {

		Node<T> * v = q.extractMin();

		for (auto it = v->adj.begin(); it != v->adj.end(); it++) {

			Node<T> * w = it->dest;

			double old_distance = w->getDist();

			double new_distance = v->getDist() + it->getWeight();

			if (old_distance > new_distance) {

				w->setDist(new_distance);

				w->setPath(v);

				if (!w->visited)
					q.insert(w);
				else
					q.decreaseKey(w);

				w->visited = true;
			}

		}

	}

}

template<class T>
void Graph<T>::A_Star(const T &origin, const T &end) {

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {

		(*it)->setDist(DBL_MAX);
		(*it)->setPath(NULL);
		(*it)->visited = false;

	}

	Node<T> * startNode = this->findNode(origin);
	Node<T> * endNode = this->findNode(end);

	if (startNode == NULL || endNode == NULL) {
		cout << "Null Node\n";
		return;
	}

	startNode->setDist(0);

	MutablePriorityQueue<Node<T> > q;

	q.insert(startNode);

	while (!q.empty()) {

		Node<T> * v = q.extractMin();

		if (v->getInfo() == endNode->getInfo()) {

			endNode->setDist(
					endNode->getDist() + startNode->euclidianDistance(endNode));

			break;

		}

		for (auto it = v->adj.begin(); it != v->adj.end(); it++) {

			Node<T> * w = it->dest;

			double old_distance = w->getDist();

			double new_distance = (v->getDist() + it->getWeight())
					- v->euclidianDistance(endNode)
					+ w->euclidianDistance(endNode);

			if (old_distance > new_distance) {

				w->setDist(new_distance);

				w->setPath(v);

				if (!w->visited)
					q.insert(w);
				else
					q.decreaseKey(w);

				w->visited = true;
			}

		}

	}

}

template<class T>
void Graph<T>::dijkstra_queue_end(const T &origin, const T &end) {

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {

		(*it)->setDist(DBL_MAX);
		(*it)->setPath(NULL);
		(*it)->visited = false;

	}

	Node<T> * startNode = this->findNode(origin);

	Node<T> * endNode = this->findNode(end);

	if (startNode == NULL || endNode == NULL) {
		cout << "Null Node\n";
		return;
	}

	startNode->setDist(0);

	MutablePriorityQueue<Node<T> > q;

	q.insert(startNode);

	while (!q.empty()) {

		Node<T> * v = q.extractMin();

		if (v->getInfo() == endNode->getInfo())

			break;

		for (auto it = v->adj.begin(); it != v->adj.end(); it++) {

			Node<T> * w = it->dest;

			double old_distance = w->getDist();

			double new_distance = v->getDist() + it->getWeight();

			if (old_distance > new_distance) {

				w->setDist(new_distance);

				w->setPath(v);

				if (!w->visited)
					q.insert(w);
				else
					q.decreaseKey(w);

				w->visited = true;
			}

		}

	}

}

/*
 * Max heap by default has the highest value on the top of the heap
 * Since we want the minimum, in terms of distance, we must define the operator in the reverse orded
 *
 */
template<typename T>
struct compareDistance {
	bool operator()(Node<T> * rhs, Node<T> * lhs) const {
		return rhs->getDist() > lhs->getDist();
	}
};

/**
 * @brief Returns a vector with the path with the "smallest" distance from the startNode to the endNode, using a heap
 *
 * @param startNode - the beginning Node of the path
 *
 */
template<typename T>
void Graph<T>::dijkstra_heap(const T & s) {

	vector<Node<T> *> path = { };

	for (auto it = this->nodes.begin(); it != this->nodes.end(); it++) {

		(*it)->setDist(DBL_MAX);
		(*it)->setPath(NULL);
		(*it)->visited = false;

	}

	Node<T> *startNode = this->findNode(s);

	startNode->setDist(0);
	path.push_back(startNode);

	//making the heap, since it only has one element does not need the function
	make_heap(path.begin(), path.end());

	Node<T> *v;
	Node<T> *w;
	double new_distance;
	double old_distance;

	while (!path.empty()) {

		//the miminum value is always in the top
		v = path.front();

		//putting the min value (considered the max since we swap the operator) in the back
		pop_heap(path.begin(), path.end());

		//removing it
		path.pop_back();

		for (auto it = v->adj.begin(); it != v->adj.end(); it++) {

			w = it->dest;

			old_distance = w->getDist();

			new_distance = v->getDist() + it->getWeight();

			if (old_distance > new_distance) {

				w->setDist(new_distance);

				w->setPath(v);

				if (!w->visited) {  //aka is not in the path
					w->visited = true;
					path.push_back(w);
				}

				make_heap(path.begin(), path.end(), compareDistance<T>());

			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;

	Node<T> * src = this->findNode(origin);

	Node<T> * dst = this->findNode(dest);

	cout << "\ntotal distance: " << dst->getDist() << endl;

	while (dst->getPath() != NULL) {

		res.push_back(dst->getInfo());

		dst = dst->getPath();

	}

	res.push_back(origin);

	reverse(res.begin(), res.end());

	return res;
}

void geneateRandomGridGraph(int n, Graph<pair<int, int>> & g) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g.addNode(make_pair(i, j), i, j);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int di = -1; di <= 1; di++)
				for (int dj = -1; dj <= 1; dj++)
					if ((di != 0) != (dj != 0) && i + di >= 0 && i + di < n
							&& j + dj >= 0 && j + dj < n)
						g.addEdge(make_pair(i, j), make_pair(i + di, j + dj));
}

void geneateRandomGridGraphExtended(int n, Graph<pair<int, int>> & g) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g.addNode(make_pair(i, j), i, j);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int di = -100; di <= 100; di++)
				for (int dj = -100; dj <= 100; dj++)
					if ((di != 0) != (dj != 0) && i + di >= 0 && i + di < n
							&& j + dj >= 0 && j + dj < n)
						g.addEdge(make_pair(i, j), make_pair(i + di, j + dj));
}

void test_performance_dijkstra_queue() {
	cout << "Testing Dijkstra performance with queue:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int> > g;
		std::cout << "Dijkstra generating grid " << n << " x " << n << " ..."
				<< std::endl;
		geneateRandomGridGraph(n, g);
		std::cout << "Dijkstra Queue processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.dijkstra_queue(make_pair(i, j));
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "Dijkstra processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}

}

void test_performance_dijkstra_heap() {
	cout << "Testing Dijkstra performance with heap:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int> > g;
		std::cout << "Dijkstra generating grid " << n << " x " << n << " ..."
				<< std::endl;
		geneateRandomGridGraph(n, g);
		std::cout << "Num Nodes: " << g.getNumNodes() << " Num Edges: "
				<< g.getNumEdges() << endl;
		std::cout << "Dijkstra Heap processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.dijkstra_heap(make_pair(i, j));
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "Dijkstra processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}
}

void testPath() {
	Graph<pair<int, int>> g;

	int n = 10;
	geneateRandomGridGraphExtended(n, g);

	std::vector<pair<int, int> > res;

	g.A_Star(make_pair(1, 1), make_pair(7, 9));

	res = g.getPath(make_pair(1, 1), make_pair(7, 9));

	for (auto it = res.begin(); it != res.end(); it++) {
		cout << "(" << it->first << "," << it->second << ")" << "\t";
	}

	g.dijkstra_queue_end(make_pair(1, 1), make_pair(7, 9));
	res = g.getPath(make_pair(1, 1), make_pair(7, 9));

	for (auto it = res.begin(); it != res.end(); it++) {
		cout << "(" << it->first << "," << it->second << ")" << "\t";
	}

	g.dijkstra_queue(make_pair(1, 1));
	res = g.getPath(make_pair(1, 1), make_pair(7, 9));

	for (auto it = res.begin(); it != res.end(); it++) {
		cout << "(" << it->first << "," << it->second << ")" << "\t";
	}

}

void compareAlgorithmsMatrixVersion() {

	/*
	cout << "Testing Dijkstra performance with queue:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int> > g;
		std::cout << "Dijkstra generating grid " << n << " x " << n << " ...";
		geneateRandomGridGraph(n, g);
		std::cout << "\tNum Nodes: " << g.getNumNodes() << "\tNum Edges: "
				<< g.getNumEdges() << endl;

		std::cout << "Dijkstra Queue processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.dijkstra_queue_end(make_pair(i, j),
						make_pair((n - 1), (n - 1)));
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "Dijkstra processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}
	*/

	cout << "\n\nTesting A Star performance with queue:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int>> g;
		std::cout << "A Star generating grid " << n << " x " << n << " ...";
		geneateRandomGridGraph(n, g);
		std::cout << "\tNum Nodes: " << g.getNumNodes() << "\tNum Edges: "
				<< g.getNumEdges() << endl;
		std::cout << "A Star Queue processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.A_Star(make_pair(i, j), make_pair((n - 1), (n - 1)));

		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "A Star processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}
}

void compareAlgorithmsExtendedVersion() {

	cout << "Testing Dijkstra performance with queue:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int> > g;
		std::cout << "Dijkstra generating grid " << n << " x " << n << " ...";
		geneateRandomGridGraphExtended(n, g);
		std::cout << "\tNum Nodes: " << g.getNumNodes() << "\tNum Edges: "
				<< g.getNumEdges() << endl;

		std::cout << "Dijkstra Queue processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.dijkstra_queue_end(make_pair(i, j),
						make_pair((n - 1), (n - 1)));
		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "Dijkstra processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}

	cout << "\n\nTesting A Star performance with queue:\n";
	for (int n = 10; n <= 100; n += 10) {
		Graph<pair<int, int>> g;
		std::cout << "A Star generating grid " << n << " x " << n << " ...";
		geneateRandomGridGraphExtended(n, g);
		std::cout << "\tNum Nodes: " << g.getNumNodes() << "\tNum Edges: "
				<< g.getNumEdges() << endl;
		std::cout << "A Star Queue processing grid " << n << " x " << n
				<< " ..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g.A_Star(make_pair(i, j), make_pair((n - 1), (n - 1)));

		auto finish = std::chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<chrono::microseconds>(
				finish - start).count();
		std::cout << "A Star processing grid " << n << " x " << n
				<< " average time (micro-seconds)=" << (elapsed / (n * n))
				<< std::endl;
	}

}
