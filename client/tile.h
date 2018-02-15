#ifndef TILEHEADER
#define TILEHEADER
#include <string>
#include <iostream>

using namespace std;

class tile {
public:
    string abb;
	string name;
	bool hasSupplyCenter;
	bool holdsFleet;
	bool holdsArmy;
	char owner; //country to most recently own the territory
    char tileType; //'L' for landlocked, 'C' for coastal, 'S' for sea
    int numNeighbors;
	tile** neighbors; //an array of pointers to tiles

    tile();
    ~tile();
	void init(string abb, string name, bool hasSupplyCenter, bool holdsFleet, bool holdsArmy, char owner, char tileType, int numNeighbors);
    void arrInit(tile** neighbors);
    string dump();

    friend ostream& operator<<(ostream& stream, const tile& t);
};

#endif
