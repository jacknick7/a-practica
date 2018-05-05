#include "hashV1.hh"

int missV1=0;
int errorsV1=0;

int miss2V1=0;
int errors2V1=0;

vector<int> errors2TV1(0);

//c1 i c2 per la versió 2
int c1V1 = 11;
int c2V1 = 17;

//Nombre d'espais a l'hora d'imprimir la taula
int separacioV1 = 15;

//Quantitat d'elements per línia a l'hora d'imprimir la taula
int elementsV1 = 5;

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
  //return (valor/capacitat)%capacitat;
  //Sembla que return (valor*c1V1)%capacitat; redueix bastant els errors.
  return (valor*c1V1)%capacitat;
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
    return obtenirClauV2(actual, passos, capacitat, c1V1, c2V1);
  }
  else if(versio==3){
    return obtenirClauV3(actual, passos, capacitat);
  }
  else{
    return obtenirClauV1(actual, passos, capacitat);
  }
}

void inserir1T(int versio, vector<int>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = obtenirClau(versio, actual, passos, capacitat);
  if(hash[clau]==-1){
    hash[clau] = actual;
  }
  else{
    int clau2 = (clau+passos)%capacitat;
    bool trobat=false;
    while(!trobat&&(clau2!=clau)){
      if(hash[clau2]==-1){
	hash[clau2] = actual;
	trobat = true;
      }
      else{
	++missV1;
      }
      clau2 = (clau2+passos)%capacitat;
    }
    if(!trobat){
      cout << "ERROR: " << actual << endl;
      ++errorsV1;
    }
  } 
}

int cercar1T(int versio, vector<int>& hash, int passos, int capacitat, int actual){
  int clau;
  clau = obtenirClau(versio, actual, passos, capacitat);
  if(hash[clau]==actual){
    return clau;
  }
  else{
    int clau2 = (clau+passos)%capacitat;
    while(clau2!=clau){
      if(hash[clau2]==actual){
	return clau2;
      }
      else{
	++miss2V1;
      }
      clau2 = (clau2+passos)%capacitat;
    }
    ++errors2V1;
  }
  return -1;
}

void inserir2T(int taula, vector<int>& hash, vector<int>& hash2, int capacitat, int actual, bool primera, pair<int, int> bucle){
  if(taula==1){
    int clau1;
    clau1 = hashing(actual, capacitat);
    if(hash[clau1]==-1){
      hash[clau1] = actual;
    }
    else{
      if((actual==bucle.first)&&(hash[clau1]==bucle.second)){
	++errorsV1;
	errors2TV1.push_back(actual);
      }
      else{
	int tmp = hash[clau1];
	hash[clau1] = actual;
	++missV1;
	if(primera){
	  bucle = pair<int, int>(actual, tmp);
	}
	inserir2T(2, hash, hash2, capacitat, tmp, false, bucle);
      }
    }
  }
  else{
    int clau2;
    clau2 = hashing2(actual, capacitat);
    if(hash2[clau2]==-1){
      hash2[clau2] = actual;
    }
    else{
      if((actual==bucle.first)&&(hash[clau2]==bucle.second)){
	++errorsV1;
	errors2TV1.push_back(actual);
      }
      else{
	int tmp = hash2[clau2];
	hash2[clau2] = actual;
	++missV1;
	if(primera){
	  bucle = pair<int, int>(actual, tmp);
	}
	inserir2T(1, hash, hash2, capacitat, tmp, false, bucle);
      }
    }
  } 
}

int cercar2T(vector<int>& hash, vector<int>& hash2, int capacitat, int actual){
  int clau;
  clau = hashing(actual, capacitat);
  if(hash[clau]==actual){
    return clau;
  }
  clau = hashing2(actual, capacitat);
  if(hash[clau]==actual){
    return clau;
  }
  return -1;
}

int quantsDigits(int valor){
    int digits = 0;
    if(valor<0){
      return digits;
    }
    while(valor){
        valor /= 10;
        ++digits;
    }
    return digits;
}

void imprimirV1(int posicio, int valor){
  --posicio;
  int digitsPos = quantsDigits(posicio);
  if(posicio==0){
    ++digitsPos;
  }
  int digitsVal = quantsDigits(valor);
  int espais = separacioV1-digitsPos-digitsVal-2;
  cout << "[" << posicio << "]";
  if(digitsVal>0){
    cout << " " << valor;
    --espais;
  }
  for(int i=0; i<espais; ++i){
    cout << " ";
  }
}

void hash1T(int versio, vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 1.5*mida;
  int passos = obtenirPassos(capacitat);
  vector<int> hash(capacitat, -1);
  
  int start1 = clock();
  for(int i=0; i<mida; ++i){
    inserir1T(versio, hash, passos, capacitat, dict[i]);
  }
  int stop1 = clock();
  
  int mida2 = entr.size();
  int trobats = 0;
  int clockSi = 0, clockNo = 0;
  int start2 = clock();
  for(int i=0; i<mida2; ++i){
    int start3 = clock();
    int clau = cercar1T(versio, hash, passos, capacitat, entr[i]);
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
  cout << "Tècnica: OPEN" << endl;
  if(versio==1){
    cout << "Funció: LINEAR" << endl;
  }
  else if(versio==2){
    cout << "Funció: QUADRATIC" << endl;
  }
  else if(versio==3){
    cout << "Funció: DOUBLE" << endl;
  }
  cout << "Ocupació: " << 100*((float)(mida-errorsV1)/(float)capacitat) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "#### INSERCIÓ ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Salts: " << missV1 << endl;
  cout << "Errors: " << errorsV1 << endl;
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
    imprimirV1(i, hash[(i-1)]);
    if((i%elementsV1)==0){
      cout << endl;
    }
  }
  if((mida%elementsV1)!=0){
    cout << endl;
  }
}

void hash2T(int versio, vector<int>& dict, vector<int>& entr){
  int mida = dict.size();
  int capacitat = 1.5*mida;
  int passos = obtenirPassos(capacitat);
  vector<int> hash(capacitat, -1);
  vector<int> hash2(capacitat, -1);
  int start1 = clock();
  for(int i=0; i<mida; ++i){
    inserir2T(1, hash, hash2, capacitat, dict[i], true, pair<int, int>(-1, -1));
  }
  int stop1 = clock();
  
  int mida2 = entr.size();
  int trobats = 0;
  int clockSi = 0, clockNo = 0;
  int start2 = clock();
  for(int i=0; i<mida2; ++i){
    int start3 = clock();
    int clau = cercar2T(hash, hash2, capacitat, entr[i]);
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
  cout << "Tècnica: OPEN" << endl;
  cout << "Funció: CUCKOO" << endl;
  cout << "Ocupació: " << 100*((float)(mida-errorsV1)/(float)(2*capacitat)) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "#### INSERCIÓ ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Salts: " << missV1 << endl;
  cout << "Errors: " << errorsV1 << endl;
  cout << "Temps: " << (stop1-start1)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### CERCA ####" << endl;
  cout << "Mida: " << mida2 << endl;
  cout << "Salts: " << miss2V1 << endl;
  cout << "Errors: " << errors2V1 << endl;
  cout << "Temps total: " << (stop2-start2)/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps trobats: " << clockSi/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "Temps no trobats: " << clockNo/double(CLOCKS_PER_SEC)*1000 << endl;
  cout << "#### RESULTAT ####" << endl;
  cout << "Trobats: " << trobats << endl;
  cout << "No trobats: " << notrobats << endl;
  cout << "#### TAULA RESULTANT 1 ####" << endl;
  for(int i=1; i<=capacitat; ++i){
    imprimirV1(i, hash[(i-1)]);
    if((i%elementsV1)==0){
      cout << endl;
    }
  }
  if((mida%elementsV1)!=0){
    cout << endl;
  }
  cout << "#### TAULA RESULTANT 2 ####" << endl;
  for(int i=1; i<=capacitat; ++i){
    imprimirV1(i, hash2[(i-1)]);
    if((i%elementsV1)==0){
      cout << endl;
    }
  }
  if((mida%elementsV1)!=0){
    cout << endl;
  }
}

void hashV1(int versio, vector<int>& dict, vector<int>& entr){
  if((versio>0)&&(versio<4)){
    hash1T(versio, dict, entr);
  }
  else if(versio==4){
    hash2T(versio, dict, entr);
  }
}
