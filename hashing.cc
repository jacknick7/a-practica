#include "hash.hh"

int miss=0;
int errors=0;

int obtenirClauV1(int valor, int capacitat){
  return valor % capacitat;
}

int obtenirClauV2(int valor, int capacitat){
  return valor % capacitat;
}

void inserir(int versio, vector<int>& hash, int capacitat, int actual){
  int clau;
  if(versio==1){
    clau = obtenirClauV1(actual, capacitat);
  }
  else if(versio==2){
    clau = obtenirClauV2(actual, capacitat);
  }
  else{
    clau = obtenirClauV1(actual, capacitat);
  }
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
      ++errors;
    }
  } 
}

void hashing(int versio, vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 2*mida;
  cout << "OCUPACIÓ: " << 100*((float)mida/(float)capacitat) << "%" << endl;
  vector<int> hash(capacitat, -1);
  for(int i=0; i<mida; ++i){
    inserir(versio, hash, capacitat, dict[i]);
  }
  cout << "SALTS: " << miss << endl;
  cout << "ERRORS: " << errors << endl;
}