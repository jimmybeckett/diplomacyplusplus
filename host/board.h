#ifndef BOARDHEADER
#define BOARDHEADER
#include "tile.h"
#include <string>

class board {
    public:
    tile** tiles;
    int numTiles;

    board(int);
    ~board();

    tile* find(std::string abb);
};

#endif
