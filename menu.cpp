#include "menu.h"
#include <vector>

void menuListStation(const Graph<string> &g) {
    vector<Node<string>*> nodes = g.getNodes();

    for(int i = 0; i < nodes.size(); i++)
        cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}