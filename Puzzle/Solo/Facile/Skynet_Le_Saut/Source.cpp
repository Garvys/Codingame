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
    int road; // the length of the road before the gap.
    cin >> road; cin.ignore();
    int gap; // the length of the gap.
    cin >> gap; cin.ignore();
    int platform; // the length of the landing platform.
    cin >> platform; cin.ignore();
    
    int speedWanted = gap + 1;
    int resauter = 0;
    int c = 0;
    
    // game loop
    while (1) {
        int speed; // the motorbike's speed.
        cin >> speed; cin.ignore();
        int coordX; // the position on the road of the motorbike.
        cin >> coordX; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if(c!=0)
            road -= speed;
        c+=1;
        if (speed > 0)
        {
            if (speed > speedWanted && resauter == 0)
                cout << "SLOW" << endl;
            else if (speed < speedWanted && resauter == 0)
                cout << "SPEED" << endl;
            else
            {
                if (road <= 1 || resauter == 1)
                {
                    cout << "JUMP" << endl;
                    if (resauter ==1)
                        resauter = 0;
                    if ((road - speed) < 0)
                        speedWanted = 0;
                    else
                        resauter = 1;
                }
                else
                    cout << "WAIT" << endl;
            }
        }
        else
            cout << "SPEED" << endl;

       // cout << "SPEED" << endl; // A single line containing one of 4 keywords: SPEED, SLOW, JUMP, WAIT.
    }
}

    