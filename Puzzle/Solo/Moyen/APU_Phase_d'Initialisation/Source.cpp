#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

int main()
{
    int none = -1;
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();

    //Plateau du jeu. On accede à une case par la commande plateau[x][y]
    bool **plateau =(bool**) malloc(width * sizeof(bool*));
    for (int i = 0; i < width; ++i)
    {
        plateau[i] =(bool*) malloc(height * sizeof(bool));
        for (int j = 0; j < height; ++j)
        {
            //Initialement, tout les noeuds sont a false ce qui signifie que le noeud n'existe pas
            plateau[i][j] = false;
        }
    }

    //On récupère les données
    for (int j = 0; j < height; j++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        //On a récupéré une ligne de longueur width
        for (int i = 0; i < width; ++i)
        {
            if (line[i] == '0')
            {
                plateau[i][j] = true;
            }
        }
        cerr << line << endl;
    }

    cerr << width << height;

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            if (plateau[i][j])
            {
                 cout << i << " " << j << " ";

                int sommeX = 1;
                bool printDroite = false;
                //Voisin de droite
                while((i + sommeX) < width && !printDroite)
                {
                    if (plateau[i + sommeX][j])
                    {
                        printDroite = true;
                        cout << (i + sommeX) << " " << j << " ";
                    }
                    sommeX++;
                }
                if (!printDroite)
                {
                    cout << "-1 -1 ";
                }

                int sommeY = 1;
                bool printBas = false;
                //Voisin du dessous
                while((j + sommeY) < height && !printBas)
                {
                    if (plateau[i][j + sommeY])
                    {
                        printBas = true;
                        cout << i << " " << (j + sommeY) << " ";
                    }
                    sommeY++;
                }
                if (!printBas)
                {
                    cout << "-1 -1 ";
                }

                cout << endl;
            }
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    //cout << "0 0 1 0 0 1" << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor
}