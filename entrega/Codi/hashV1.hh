#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

int obtenirPassos(int valor);
int hashing(int valor, int capacitat);
int hashing2(int valor, int capacitat);

void hashV1(int versio, vector<int>& dict, vector<int>& entr);