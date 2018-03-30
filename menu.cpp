#include "menu.h"
#include <vector>

void menuListStation(const Graph<string> &g) {
    vector<Node<string>*> nodes = g.getNodes();

    for(int i = 0; i < nodes.size(); i++)
        cout << "[" << i << "] - " << nodes.at(i)->getInfo() << endl;
}

void menu() {
    unsigned int id_origin, id_dest;
    cout << "Origem ? ";
    cin >> id_origin;
    cout << "Destino ? ";
    cin >> id_dest;

    // ask for the criteria
    cout << "Critério ? ";
    cout << "Menor numero de transbordos\n";
    cout << "Caminhos sem andar a pé\n";
    cout << "Menor preço\n";
    cout << "Menor tempo de viagem\n";
}