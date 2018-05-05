#include "binaryV2.hh"
#include <ctime>


int comp1, comp1i, comp2, comp2i;

/* Class AVL representa un arbre auto-balancejat AVL ideal
 * per fer cerques binaries (altura del arbre serà lgn)
 */
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
        else if (x == t->dada) {
            return t;
        }
        else if(x < t->dada) {
            comp1i += 2;
            t->esq = insert(x, t->esq);
            if(altura(t->esq) - altura(t->dre) == 2) {
                comp1i += 1;
                if(x < t->esq->dada) t = singleRightRotate(t);
                else t = doubleRightRotate(t);
            }
        }
        else {
            comp1i += 2;
            t->dre = insert(x, t->dre);
            if(altura(t->dre) - altura(t->esq) == 2) {
                comp1i += 1;
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
        t->altura = max(altura(t->esq), altura(t->dre)) + 1;
        u->altura = max(altura(t->dre), t->altura) + 1;
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
        if (t == NULL) return -1;
        return t->altura;
    }
    
    bool findInRoot(int x, node* t) {
        if (t == NULL){
	    return false;
	}
        else if (x == t->dada) {
            comp2i += 1;
            return true;
        }
        else if (x < t->dada) {
            comp2i += 2;
            findInRoot(x, t->esq);
        }
        else {
	    comp2i += 2;
	    findInRoot(x, t->dre);
	}
        return false;
    }

    void inorder(node* t)
    {
        if(t == NULL) return;
        inorder(t->esq);
        cout << t->dada << " ";
        inorder(t->dre);
    }

public:
    
    /* Pre: --
     * Post: es crea un arbre AVL buit
     */
    AVL() {
        root = NULL;
    }

    /* Pre: --
     * Post: si x no era en l'arbre, s'afegeix, si no l'arbre no canvia
     */
    void insert(int x) {
        comp1i = 0;
        root = insert(x, root);
    }
    
    /* Pre: --
     * Post: si x era en l'arbre, retorna cert, si no retorna fals
     */
    bool find(int x) {
        comp2i = 0;
        return findInRoot(x, root);
    }

    /* Pre: --
     * Post: s'imprimeix l'arbre en inordre pel canal estandard
     */
    void show() {
        inorder(root);
        cout << endl;
    }
    
};


void binaryV2(vector<int>& dict, vector<int>& entr){
    AVL dic;
    
    /* Ordenar diccionari */
    comp1 = 0;
    int start1 = clock();
    for (auto elem : dict) {
        dic.insert(elem);
        comp1 += comp1i;
    }
    int stop1 = clock();
    cout << "Numero comparacions per ordenar el diccionari: " << comp1 << endl;
    cout << "Temps per ordenar el diccionari: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    /* Cerca diccionari */
    int comp2 = 0;
    int start2 = clock();
    for (auto elem : entr) {
        dic.find(elem);
        comp2 += comp2i;
    }
    int stop2 = clock();
    cout << "Numero comparacions total de les cerques: " << comp2 << endl;
    cout << "Temps per fer totes les cerques: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
}