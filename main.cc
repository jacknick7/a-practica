#include <iostream>
#include <fstream>
#include <vector>

#include "binaryV1.hh"
#include "binaryV2.hh"
#include "hash.hh"
#include "bloomV1.hh"

using namespace std;

int main() {
    ifstream File;
    File.open("exemples/exemple_01.dict");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.dict." << endl;
    int n;
    File >> n;
    vector<int> dict(n), entr(2*n);
    for (int i = 0; i < n; ++i) File >> dict[i];
    File.close();
    File.open("exemples/exemple_01.entr");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.entr." << endl;
    for (int i = 0; i < 2*n; ++i) File >> entr[i];
    File.close();
    
    cout << "Selecciona la tècnica a utilitzar (binary, hash o bloom)." << endl;
    string type;
    cin >> type;
    if(type == "binary"){
	cout << "Selecciona la versió a utilitzar (1 o 2)." << endl;
	int version;
	cin >> version;
	if (version == 1) binaryV1(dict, entr);
        else binaryV2(dict, entr);
    }
    else if (type == "hash"){
	cout << "Selecciona la versió a utilitzar (1, 2 o 3)." << endl;
	int version;
	cin >> version;
	hashV(version, dict, entr);
    }
    else if (type == "bloom"){
	bloomV1(dict, entr);
    }
}  