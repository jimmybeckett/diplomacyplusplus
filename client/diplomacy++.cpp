#include <iostream>
#include <fstream>
#include <string>
#include "board.h"

using namespace std;  

void printMap() {
	string line;
	ifstream myfile ("../map.txt");
	while (getline(myfile,line))
	{
		cout << line << '\n';
	}
	myfile.close();
}

int main() {
	string input;
	bool running = true;
    board* b = new board(76);
	while(running) {
		cout << endl << "enter a command (try help)" << endl;
		cin >> input;
		cout << endl;
		
		if(input == "help") {
			cout << "help : shows a list of commands" << endl;
			cout << "display : prints the board" << endl;
			cout << "exit : quits diplomacy++" << endl;
		} else if(input == "display") {
			printMap();
		} else if(input == "exit") {
			running = false;
            delete b;
			cout << "closing diplomacy++" << endl;
		} else { 
            std::cout << "command not recognized" << endl;
        }
	}
}
