#include <iostream>
#include <fstream>
#include <vector>

#include "binaryV1.hh"
#include "hashV1.hh"

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
    
    int type;
    cin >> type;
    if(type==1){
	binaryV1(dict, entr);
    }
    else if(type==2){
	hashV1(dict, entr);
    }
}  