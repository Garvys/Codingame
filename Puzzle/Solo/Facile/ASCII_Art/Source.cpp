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
	//Largeur d'une lettre en ASCII Art
	int L;
	cin >> L; cin.ignore();
	//Hauteur d'une lettre en ASCII Art
	int H;
	cin >> H; cin.ignore();
	//Chaine a ecrire en ASCII Art
	string T;
	getline(cin, T);

	//tableau qui va contenir le modele
	vector <string> tab_line_ascii;
	for (int i = 0; i < H; i++) {
		string ROW;
		getline(cin, ROW);
		tab_line_ascii.push_back(ROW);
	}

	string init("");
	for (int i = 0; i < (int)T.size() * L; i++)
	{
		init = init + "a";
	}

	vector <string> output(30, init);
	// parcoure chaque caractère de la chaine a ecrire
	for (int i = 0; i < (int)T.size(); i++)
	{
		if (tolower(T[i]) >= 'a' && tolower(T[i]) <= 'z')
		{
			int diff = tolower(T[i]) - 'a';
			for (int ligne = 0; ligne < H; ligne++)
			{
				for (int colonne = 0; colonne < L; colonne++)
				{
					output[ligne][L*i + colonne] = tab_line_ascii[ligne][L*diff + colonne];
				}

			}
		}
		else
		{
			for (int ligne = 0; ligne < H; ligne++)
			{
				for (int colonne = 0; colonne < L; colonne++)
				{
					output[ligne][L*i + colonne] = tab_line_ascii[ligne][L * 26 + colonne];
				}

			}
		}
	}

	//On affiche
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < (int)T.size() * L; j++)
		{
			cout << output[i][j];
		}
		cout << endl;
	}

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;
}