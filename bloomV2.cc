#include "bloomV2.hh"
#include <ctime>

// Els bools en C++ ocupen 1 byte per tenir @ optima,
// en futures versions usar setbit
vector<bool> bloomTabV2;
int despV2;

int hashF1V2(int x) {
    return x % despV2; 
}

int hashF2V2(int x) {
    return ((x + 1) % (bloomTabV2.size() - despV2)) + despV2;
}

int hashF3V2(int x) {
    return (((x % 37) + x) % (bloomTabV2.size() - 2 * despV2)) + 2 * despV2;
}

int hashF4V2(int x) {
    return ((x * 7) % (bloomTabV2.size() - 3 * despV2)) + 3 * despV2;
}

void makeTableV2(vector<int>& dict) {
    bloomTabV2 = vector<bool> (dict.size() * 28, false);
    despV2 = 7 * dict.size();
    for (auto elem : dict) {
        bloomTabV2[hashF1V2(elem)] = true;
        bloomTabV2[hashF2V2(elem)] = true;
        bloomTabV2[hashF3V2(elem)] = true;
        bloomTabV2[hashF4V2(elem)] = true;
    }
}

bool maybeV2(int x) {
    return bloomTabV2[hashF1V2(x)] and bloomTabV2[hashF2V2(x)]
           and bloomTabV2[hashF3V2(x)] and bloomTabV2[hashF4V2(x)];
}

void bloomV2(vector<int>& dict, vector<int>& entr){
    
    /* Crear la taula de bloom */
    int start1 = clock();
    makeTableV2(dict);
    int stop1 = clock();
    cout << "Temps per generar la taula de bloom: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    /* Cerca al conjunt */
    vector<int> posibles;
    int start2 = clock();
    for (auto elem : entr) {
        if (maybeV2(elem)) posibles.push_back(elem);
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
