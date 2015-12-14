/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;


void flips(vector<int> &pancakes, int pos);

int main(void)
{
	vector<int> pancakes;
	string tmp;
	int diameter;
	stringstream ss(stringstream::in | stringstream:: out);
	
	while(!cin.eof()) {
		getline(cin, tmp);
		//pasar numeros al stack de pancakes (en realidad un vector)
		ss.str(tmp);
//		cout << ss.str() << endl;
		while(!ss.eof()) {
			ss >> diameter;
			pancakes.push_back(diameter);
		}
		ss.clear(stringstream::goodbit);
		
		//imprimir stack original
		for(int i=0; i<pancakes.size(); i++)
			cout << pancakes[i] << " ";
		cout << endl;
	
		//algoritmo
		int indice_ordenado = pancakes.size()-1, max, aux;	//indice_ordenado indica que las ultimas n-1 - índice_ordenado posiciones del stack están ordenadas
	
		while(indice_ordenado>=1) {
			//buscar panqueque mas grande en el substack desordenado
			max=0, aux=1;
			while(aux<=indice_ordenado) {
				if(pancakes[aux] > pancakes[max])
					max = aux;
				aux++;
			}
			if(max!=indice_ordenado && max!=0) {
				flips(pancakes, max);
				cout << pancakes.size()-max << " ";
				flips(pancakes, indice_ordenado);
				cout << pancakes.size()-indice_ordenado << " ";
			} else if(max==0) {
				flips(pancakes, indice_ordenado);
				cout << pancakes.size()-indice_ordenado << " ";
			}
			indice_ordenado--;
		}
		cout << 0 << endl;
		pancakes.clear();
	}

	return 0;
}

void flips(vector<int> &pancakes, int pos)
{
	int tmp;
	for(int i=0; i<=(int) floor((pos-1.0)/2.0); i++) {
		//swap i con pos-i
		tmp = pancakes[i];
		pancakes[i] = pancakes[pos-i];
		pancakes[pos-i] = tmp;
	}

}
