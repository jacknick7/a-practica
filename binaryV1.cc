#include "binaryV1.hh"

using namespace std;

vector<int> dic, text;

/* Pre: --
 * Post: la funcio retorna el vector original ordenat usant merge sort (cost nlogn) 
 */
vector<int> mergeSort(vector<int> pdic) {
    int n = pdic.size();
    if (n > 1) {
        int m = n/2;
        vector<int> dicf(m);
        vector<int> dicl(n-m);
        for (int i = 0; i <= m; ++i) dicf[i] = pdic[i];
        for (int i = 0; i < dicl.size(); ++i) dicl[i] = pdic[i+m];
        vector<int> me = mergeSort(dicf);
        vector<int> md = mergeSort(dicl);
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


void binaryV1(vector<int>& dict, vector<int>& entr){
    dic = mergeSort(dict);
    text = entr;
}