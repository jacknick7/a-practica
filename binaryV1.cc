#include "binaryV1.hh"
#include <ctime>


int sear;

/* Pre: --
 * Post: la funcio ordena un segment del vector i acumula el numero
 *       de comparacions
 */
void merge(int* pdic, int fst, int m, int lst) {
    int ne = m - fst + 1;
    int nd = lst - m;
    int me[ne + 1];
    int md[nd + 1];
    for(int i = 0; i < ne; i++) me[i] = pdic[fst + i];
    for(int j = 0; j< nd; j++) md[j] = pdic[m + 1 + j];
    int i, j, k;
    i = j = k = 0;
    while (j != ne and k != nd) {
        if (me[j] < md[k]) {
            pdic[fst + i] = me[j];
            ++j;
        }
        else {
            pdic[fst + i] = md[k];
            ++k;
        }
        ++i;
        ++sear;
    }
    while (j != ne) {
        pdic[fst + i] = me[j];
        ++j;
        ++i;
    }
    while (k != nd) {
        pdic[fst + i] = md[k];
        ++k;
        ++i;
    }
}


/* Pre: --
 * Post: la funcio retorna el vector original ordenat usant merge sort (cost nlogn)
 *       i també el numero total de comparacions de claus 
 */
void mergeSort(int* pdic, int fst, int lst) {
    if(fst < lst) {
        int m = (fst + lst) / 2;
        mergeSort(pdic, fst, m);
        mergeSort(pdic, m + 1, lst);
        merge(pdic, fst, m, lst);
    }
}

/* Pre: --
 * Post: la funcio retorna l'index del diccionari on es troba l'element, si no 
 *       es troba en el diccionari retorna -1 (cost lgn), a mes conta el nombre de
 *       comparacions de claus
 */
int binarySearch(int l, int r, int* dict, int elem, int& sear1) {
    if (l <= r) {
        int m = (l + r)/2;
        if (dict[m] == elem) {
            sear1 += 1;
            return m;
        }
        else if (dict[m] < elem) {
            sear1 += 2;
            return binarySearch((m+1), r, dict, elem, sear1);
        }
        else {
            sear1 += 2;
            ++sear1;
            return binarySearch(l, (m-1), dict, elem, sear1);
        }
    }
    return -1;
}

void binaryV1(vector<int>& dict, vector<int>& entr){
    int n = dict.size();
    int* dic = new int[n];
    for (int i = 0; i < n; ++i) dic[i] = dict[i];
    
    /* Ordenar diccionari */
    sear = 0;
    int start1 = clock();
    mergeSort(dic, 0, n - 1);
    int stop1 = clock();
    cout << "Numero comparacions per ordenar el diccionari: " << sear << endl;
    cout << "Temps per ordenar el diccionari: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    /* Cerca diccionari */
    int comp2 = 0;
    int start2 = clock();
    for (auto elem : entr) {
	int comp2i = 0;
        int pos = binarySearch(0, n - 1, dic, elem, comp2i);
        comp2 += comp2i;
    }
    int stop2 = clock();
    cout << "Numero comparacions total de les cerques: " << comp2 << endl;
    cout << "Temps per fer totes les cerques: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
}