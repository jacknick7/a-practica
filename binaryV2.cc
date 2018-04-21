#include "binaryV2.hh"
#include <ctime>

using namespace std;


class AVL {
    
private:
    
    struct node {
        int dada;
        node* esq;
        node* dre;
        int altura;
    };

    node* root;

    node* insert(int x, node* t) {
        if(t == NULL) {
            t = new node;
            t->dada = x;
            t->altura = 0;
            t->esq = t->dre = NULL;
        }
        else if(x < t->dada) {
            t->esq = insert(x, t->esq);
            if(altura(t->esq) - altura(t->dre) == 2) {
                if(x < t->esq->dada) t = singleRightRotate(t);
                else t = doubleRightRotate(t);
            }
        }
        else if(x > t->dada) {
            t->dre = insert(x, t->dre);
            if(altura(t->dre) - altura(t->esq) == 2) {
                if(x > t->dre->dada) t = singleLeftRotate(t);
                else t = doubleLeftRotate(t);
            }
        }
        t->altura = max(altura(t->esq), altura(t->dre))+1;
        return t;
    }

    node* singleRightRotate(node* &t) {
        node* u = t->esq;
        t->esq = u->dre;
        u->dre = t;
        t->altura = max(altura(t->esq), altura(t->dre))+1;
        u->altura = max(altura(u->esq), t->altura)+1;
        return u;
    }

    node* singleLeftRotate(node* &t) {
        node* u = t->dre;
        t->dre = u->esq;
        u->esq = t;
        t->altura = max(altura(t->esq), altura(t->dre))+1;
        u->altura = max(altura(t->dre), t->altura)+1 ;
        return u;
    }

    node* doubleLeftRotate(node* &t) {
        t->dre = singleRightRotate(t->dre);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t) {
        t->esq = singleLeftRotate(t->esq);
        return singleRightRotate(t);
    }

    int altura(node* t) {
        return (t == NULL ? -1 : t->altura);
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->esq);
        cout << t->dada << " ";
        inorder(t->dre);
    }

public:
    
    AVL() {
        root = NULL;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
    
};


void binaryV2(vector<int>& dict, vector<int>& entr){
    AVL dic;
    
    /* Ordenar diccionari */
    int comp1 = 0;
    int start1 = clock();
    for (auto elem : dict) dic.insert(elem);
    int stop1 = clock();
    cout << "Numero comparacions per ordenar el diccionari: " << comp1 << endl;
    cout << "Temps per ordenar el diccionari: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    dic.display();
    /* Cerca diccionari */
    /*
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
    */
}