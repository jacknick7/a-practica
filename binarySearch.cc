#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main() {
    ifstream File;
    File.open("arxiu1.txt");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'arxiu1" << endl;
    int n;
    File >> n;
    vector<int> dicData(n), text(2*n);
    for (int i = 0; i < n; ++i) File >> dicData[i];
    for (int i = 0; i < n; ++i) cout << dicData[i] << endl;
    cout << dicData[0] << ' ' << dicData[n-1] << endl;
    File.close();
    File.open("arxiu2.txt");
    if (not File.is_open())
        cout << "No s'ha pogut llegir l'arxiu2" << endl;
    for (int i = 0; i < 2*n; ++i) File >> text[i];
    for (int i = 0; i < 2*n; ++i) cout << text[i] << endl;
    cout << text[0] << ' ' << text[2*n-1] << endl;
    File.close();
}
