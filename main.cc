#include <iostream>
#include <fstream>
#include <vector>

#include "binaryV1.hh"
#include "binaryV2.hh"
#include "hashV1.hh"
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
    
    cout << "Selecciona la tecnica a usar [binary | hash | bloom]: ";
    string type;
    cin >> type;
    cout << endl;
    cout << "Selecciona la versio a usar [1 | 2]: ";
    int version;
    cin >> version;
    cout << endl;
    if(type == "binary"){
	if (version == 1) binaryV1(dict, entr);
        else binaryV2(dict, entr);
    }
    else if (type == "hash"){
	if (version == 1) hashV1(1, dict, entr);
    }
    else if (type == "bloom"){
	if (version == 1) bloomV1(dict, entr);
    }
}  