#include "bloomV1.hh"
#include <ctime>

// Els bools en C++ ocupen 1 byte per tenir @ optima,
// en futures versions usar setbit
vector<bool> bloomTab;
int desp;

int hashF1(int x) {
    return x % desp; 
}

int hashF2(int x) {
    return ((x + 1) % (bloomTab.size() - desp)) + desp;
}

int hashF3(int x) {
    return (((x % 37) + x) % (bloomTab.size() - 2 * desp)) + 2 * desp;
}

int hashF4(int x) {
    return ((x * 7) % (bloomTab.size() - 3 * desp)) + 3 * desp;
}

void makeTable(vector<int>& dict) {
    bloomTab = vector<bool> (dict.size() * 16, false);
    desp = 4 * dict.size();
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
    vector<int> posibles;
    int start2 = clock();
    for (auto elem : entr) {
        if (maybe(elem)) posibles.push_back(elem);
    }
    int stop2 = clock();
    int falsPositiu = 0;
    for (auto elem : posibles) {
        int i = 0;
        bool trobat = false;
        while (i < dict.size() and not trobat) {
            if (elem == dict[i]) trobat = true;
            ++i;
        }
        if (not trobat) ++falsPositiu;
    }
    cout << "Temps per fer totes les cerques: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Numero de fals positius: " << falsPositiu << endl;
    cout << "Numero total de positius: " << posibles.size() << endl;
}