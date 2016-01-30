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
string fileToExt(string input)
{
	string ext;
	string::iterator it;
	for (it = input.end(); it != input.begin() ; it--)
	{
		if (*it == '.')
		{
			break;
		}
	}
	ext.insert(ext.begin(), it + 1, input.end());
	for (int i = 0; i < (int) ext.size(); i++)
	{
		ext[i] = tolower(ext[i]);
	}
	return ext;
}

int main()
{
	map<string, string> fileToMime;
	int N; // Number of elements which make up the association table.
	cin >> N; cin.ignore();
	int Q; // Number Q of file names to be analyzed.
	cin >> Q; cin.ignore();
	for (int i = 0; i < N; i++) {
		string EXT; // file extension
		string MT; // MIME type.
		cin >> EXT >> MT; cin.ignore();
		for (int i = 0; i < (int)EXT.size(); i++)
		{
			EXT[i] = tolower(EXT[i]);
		}
		fileToMime[EXT] = MT;
	}
	for (int i = 0; i < Q; i++) {
		string FNAME; // One file name per line.
		getline(cin, FNAME);
		if (fileToMime.count(fileToExt(FNAME)) > 0)
		{
			cout << fileToMime[fileToExt(FNAME)] << endl;
		}
		else
		{
			cout << "UNKNOWN" << endl;
		}
		
	}

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	//cout << "UNKNOWN" << endl; // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
}