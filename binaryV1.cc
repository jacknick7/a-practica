#include "binaryV1.hh"
#include <ctime>


vector<int> dic, text;

/* Pre: --
 * Post: la funcio retorna el vector original ordenat usant merge sort (cost nlogn)
 *       i també el numero total de comparacions de claus 
 */
vector<int> mergeSort(vector<int>& pdic, int& sear) {
    int n = pdic.size();
    if (n > 1) {
        int m = n/2;
        vector<int> dicf(m);
        vector<int> dicl(n-m);
        for (int i = 0; i <= m; ++i) dicf[i] = pdic[i];
        for (int i = 0; i < dicl.size(); ++i) dicl[i] = pdic[i+m];
        int searl, searr;
        searl = searr = 0;
        vector<int> me = mergeSort(dicf, searl);
        vector<int> md = mergeSort(dicl, searr);
        sear = sear + searl + searr;
        int i, j, k;
        i = j = k = 0;
        while (j != me.size() and k != md.size()) {
            if (me[j] < md[k]) {
                pdic[i] = me[j];
                ++j;
            }
            else {
                pdic[i] = md[k];
                ++k;
            }
            ++i;
            ++sear;
        }
        while (j != me.size()) {
            pdic[i] = me[j];
            ++j;
            ++i;
        }
        while (k != md.size()) {
            pdic[i] = md[k];
            ++k;
            ++i;
        }
    }
    return pdic;
}

/* Pre: --
 * Post: la funcio retorna l'index del diccionari on es troba l'element, si no 
 *       es troba en el diccionari retorna -1 (cost lgn), a mes conta el nombre de
 *       comparacions de claus
 */
int binarySearch(int l, int r, const vector<int>& dict, int elem, int& sear) {
    if (l <= r) {
        int m = (l + r)/2;
        if (dict[m] == elem) {
            sear += 1;
            return m;
        }
        else if (dict[m] < elem) {
            sear += 2;
            return binarySearch((m+1), r, dict, elem, sear);
        }
        else {
            sear += 2;
            return binarySearch(l, (m-1), dict, elem, sear);;
        }
    }
    return -1;
}


void binaryV1(vector<int>& dict, vector<int>& entr){
    dic = dict;
    text = entr;
    
    /* Ordenar diccionari */
    int comp1 = 0;
    int start1 = clock();
    dic = mergeSort(dic, comp1);
    int stop1 = clock();
    cout << "Numero comparacions per ordenar el diccionari: " << comp1 << endl;
    cout << "Temps per ordenar el diccionari: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    /* Cerca diccionari */
    int comp2 = 0;
    int start2 = clock();
    for (int i = 0; i < text.size(); ++i) {
        int comp2i = 0;
        int n = binarySearch(0, dic.size() - 1, dic, text[i], comp2i);
        comp2 += comp2i;
    }
    int stop2 = clock();
    cout << "Numero comparacions total de les cerques: " << comp2 << endl;
    cout << "Temps per fer totes les cerques: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
}