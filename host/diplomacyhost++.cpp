#include <iostream>
#include <fstream>
#include <string>

using namespace std;  

class tile()
{
	bool hasSupplyCenter;
	bool holdsFleet;
	bool holdsArmy;
	char unitType;			//'A' is army, 'F' is fleet, ' ' is empty
	char unitOwner;			//character for the country
	tile* neighbors[];

	tile() 
	{
		hasSupplyCenter = false;
		holdsFleet = true;
		holdsArmy = true;
		unitType = ' ';			//'A' is army, 'F' is fleet, ' ' is empty
		unitOwner = ' ';			//character for the country
		neighbors = tile*[0];
	}
};

class board()
{
/*______________________________________________________________________________________________________________________________________________________________________________________________________________
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\    \| /_____~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~___~|~_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~____/                |                 |                 |                 |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/            /~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~___/   \_/ \___~~~~~~~~~~A:A~BAR~~~~~___/                     |  Your Orders    |  Spring 1901    |  Winter 1900    |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\_         _/~~~~~~~~~~~~~~~~~~~A:A~~~~~~~~~~~~~~~~~~~~~/        ____   \___________~~~~~~~~~/                         |_________________|_________________|_________________|
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\_______/~~~~~~~~~~~~~~~~~~~~~NWG~~~~~~~~~~~~~~~~~~~~/    ____/    \__/           \___~~~~~\_                        |                 |                 |                 |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|    /    \       \               \~~~~~~|                       |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~___/    /      |       \      ________/~~~~~/                        |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~___/       /       |___     |    /_~~~~~~~~~~~_/___                      |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~__~~__~~__~~~~~~___/        __/       /~~~~\     \     \___~~~___/     \__                   |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~A:A~~~~~~~~~~~~~~~~~~~~~~~~/~~~~~~~~~~~~~\~~_/          _/        _|~~~~~~|     \_       \_/            \                  |  A:A Aaa > Aaa  |  -------------  |  -------------  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~NAO~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~/    A:A    /         /~~~~~~~/        \   nc                 \_                |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~____~~~~~/~~~~~~~~~~~~~~~~/    Nor    /       __/~~~~~~~|   A:A    |                       \__             |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~A:A~|   |\___~~~~~~~~~~~~~~~~~|          _/       |~~~~~~~~~~/   Fin    | _                       _\            |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_Cly /  Edi~~~~~~~~A:A~~~~~~~\_    * _/          \~~~A:A~~|        __/ [~]   A:A             __/  \_          |  A:A Aaa > Aaa  |  -------------  |  -------------  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~__~~~\ __| * /~A:A~~~~~~NTH~~~~~~~~~\____/     A:A   * |~~GOB~~~\______/~~\      Stp           __/       \_        |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~___/  \~_~\   \_|~~~~~~~~~~~~~~~~~~~~~~|~~~~~\     Swe   _/~~~~~~~~~~~________/*               ___/            \       |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/      /~~~~|* |  \~~~~~~~~~~~~__~~__~~__~~A:A~\         /~~~~~~~~~~~_/     |   sc       ______/                 |      |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/     _/~A:A~Lvp/ Yor~A:A~~~~~~~~~~~~~~/  \__SKA~|       /~\~~__~~~~~/        \       ___/                        |      |  A:A Aaa > Aaa  |  -------------  |  -------------  |
|~~~~~~~~~~~~~~~~~~~~~~~__~~__~~|_____/~~~~__/__/____|~~~~~~~~~~|~~A:A~| A:A /~~_~|     _|~~~~~~~~~\~/   A:A    |  ___/                             \     |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~/~~~~~~~~~~~~~~~~~~__/      /   \_~~~~~~~~~~~~HEL~| Den *|=\|=\___/~~~A:A~~~~__|   Liv     |_/                                  |    |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~A:A~~~~~~~~/_ A:A  _/ A:A  |~~~~~~~~|~~~~_~~\__ _/~~~~~~~~~~~~BAL~~~~/             /                  *                   \   |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~/~~~~~~~~IRE~~~~~~~~_/ Wal | Lon *_/~~~~~~_______/ \_/==|_~~~~___~~~~~~~~~~~_/ \        ___/               A:A Mos                  |  |  A:A Aaa > Aaa  |  -------------  |  -------------  |
|~__~~__~~__~~__~~__~~__~~__~~__~~__~~/_______|_____\~~~~~__/  A:A  |     *  \__/   \_________/    |    __/                                       _____|  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~A:A~~~~~~~\___/ | * Hol /  A:A   _/   A:A     \  A:A   /____/                                    _____/      \ |_________________|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~\~~__~~__~~____~~~CHA~~_____/ A:A  \_____/  Kie __/  * Ber ______| Pru  /     \__     ___                _________/             \____              |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/ *  \______/ A:A \_Bel *_/    |_____/  \ ______/       \____/   A:A   \___/   \___    _______/                            \___       ___|  -------------- |  -------------  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\_          | Pic / \__/  A:A  |      *  |______ A:A Sil |       War    |          \__/                                        \   __/~~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\_  A:A   |____/     |  Ruh_/   A:A   /       \________|_  * _________|___  A:A     \               A:A Sev                   \_/~~~~~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~A:A~~~~~~~~~~~~~~~~~~~~~\  Bre /  * | A:A  |____/   Mun ___/ A:A Boh  /____    \__/             \   Ukr   /                    __                    /~~~~~~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~MAO~~~~~~~~~~~~~~~~~~~~~~|____/ A:A | Bur /____________/   \_________/     \____     A:A Gal     |_      /               _____/~_/                   \~~~~~~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|    \ Par |    |        |    A:A  __|_____  * A:A   | \________   ____/  \____/       ___     /~~~~~~/                      \_~~~~~|  -------------  |  -------------  |
|~~~~~~~~~~~~~~~~~~~_______~~~~~~~~~~~~/ A:A  \ __/   _/  _______/ Tyr ___/_____   \__ Vie  /           \_/            \__   _/~~~/ *  \~~~__/                        _\~~~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~/   nc  \__~~~~~~__/  Gas __|_____/ \_/  A:A  \____/   A:A   \     \____/   * A:A      \     A:A       \_/~~~~~\____/~~~\________               __/  \_~~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~/___        \____/      __/  A:A      /   Pie    ___\ Ven *___/         \__    Bud       |    Rum  *   _/~~~~~~~~~~~~~~~~~~~~~~~~~\____      ___/       \~|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~/    \            \_____/    Mar ___* |   _______/    \    |~~~\__*  A:A    \_________   /    _________/~~~~~~A:A~~~~~~~~~~~~~~~~~~~~~~~\____/            \|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~_| A:A  |   A:A         \___     _/~~~\__\_/~~~~\____A:A |   _\~~~~~\   Tri    \        \_/  __/        /~~~~~~BLA~~~~~~~~___~~~~~~~~~~___/                  |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~/  Por  /    Spa             \___/~~~~~~~~~~~~~~~~~~~~\Tus|__/  \~~~~~\__        |__* A:A  \ /   A:A  ec \~~~~~~~~~~~~~~__/   \________/         A:A Arm      |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~|  *  __/                 ____/~~~~~~~~~~A:A~~~~~~~~~/~~\_/ * \_  \__~A:A~\__    /   \  Ser  |    Bul  ____\~~~~~~~~___/                \__                    |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~|    /         *        _/~~~~~~~~_~~~~~~GOL~~~[]~~~~~~~~~\_A:A \ A:A\~ADR~~~\__/ A:A |______|  *    _/     \______/                     __\____               |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~|___/                  /~~~~~~__~|/~~~~~~~~~~~~~_~~/~~~~~~~~\Rom | Apu\~~~~~~~~~\ Alb |      _\_ sc / A:A  //  |      A:A Ank  _________/       \______        |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~\__          sc ____\~~[]~|_/~~~~~~~~~~~~~~~| \~~~~~~~~~~~\__/ \___ \__~~~~__~|   /     _/~~~\__| Con _//   |    *  _______/                   /    \___    |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~\_   _______/~~~~~~~~~~~~~~\~~__~~__~~__~\_|~~~A:A~~~~~~~~\__A:A\   \~/~~~~~\ /     /~~~~~~~~~\__/~_/    |______/                     _____/         \___|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~~~~~\_/~~~~~~~~~~~~~~~~A:A~~~~~~~~~~~~~~~~~~~~~~~TYR~~~~~~~~~~~\Nap\ __|~~~~~~~|  A:A \_~~~A:A~~~~~~/_ *  /               *    ________/                   |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~~~~______|~~~~~~~~~~~~~~~~~WES~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~|*  |~~~~~~~~~~~\  Gre  \~~AEG~~~~~|  \__/    A:A Smy    _____/           _________________|  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~~~~~~~__/      \____~~~~~~______________~~~~~~~~~~___~~~~_~~__~~_______~~|__/~~~~~A:A~~~~~|   * _/~~~~~~~~~~~\____       ________/~~~~~\_    A:A  |                 |  A:A Aaa > Aaa  |  A:A Aaa > Aaa  |
|~~~~~~~_____/     A:A      \____/         /    \________/   \~~/~~~~~~~\_     /~~~~~~~~~~ION~~~~~|____/~__~~_____~/~~~~~~\_____/~~~~~~~~~~~~~~~~\   Syr  |  Current Turn:  |                 |                 |
|~~____/            Naf                   /      A:A Tun   *  |~~~~~~~~~~~\___/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/____/~~~~~~~~~~~~~~~~~~~A:A~EAS~~~~~~|       |  Fall 1901      |                 |                 |
|_/______________________________________/_____________________\______________________________________________|___________________________________|_______|_________________|_________________|_________________|
19 sea tiles + 56 land tiles (34 have supply centers) */
	
	tile NAO; //water
	tile NWG;
	tile BAR;
	tile NTH;
	tile GOB;
	tile IRE;
	tile HEL;
	tile SKA;
	tile BAL;
	tile MAO;
	tile GOL;
	tile ADR;
	tile BLA;
	tile WES;
	tile TYR;
	tile ION;
	tile AEG;
	tile EAS; //water
	tile Cly; //england
	tile Edi;
	tile Lvp;
	tile Yor;
	tile Wal;
	tile Lon; //england
	tile Nor; //norse
	tile Swe;
	tile Den; //norse
	tile Fin; //russia
	tile Stp;
	tile Liv;
	tile Mos;
	tile War;
	tile Ukr;
	tile Sev; //russia
	tile Arm; //turkey
	tile Syr;
	tile Smy;
	tile Ank;
	tile Con; //turkey
	tile Bul; //balkan
	tile Gre;
	tile Alb;
	tile Ser;
	tile Rum; //balkan
	tile Gal; //austria-hungary
	tile Boh;
	tile Tyr;
	tile Vie;
	tile Bud;
	tile Tri; //austria-hungary
	tile Ven; //italy
	tile Apu;
	tile Nap;
	tile Rom;
	tile Tus;
	tile Pie; //italy
	tile Tun; //mediteranean
	tile Naf;
	tile Por;
	tile Spa; //mediteranean
	tile Mar; //france
	tile Gas;
	tile Bur;
	tile Par;
	tile Bre;
	tile Pic; //france
	tile Bel; //low countries
	tile Hol; //low countries
	tile Ruh; //germany
	tile Mun;
	tile Sil;
	tile Pru;
	tile Ber;
	tile Kie; //germany

	board(){
		//sets up ocean and inland countries
		NAO.holdsArmy = false;
		NWG.holdsArmy = false;
		BAR.holdsArmy = false;
		NTH.holdsArmy = false;
		GOB.holdsArmy = false;
		IRE.holdsArmy = false;
		HEL.holdsArmy = false;
		SKA.holdsArmy = false;
		BAL.holdsArmy = false;
		MAO.holdsArmy = false;
		GOL.holdsArmy = false;
		ADR.holdsArmy = false;
		BLA.holdsArmy = false;
		WES.holdsArmy = false;
		TYR.holdsArmy = false;
		ION.holdsArmy = false;
		AEG.holdsArmy = false;
		EAS.holdsArmy = false;
		Mos.holdsFleet = false;
		War.holdsFleet = false;
		Ukr.holdsFleet = false;
		Ser.holdsFleet = false;
		Gal.holdsFleet = false;
		Boh.holdsFleet = false;
		Tyr.holdsFleet = false;
		Vie.holdsFleet = false;
		Bud.holdsFleet = false;
		Bur.holdsFleet = false;
		Par.holdsFleet = false;
		Ruh.holdsFleet = false;
		Mun.holdsFleet = false;
		Sil.holdsFleet = false;
	}
};

void printMap() 
{
	string line;
	ifstream myfile ("map.txt");
	while (getline(myfile,line))
	{
		cout << line << '\n';
	}
	myfile.close();
}

int main()
{
	string input;
	bool running = true;
	while(running)
	{
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
			cout << "closing diplomacy++" << endl;
		}
	}
}
