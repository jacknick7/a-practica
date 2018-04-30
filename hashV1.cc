#include "hashV1.hh"

int missV1=0;
int errorsV1=0;

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
  return (valor/capacitat)%capacitat;
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
    int clau2 = (clau+1)%capacitat;
    bool trobat=false;
    while(!trobat&&(clau2!=clau)){
      if(hash[clau2]==-1){
	hash[clau2] = actual;
	trobat = true;
      }
      else{
	++missV1;
      }
      clau2 = (clau2+1)%capacitat;
    }
    if(!trobat){
      cout << actual << endl;
      ++errorsV1;
    }
  } 
}

void inserir2T(int taula, vector<int>& hash, vector<int>& hash2, int passos, int capacitat, int actual, bool primera, pair<int, int> bucle){
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
	inserir2T(2, hash, hash2, passos, capacitat, tmp, false, bucle);
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
	inserir2T(1, hash, hash2, passos, capacitat, tmp, false, bucle);
      }
    }
  } 
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

void imprimir(int posicio, int valor){
  int digitsPos = quantsDigits(posicio);
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
  for(int i=0; i<mida; ++i){
    inserir1T(versio, hash, passos, capacitat, dict[i]);
  }
  cout << "#### RESULTATS ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Ocupació: " << 100*((float)(mida-errorsV1)/(float)capacitat) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "Salts: " << missV1 << endl;
  cout << "errorsV1: " << errorsV1 << endl;
  cout << "#### TAULA RESULTANT ####" << endl;
  for(int i=1; i<=mida; ++i){
    imprimir(i, hash[(i-1)]);
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
  for(int i=0; i<mida; ++i){
    inserir2T(1, hash, hash2, passos, capacitat, dict[i], true, pair<int, int>(-1, -1));
  }
  cout << "#### RESULTATS ####" << endl;
  cout << "Mida: " << mida << endl;
  cout << "Ocupació: " << 100*((float)(mida-errorsV1)/(float)(2*capacitat)) << "%" << endl;
  cout << "Var. passos: " << passos << endl;
  cout << "Salts: " << missV1 << endl;
  cout << "errorsV1: " << errorsV1 << endl;
  cout << "#### TAULA RESULTANT 1 ####" << endl;
  for(int i=1; i<=mida; ++i){
    imprimir(i, hash[(i-1)]);
    if((i%elementsV1)==0){
      cout << endl;
    }
  }
  if((mida%elementsV1)!=0){
    cout << endl;
  }
  cout << "#### TAULA RESULTANT 2 ####" << endl;
  for(int i=1; i<=mida; ++i){
    imprimir(i, hash2[(i-1)]);
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
