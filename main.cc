#include <iostream>
#include <fstream>
#include <vector>

#include "binaryV1.hh"
#include "hashing.hh"

using namespace std;

void showError(){
    cout << "Error, no available choice for entered input." << endl;
}

int main() {
    ifstream File;
    File.open("exemples/exemple_02.dict");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.dict." << endl;
    int n;
    File >> n;
    vector<int> dict(n), entr(2*n);
    for (int i = 0; i < n; ++i) File >> dict[i];
    File.close();
    File.open("exemples/exemple_02.entr");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.entr." << endl;
    for (int i = 0; i < 2*n; ++i) File >> entr[i];
    File.close();
    
    char type;
    cout << "[B]inary or [H]ash?" << endl;
    cin >> type;
    if((type=='B')||(type=='b')){
	binaryV1(dict, entr);
    }
    else if((type=='H')||(type=='h')){
	cout << "Version [1] or [2]?" << endl;
	cin >> type;
	if((type=='1')||(type=='2')){
	    hashing((type-48), dict, entr);
	}
	else{
	    showError();
	}
    }
    else{
	showError();
    }
}  