#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{

    // game loop
    while (1) {
        int spaceX;
        int spaceY;
        cin >> spaceX >> spaceY; cin.ignore();
        vector<int> hMountains;
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain, from 9 to 0. Mountain heights are provided from left to right.
            cin >> mountainH; cin.ignore();
            hMountains.push_back(mountainH);
        }
        
        vector<int>::iterator maxH = max_element(hMountains.begin(),hMountains.end());
        
        if(hMountains[spaceX] == *maxH)
            cout << "FIRE" << endl;
        else
            cout << "HOLD" << endl;

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        //cout << "HOLD" << endl; // either:  FIRE (ship is firing its phase cannons) or HOLD (ship is not firing).
    }
}