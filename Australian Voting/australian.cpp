/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <set>
#include <cstdlib>

using namespace std;

int ballots[1000][20];
int conteo[21];

bool es_blanca(string s)
{
	string::iterator it;
	for(it=s.begin(); it!=s.end(); it++) {
		if(*it != ' ' || *it != '\t' || *it != '\n') return false;
	}
	return true;
}

int main(void)
{
	int n, cases, tmp_int, i, j;
	string candidate, tmp;
	vector<string> candidates;
	stringstream ss(stringstream::in | stringstream::out);
	
	cin >> cases;
	getline(cin, tmp); //linea blanca
	
	while(cases>0) {
		//leer los candidatos
		cin >> n;getline(cin, candidate);
		i = n;
		while(i>0) {
			getline(cin, candidate);
			candidates.push_back(candidate);
			i--;
		}
		
		//leer las boletas
		bool votos = false;
		i = 0;
		getline(cin, tmp);
		while(!es_blanca(tmp)) {
			votos = true;
			ss.str(tmp);
			j = 0;
			while(!ss.eof()) {
				ss >> ballots[i][j];
				j++;
			}
			ss.clear(stringstream::goodbit);
			if(cin.eof()) break;
			getline(cin, tmp);
			if(es_blanca(tmp)) break;
			i++;
		}
		
		set<int> candidatos_en_carrera;
		set<int>::iterator it_s;
		//set<int> boletas_consideradas;  //o mejor contamos todas las boletas de nuevo
		bool flag = false;
		int min=i+1;    //i+1 es cantidad de votos
		int rango = 0;
    	int g = (int) floor((i+1)/2.0);   //un candidato debe recibir g+1 votos entonces
		
		//resetear candidatos en carrera
		for(int c=1; c<=n; c++)
		    candidatos_en_carrera.insert(c);

		while(1) {
        	if(!votos) {
				for(vector<string>::iterator it=candidates.begin(); it!=candidates.end(); it++)
		    		cout << *it << endl;
				break;
			}
	
			min=i+1;
            //resetear conteo de votos
			for(int c=0; c<21; c++) conteo[c] = 0;
			
			//contar todos los votos en cada iteracion, pero solo los de los candidatos validos
			for(int c = 0; c<=i; c++) {
	 			rango = 0;
				while(!candidatos_en_carrera.count(ballots[c][rango]) && rango<=n)
					rango++;
				if(rango<=n)
					conteo[ballots[c][rango]]++;
			}

			for(int c = 1; c<=n; c++) {
				if(conteo[c] < min && candidatos_en_carrera.count(c)) min = conteo[c];
			    if(conteo[c]>=g+1) {
					flag = true;
					cout << candidates[c-1] << endl;
				}
			}
			//si hubo ganador lo imprimimos, sino borramos a los peores
			if(flag) {
				break;
			} else {
				bool flag_2 = true;
				//cout << "min " << min << endl;
				for(it_s = candidatos_en_carrera.begin(); it_s != candidatos_en_carrera.end(); it_s++) {
				    if(conteo[*it_s] != min) flag_2 = false;
				}
				if(flag_2) {
                    for(it_s = candidatos_en_carrera.begin(); it_s != candidatos_en_carrera.end(); it_s++) {
						cout << candidates[(*it_s) - 1] << endl;
					}
					break;
				} else {
					for(int c=1; c<=n; c++)
						if(conteo[c] == min) candidatos_en_carrera.erase(c);
				}
			}
		}

		candidates.clear();
		cases--;
		if(cases>0) cout << endl;
	}
	
	return 0;
}
