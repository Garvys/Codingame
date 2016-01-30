#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int N;
    cin >> N; cin.ignore();
    std::vector<int> puissanceChevaux;
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        puissanceChevaux.push_back(Pi);
    }

    sort(puissanceChevaux.begin(),puissanceChevaux.end());

    std::vector<int> diffP;

    for (int i = 0; i < N - 1; ++i)
    {
    	diffP.push_back(puissanceChevaux[i+1] - puissanceChevaux[i]);
    }

    cout << *min_element(diffP.begin(),diffP.end()) << endl;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

}