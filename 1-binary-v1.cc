#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream File;
    File.open("exemples/exemple_01.dict");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.dict" << endl;
    int n;
    File >> n;
    vector<int> dicData(n), text(2*n);
    for (int i = 0; i < n; ++i) File >> dicData[i];
    for (int i = 0; i < n; ++i) cout << dicData[i] << endl;
    cout << dicData[0] << ' ' << dicData[n-1] << endl;
    File.close();
    File.open("exemples/exemple_01.entr");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'exemple_01.entr" << endl;
    for (int i = 0; i < 2*n; ++i) File >> text[i];
    for (int i = 0; i < 2*n; ++i) cout << text[i] << endl;
    cout << text[0] << ' ' << text[2*n-1] << endl;
    File.close();
}
