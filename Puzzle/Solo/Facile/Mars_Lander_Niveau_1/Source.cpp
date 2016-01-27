#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define ZONE_SECURITE 100

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Coord
{
    int X;
    int Y;
};

bool operator<(Coord c1, Coord c2)
{
    return (c1.X< c2.X);
}

void zone_atterissage(std::vector<Coord> &plateau, int &x1, int &x2, int &h)
{
    int y_prec = -1;
    x1 = 0;
    x2 = 0;
    for (int i = 0; i < (int)plateau.size(); ++i)
    {
        if (plateau[i].Y == y_prec)
        {
            x2 = plateau[i].X;
        }
        else if (plateau[i].Y != y_prec && (x2 - x1) >= 1000)
        {
            h = y_prec;
            break;
        }
        else
        {
            x1 = plateau[i].X;
            x2 = plateau[i].X;
        }

        y_prec = plateau[i].Y;
    }
}

int main()
{
    std::vector<Coord> plateau;
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        Coord temp;
        temp.X = landX;
        temp.Y = landY;
        plateau.push_back(temp);
    }
    sort(plateau.begin(),plateau.end());

    //Il faut trouver où se situe le plateau
    int xmin, xmax, h_att;
    zone_atterissage(plateau,xmin,xmax, h_att);

        int xmin_safe = xmin + ZONE_SECURITE;
        int xmax_safe = xmax - ZONE_SECURITE;

    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

        int rotate_wanted;
        int power_wanted;

        //Si on est au dessus de la zone d'atterissage
        if (xmin_safe < X && X < xmax_safe)
        {
            rotate_wanted = 0;
            if (vSpeed <= -40)
            {
                power_wanted = 4;
            }
            else
            {
                power_wanted = 0;
            }
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << rotate_wanted << " " << power_wanted << endl; // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
    }
}