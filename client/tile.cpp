#include "tile.h"


tile::tile() {
    this->abb = "";
    this->name = "";
    this->hasSupplyCenter = false;
    this->holdsFleet = false;
    this->holdsArmy = false;
    this->owner = ' ';
    this->tileType = ' ';
    this->numNeighbors = 0;
    this->neighbors = new tile*[0];
}

void tile::init(string abb, string name, bool hasSupplyCenter, bool holdsFleet, bool holdsArmy, char owner, char tileType, int numNeighbors) {
    this->abb = abb; 
    this->name = name;
    this->hasSupplyCenter = hasSupplyCenter;
    this->holdsFleet = holdsFleet;
    this->holdsArmy = holdsArmy;
    this->owner = owner;
    this->tileType = tileType;
    this->numNeighbors = numNeighbors;
    this->neighbors = new tile*[numNeighbors];
}

void tile::arrInit(tile** neighbors) {
    for (int i = 0; i < numNeighbors; i++) {
        this->neighbors[i] = neighbors[i];
    }
}

tile::~tile() {
    delete[] this->neighbors;
}

std::ostream& operator<<(std::ostream& stream, const tile& t) {
    stream << "tile[abb=" << t.abb << ", name=" << t.name << ", hasSupplyCenter=" << t.hasSupplyCenter << ", holdsFleet=" << t.holdsFleet << ", holdsArmy=" << t.holdsArmy << ", owner=" << t.owner << ", tileType=" << t.tileType << ", numNeighbors=" << t.numNeighbors << ", neighbors=[";
    for (int i = 0; i < t.numNeighbors; i++) {
        stream << t.neighbors[i]->abb;
        if (i != t.numNeighbors - 1) stream << ", ";
    }
    stream << "]}";
    return stream;
}

std::string tile::dump() {
    using namespace std;
    string d = "";
    d += abb + " " + name + " " + to_string(hasSupplyCenter) + " " + to_string(holdsFleet) + " " + to_string(holdsArmy) + " " + char(owner) + " " + char(tileType) + " " + to_string(numNeighbors) + " ";
    for (int i = 0; i < numNeighbors; i++) {
        d += neighbors[i]->abb;
        if (i != numNeighbors - 1) d += " ";
    }
    return d;
}
