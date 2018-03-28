#include "hashing.hh"

int miss=0;
int errors=0;

//C1 i C2 per la versió 2
int c1 = 11;
int c2 = 17;

int obtenirPassos(int valor){
  for(int factor=1; factor<valor; --factor){
    if(valor%factor==0){
      return factor;
    }
  }
  return 0;
}

int obtenirClauV1(int valor, int passos, int capacitat){
  return (valor+passos)%capacitat;
}

int obtenirClauV2(int valor, int passos, int capacitat, int i1, int i2){
  return (valor+i1*passos+i2*(passos*passos))%capacitat;
}

int obtenirClau(int versio, int actual, int passos, int capacitat, int i){
  if(versio==1){
    return (obtenirClauV1(actual, passos, capacitat)+i)%capacitat;
  }
  else if(versio==2){
    return (obtenirClauV2(actual, passos, capacitat, c1, c2)+i)%capacitat;
  }
  else{
    return (obtenirClauV1(actual, passos, capacitat)+i)%capacitat;
  }
}

void inserir(int versio, vector<int>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = obtenirClau(versio, actual, passos, capacitat, 0);
  if(hash[clau]==-1){
    hash[clau] = actual;
  }
  else{
    int i=1;
    int clau2 = obtenirClau(versio, actual, passos, capacitat, i);
    bool trobat=false;
    while(!trobat&&(clau2!=clau)){
      if(hash[clau2]==-1){
	hash[clau2] = actual;
	trobat = true;
      }
      else{
	++miss;
      }
      ++i;
      clau2 = obtenirClau(versio, actual, passos, capacitat, i);
    }
    if(!trobat){
      cout << actual << endl;
      ++errors;
    }
  } 
}

void hashing(int versio, vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 1.1*mida;
  int passos = obtenirPassos(capacitat);
  cout << "Ocupació: " << 100*((float)mida/(float)capacitat) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  vector<int> hash(capacitat, -1);
  for(int i=0; i<mida; ++i){
    inserir(versio, hash, passos, capacitat, dict[i]);
  }
  cout << "Salts: " << miss << endl;
  cout << "Errors: " << errors << endl;
}