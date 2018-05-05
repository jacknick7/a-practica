#include "hashV1.hh"
#include "hashV2.hh"

int missV2=0;
int errorsV2=0;

vector<int> errors2TV2(0);

//C1 i C2 per la versió 2
int c1V2 = 11;
int c2V2 = 17;

void inserir1V2(vector<list<int>>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = hashing(actual, capacitat);
  hash[clau].insert(hash[clau].begin(), actual);
}

int cercar1V2(vector<list<int>>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = hashing(actual, capacitat);
  list<int>::iterator it = hash[clau].begin();
  int posicio=0;
  while(it!=hash[clau].end()){
    if(*it==actual){
      hash[clau].splice(hash[clau].begin(), hash[clau], it);
      return posicio;
    }
    ++missV2;
    ++posicio;
    ++it;
  }
  return -1;
}

void inserir2V2(vector<vector<int>>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = hashing(actual, capacitat);
  hash[clau].push_back(actual);
}

int cercar2V2(vector<vector<int>>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = hashing(actual, capacitat);
  int posicio=0;
  while(posicio<hash[clau].size()){
    if(hash[clau][posicio]==actual){
      return posicio;
    }
    ++missV2;
    ++posicio;
  }
  return -1;
}

void imprimir1V2(int posicio, list<int> valors){
  --posicio;
  cout << "[" << posicio << "]";
  list<int>::iterator it = valors.begin();
  while(it!=valors.end()){
    cout << " " << *it;
    ++it;
  }
}

void imprimir2V2(int posicio, vector<int> valors){
  --posicio;
  cout << "[" << posicio << "]";
  for(int i=0; i<valors.size(); ++i){
    cout << " " << valors[i];
  }
}

void hashL(vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 1.5*mida;
  int passos = obtenirPassos(capacitat);
  vector<list<int>> hash(capacitat, list<int>(0));
  int start1 = clock();
  for(int i=0; i<mida; ++i){
    inserir1V2(hash, passos, capacitat, dict[i]);
  }
  int stop1 = clock();
  
  int mida2 = entr.size();
  int trobats = 0;
  int clockSi = 0, clockNo = 0;
  int start2 = clock();
  for(int i=0; i<mida2; ++i){
    int start3 = clock();
    int clau = cercar1V2(hash, passos, capacitat, entr[i]);
    int stop3 = clock();
    if(clau>=0){
      ++trobats;
      clockSi += (stop3-start3);
    }
    else{
      clockNo += (stop3-start3);
    }
  }
  int stop2 = clock();
  int notrobats = mida2-trobats;
  
  cout << "#### INFORMACIÓ ####" << endl;
  cout << "Cerca: HASH" << endl;
  cout << "Tècnica: CHAIN" << endl;
  cout << "Funció: MOVE" << endl;
  cout << "Ocupació: " << 100*((float)(mida-errorsV2)/(float)capacitat) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "#### INSERCIÓ ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Salts: " << missV2 << endl;
  cout << "Errors: " << errorsV2 << endl;
  cout << "Temps: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### CERCA ####" << endl;
  cout << "Mida: " << mida2 << endl;
  cout << "Temps total: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps trobats: " << clockSi/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps no trobats: " << clockNo/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### RESULTAT ####" << endl;
  cout << "Trobats: " << trobats << endl;
  cout << "No trobats: " << notrobats << endl;
  cout << "#### TAULA RESULTANT ####" << endl;
  for(int i=1; i<=capacitat; ++i){
    imprimir1V2(i, hash[(i-1)]);
    cout << endl;
  }
}

void hashA(vector<int>& dict, vector<int>& entr){
    int mida = dict.size();
  int capacitat = 1.5*mida;
  int passos = obtenirPassos(capacitat);
  vector<vector<int>> hash(capacitat, vector<int>(0));
  int start1 = clock();
  for(int i=0; i<mida; ++i){
    inserir2V2(hash, passos, capacitat, dict[i]);
  }
  int stop1 = clock();
  
  int mida2 = entr.size();
  int trobats = 0;
  int clockSi = 0, clockNo = 0;
  int start2 = clock();
  for(int i=0; i<mida2; ++i){
    int start3 = clock();
    int clau = cercar2V2(hash, passos, capacitat, entr[i]);
    int stop3 = clock();
    if(clau>=0){
      ++trobats;
      clockSi += (stop3-start3);
    }
    else{
      clockNo += (stop3-start3);
    }
  }
  int stop2 = clock();
  int notrobats = mida2-trobats;
  
  cout << "#### INFORMACIÓ ####" << endl;
  cout << "Cerca: HASH" << endl;
  cout << "Tècnica: CHAIN" << endl;
  cout << "Funció: EXACT" << endl;
  cout << "Ocupació: " << 100*((float)(mida-errorsV2)/(float)capacitat) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "#### INSERCIÓ ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Salts: " << missV2 << endl;
  cout << "Errors: " << errorsV2 << endl;
  cout << "Temps: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### CERCA ####" << endl;
  cout << "Mida: " << mida2 << endl;
  cout << "Temps total: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps trobats: " << clockSi/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps no trobats: " << clockNo/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### RESULTAT ####" << endl;
  cout << "Trobats: " << trobats << endl;
  cout << "No trobats: " << notrobats << endl;
  cout << "#### TAULA RESULTANT ####" << endl;
  for(int i=1; i<=capacitat; ++i){
    imprimir2V2(i, hash[(i-1)]);
    cout << endl;
  }
}

void hashV2(int versio, vector<int>& dict, vector<int>& entr){
  if(versio==1){
    hashL(dict, entr);
  }
  else if(versio==2){
    hashA(dict, entr);
  }
  
}