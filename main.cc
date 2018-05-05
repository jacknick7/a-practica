#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "binaryV1.hh"
#include "binaryV2.hh"
#include "hashV1.hh"
#include "hashV2.hh"
#include "bloomV1.hh"

using namespace std;

int main() {
    bool automatic=true;
    if(automatic){
      cout << "#&#&#&#&#" << endl;
      for(int j=2; j<3; ++j){
	string tipus="";
	if(j==1){
	  tipus = "linear";
	}
	else if(j==2){
	  tipus = "quadratic";
	}
	else if(j==3){
	  tipus = "double";
	}
	else{
	  tipus = "cuckoo";
	}
	for(int i=2; i<5; ++i){
	  ifstream File;
	  stringstream fitxer1, fitxer2;
	  fitxer1 << "dades/" << i << ".dict";
	  fitxer2 << "dades/" << i << ".entr";
	  File.open(fitxer1.str());
	  int n;
	  File >> n;
	  vector<int> dict(n), entr(2*n);
	  for (int i = 0; i < n; ++i) File >> dict[i];
	  File.close();
	  File.open(fitxer2.str());
	  for (int i = 0; i < 2*n; ++i) File >> entr[i];
	  File.close();
	    for(int c1=0; c1<=64; ++c1){
	      for(int c2=0; c2<=64; ++c2){
		cout << "#@#@#@#@#" << endl;
		cout << "C1: " << c1 << endl;
		cout << "C2: " << c2 << endl;
		cout << "JOC: " << i << endl;
		cout << "#@#@#@#@#" << endl;
		hashV1(j, dict, entr, c1, c2);
		cout << "#&#&#&#&#" << endl;
	      }
	    }
	 }
      }
    }
    else{
      cout << "Selecciona l'entrada [1], [2], [3], [4] o [5]." << endl;
      char entrada;
      cin >> entrada;
      if((entrada>48)&&(entrada<54)){
	ifstream File;
	stringstream fitxer1, fitxer2;
	fitxer1 << "dades/" << entrada << ".dict";
	fitxer2 << "dades/" << entrada << ".entr";
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
		hashV1(1, dict, entr, 11, 17);
	      }
	      else if(versio=='Q'){
		hashV1(2, dict, entr, 11, 17);
	      }
	      else if(versio=='D'){
		hashV1(3, dict, entr, 11, 17);
	      }
	      else if(versio=='C'){
		hashV1(4, dict, entr, 11, 17);
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
	    bloomV1(dict, entr);
	}
	else{
	  cout << "Error, la cerca seleccionada és incorrecta." << endl;
	}
      }
      else{
	cout << "Error, l'entrada seleccionada és incorrecta." << endl;
      }
    }
}  