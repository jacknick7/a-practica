#include "hash.hh"

int miss=0;
int errors=0;

//C1 i C2 per la versió 2
int c1 = 11;
int c2 = 17;

int obtenirPassos(int valor){
  /*for(int factor=1; factor<valor; --factor){
    if(valor%factor==0){
      return factor;
    }
  }*/
  return 13;
}

int hashing(int valor, int capacitat){
  return valor%capacitat;
}

int hashing2(int valor, int capacitat){
  return valor%capacitat;
}

int obtenirClauV1(int valor, int passos, int capacitat){
  return (hashing(valor, capacitat)+passos)%capacitat;
}

int obtenirClauV2(int valor, int passos, int capacitat, int i1, int i2){
  return (hashing(valor, capacitat)+i1*passos+i2*(passos*passos))%capacitat;
}

int obtenirClauV3(int valor, int passos, int capacitat){
  return (hashing(valor, capacitat)+passos*hashing2(valor, capacitat))%capacitat;
}

int obtenirClau(int versio, int actual, int passos, int capacitat){
  if(versio==1){
    return obtenirClauV1(actual, passos, capacitat);
  }
  else if(versio==2){
    return obtenirClauV2(actual, passos, capacitat, c1, c2);
  }
  else if(versio==3){
    return obtenirClauV3(actual, passos, capacitat);
  }
  else{
    return obtenirClauV1(actual, passos, capacitat);
  }
}

void inserir(int versio, vector<int>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = obtenirClau(versio, actual, passos, capacitat);
  if(hash[clau]==-1){
    hash[clau] = actual;
  }
  else{
    int clau2 = (clau+1)%capacitat;
    bool trobat=false;
    while(!trobat&&(clau2!=clau)){
      if(hash[clau2]==-1){
	hash[clau2] = actual;
	trobat = true;
      }
      else{
	++miss;
      }
      clau2 = (clau2+1)%capacitat;
    }
    if(!trobat){
      cout << actual << endl;
      ++errors;
    }
  } 
}

void hashV(int versio, vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 1.25*mida;
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