#include "board.h"
#include <fstream>
#include <regex>
#include <stdio.h>
#include <string.h>

using namespace std;

board::board(int numTiles) {
    this->numTiles = numTiles;
    if (numTiles != 76) return; //if not a standard diplomacy board
    this->tiles = new tile*[numTiles];
    for (int i = 0; i < numTiles; i++) {
        tiles[i] = new tile();
    }
    ifstream in ("dump.dpp");
    string str;
    //Data in the form "yor York 0 0 0 E L 5 edi nth lon wal lvp"
    std::regex re ("^(\\w{3})\\s+((?:\\S+\\s+)+)(\\d)\\s+(\\d)\\s+(\\d)\\s+([A-Z ])\\s+([A-Z ])\\s+(\\d+)\\s*(.*)");
    std::smatch match;
    int index = 0;
    std::string* neighborAbbs = new std::string[numTiles];
    int neighborAbbsIndex = 0;
    while (getline(in, str)) {
        if (!regex_match(str, re)) {
            std::cout << "Failure to match " << str << std::endl;
            continue;
        }
        std::regex_search(str, match, re);
        tiles[index]->init(match.str(1), match.str(2), stoi(match.str(3)), stoi(match.str(4)), stoi(match.str(5)), match.str(6)[0], match.str(7)[0], stoi(match.str(8)));
        neighborAbbs[neighborAbbsIndex] = match.str(9);
        neighborAbbsIndex++;
        index++;
    }
    for (int i = 0; i < numTiles; i++) {
        std::string str = neighborAbbs[i];
        int next = str.find(' ');
        int prev = 0;
        int numAbbs = 0;
        while (str.find(' ', prev) != std::string::npos) {
            numAbbs++;
            prev = str.find(' ', prev + 1);
        }
        tile** neighbors = new tile*[numAbbs == 0 ? str.length() == 0 ? 0 : 1 : numAbbs + 1];
        prev = 0;
        int index = 0;
        while (next != std::string::npos) {
            std::string sub = str.substr(prev, next - prev);
            prev = next + 1;
            next = str.find(' ', next + 1);
            if (this->find(sub))
                neighbors[index] = this->find(sub);
            else 
                std::cout << "Failure to find " << sub << std::endl;
            index++;
        }
        neighbors[index] = this->find(str.substr(prev));
        tiles[i]->arrInit(neighbors);
        delete[] neighbors;
    }
    for (int i = 0; i < numTiles; i++) {
        std::cout << *tiles[i] << std::endl;
    }
    delete[] neighborAbbs;
    in.close();
}

board::~board() {
    for (int i = 0; i < this->numTiles; i++) {
        delete this->tiles[i]; 
    }
    delete[] this->tiles;
}

tile* board::find(std::string abb) {
    for (int i = 0; i < this->numTiles; i++) {
        if (this->tiles[i]->abb == abb) return this->tiles[i];
    }
    return nullptr;
}
