#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    if(n==0)
    {
        cout << "0" << endl;
        return 0;
    }
    int best = INT_MAX;
    for(int i  = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        if((abs(temp) < abs(best)) || (abs(temp) == abs(best) && temp > 0))
        {
            best = temp;   
        }
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << best << endl;
}