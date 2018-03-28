#include "hashV1.hh"

using namespace std;

int missV1=0;
int errorsV1=0;

int obtenirClauV1(int valor, int capacitat){
  return valor % capacitat;
}

void inserirV1(vector<int>& hash, int capacitat, int actual){
  int clau = obtenirClauV1(actual, capacitat);
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
	++missV1;
      }
      i = (i+1)%capacitat;
    }
    if(!trobat){
      cout << actual << endl;
      ++errorsV1;
    }
  } 
}

void hashV1(vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 2*mida;
  cout << "OCUPACIÓ: " << 100*((float)mida/(float)capacitat) << "%" << endl;
  vector<int> hash(capacitat, -1);
  for(int i=0; i<mida; ++i){
    inserirV1(hash, capacitat, dict[i]);
  }
  cout << "SALTS: " << missV1 << endl;
  cout << "ERRORS: " << errorsV1 << endl;
}