#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "binaryV1.hh"
#include "binaryV2.hh"
#include "hashV1.hh"
#include "hashV2.hh"
#include "bloomV1.hh"
#include "bloomV2.hh"

using namespace std;

int main() {
    cout << "Selecciona l'entrada [1], [2], [3], [4] o [5]." << endl;
    char entrada;
    cin >> entrada;
    if((entrada>48)&&(entrada<54)){
      ifstream File;
      stringstream fitxer1, fitxer2;
      fitxer1 << "../Dades/" << entrada << ".dict";
      fitxer2 << "../Dades/" << entrada << ".entr";
      File.open(fitxer1.str());
      if (not File.is_open()){
	  cout << "Error, no s'ha pogut llegir el diccionari " << entrada << "." << endl;
	  return 1;
      }
      int n;
      File >> n;
      vector<int> dict(n), entr(2*n);
      for (int i = 0; i < n; ++i) File >> dict[i];
      File.close();
      File.open(fitxer2.str());
      if (not File.is_open()){
	  cout << "Error, no s'ha pogut llegir el text " << entrada << "." << endl;
	  return 1;
      }
      for (int i = 0; i < 2*n; ++i) File >> entr[i];
      File.close();
      
      cout << "Selecciona la cerca [B]inary, [H]ash o [BL]oom." << endl;
      string type;
      cin >> type;
      if(type == "B"){
	  cout << "Selecciona la versió [1] o [2]." << endl;
	  int versio;
	  cin >> versio;
	  if(versio==1){
	    binaryV1(dict, entr);
	  }
	  else if(versio==2){
	    binaryV2(dict, entr);
	  }
	  else{
	    cout << "Error, la versió seleccionada és incorrecta." << endl;
	  }
      }
      else if (type == "H"){
	  cout << "Selecciona la tècnica [O]pen o [C]hain." << endl;
	  char versio;
	  cin >> versio;
	  if(versio=='O'){
	    cout << "Selecciona la funció [L]inear, [Q]uadratic, [D]ouble o [C]uckoo." << endl;
	    cin >> versio;
	    if(versio=='L'){
	      hashV1(1, dict, entr);
	    }
	    else if(versio=='Q'){
	      hashV1(2, dict, entr);
	    }
	    else if(versio=='D'){
	      hashV1(3, dict, entr);
	    }
	    else if(versio=='C'){
	      hashV1(4, dict, entr);
	    }
	    else{
	      cout << "Error, la funció seleccionada és incorrecta." << endl;
	    }
	  }
	  else if(versio=='C'){
	    cout << "Selecciona la funció [M]ove to front o [E]xact fit." << endl;
	    cin >> versio;
	    if(versio=='M'){
	      hashV2(1, dict, entr);
	    }
	    else if(versio=='E'){
	      hashV2(2, dict, entr);
	    }
	    else{
	      cout << "Error, la funció seleccionada és incorrecta." << endl;
	    }
	  }
	  else{
	    cout << "Error, la tècnica seleccionada és incorrecta." << endl;
	  }
      }
      else if(type == "BL"){
	cout << "Selecciona la versió [1] o [2]." << endl;
	int versio;
	cin >> versio;
	if(versio==1){
          bloomV1(dict, entr);
	}
	else if(versio==2){
          bloomV2(dict, entr);
	}
	else{
	  cout << "Error, la versió seleccionada és incorrecta." << endl;
	}
      }
      else{
	cout << "Error, la cerca seleccionada és incorrecta." << endl;
      }
    }
    else{
      cout << "Error, l'entrada seleccionada és incorrecta." << endl;
    }
}  