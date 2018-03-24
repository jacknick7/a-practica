#include "hashV1.hh"

using namespace std;

int miss=0;

int obtenirClau(int valor, int capacitat){
  return valor % capacitat;
}

void inserir(vector<int>& hash, int capacitat, int actual){
  int clau = obtenirClau(actual, capacitat);
  if(hash[clau]==-1){
    hash[clau] = actual;
  }
  else{
    int i=((clau+1)%capacitat);
    bool trobat=false;
    while(!trobat&&(i!=clau)){
      if(hash[i]==-1){
	hash[i] = actual;
	trobat = true;
      }
      else{
	++miss;
      }
      i = (i+1)%capacitat;
    }
    if(!trobat){
      cout << actual << endl;
      cout << "ERROR! La taula està plena!" << endl;
    }
  } 
}

void hashV1(vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 2*mida;
  cout << "ENTRADA: " << mida << endl;
  cout << "CAPACITAT: " << capacitat << endl;
  vector<int> hash(capacitat, -1);
  for(int i=0; i<mida; ++i){
    inserir(hash, capacitat, dict[i]);
  }
  /*for(int i=0; i<capacitat; ++i){
    cout << hash[i] << endl;
  }*/
  cout << "SALTS: " << miss << endl;
}