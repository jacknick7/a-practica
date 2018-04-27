#include "bloomV1.hh"
#include <ctime>

vector<bool> bloomTab;

int hashF1(int x) {
    return (3 * x + 3 % 6) % bloomTab.size(); 
}

int hashF2(int x) {
    return (2 * x + 9 % 2) % bloomTab.size();
}

int hashF3(int x) {
    return (3 * x + 7 % 8) % bloomTab.size();
}

int hashF4(int x) {
    return (2 * x + 3 % 5) % bloomTab.size();
}

void makeTable(vector<int>& dict) {
    bloomTab = vector<bool> (dict.size() * 16, false);
    for (auto elem : dict) {
        bloomTab[hashF1(elem)] = true;
        bloomTab[hashF2(elem)] = true;
        bloomTab[hashF3(elem)] = true;
        bloomTab[hashF4(elem)] = true;
    }
}

bool maybe(int x) {
    return bloomTab[hashF1(x)] and bloomTab[hashF2(x)]
           and bloomTab[hashF3(x)] and bloomTab[hashF4(x)];
}

void bloomV1(vector<int>& dict, vector<int>& entr){
    
    /* Crear la taula de bloom */
    int start1 = clock();
    makeTable(dict);
    int stop1 = clock();
    cout << "Temps per generar la taula de bloom: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    /* Cerca al conjunt */
    int start2 = clock();
    for (auto elem : entr) {
        if (maybe(elem)) cout << elem << endl;
    }
    int stop2 = clock();
    cout << "Temps per fer totes les cerques: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
}