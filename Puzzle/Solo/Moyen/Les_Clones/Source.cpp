#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
string returnDirection(int posClone, int posVoulue)
{
	if (posClone < posVoulue)
	{
		return "RIGHT";
	}
	else if (posClone > posVoulue)
	{
		return "LEFT";
	}
	else
	{
		return "OK";
	}
}

int main()
{
	int nbFloors; // number of floors
	int width; // width of the area
	int nbRounds; // maximum number of rounds
	int exitFloor; // floor on which the exit is found
	int exitPos; // position of the exit on its floor
	int nbTotalClones; // number of generated clones
	int nbAdditionalElevators; // ignore (always zero)
	int nbElevators; // number of elevators
	map<int,int> tabElevator;
	cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
	for (int i = 0; i < nbElevators; i++) {
		int elevatorFloor; // floor on which this elevator is found
		int elevatorPos; // position of the elevator on its floor
		cin >> elevatorFloor >> elevatorPos; cin.ignore();
		tabElevator[elevatorFloor] = elevatorPos;
	}

	// game loop
	while (1) {
		int cloneFloor; // floor of the leading clone
		int clonePos; // position of the leading clone on its floor
		string direction; // direction of the leading clone: LEFT or RIGHT
		cin >> cloneFloor >> clonePos >> direction; cin.ignore();

		if (cloneFloor == exitFloor) //On est au bon étage
		{
			//On va en direction de l'aspirateur qui est sur notre étage
			if (direction == returnDirection(clonePos, exitPos) || "OK" == returnDirection(clonePos, exitPos))
			{
				cout << "WAIT" << endl;
			}
			else
			{
				//Il faut bloquer
				cout << "BLOCK" << endl;
			}

		}
		else //Il faut monter
		{
			//On va en direction de l'ascenseur qui est sur notre
			if (direction == returnDirection(clonePos, tabElevator[cloneFloor]) || "OK" == returnDirection(clonePos, tabElevator[cloneFloor]))
			{
				cout << "WAIT" << endl;
			}
			else
			{
				//Il faut bloquer
				cout << "BLOCK" << endl;
			}
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		//cout << "WAIT" << endl; // action: WAIT or BLOCK
	}
}