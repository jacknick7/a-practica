#include "hashV2.hh"

using namespace std;

int missV2=0;
int errorsV2=0;

int obtenirClauV2(int valor, int capacitat){
  return valor % capacitat;
}

void inserirV2(vector<int>& hash, int capacitat, int actual){
  int clau = obtenirClauV2(actual, capacitat);
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
	++missV2;
      }
      i = (i+1)%capacitat;
    }
    if(!trobat){
      cout << actual << endl;
      ++errorsV2;
    }
  } 
}

void hashV2(vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 2*mida;
  cout << "OCUPACIÓ: " << 100*((float)mida/(float)capacitat) << "%" << endl;
  vector<int> hash(capacitat, -1);
  for(int i=0; i<mida; ++i){
    inserirV2(hash, capacitat, dict[i]);
  }
  cout << "SALTS: " << missV2 << endl;
  cout << "ERRORS: " << errorsV2 << endl;
}