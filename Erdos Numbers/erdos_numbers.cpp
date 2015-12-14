/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

//espero que las p lineas de los papers sean escritas exactamente como dice el ejemplo, ni un espacio en blanco mas

int main(void)
{
	int scenarios;
	int p, n, i, escenario;
	string tmp, nombre, apellido;
	stringstream ss(stringstream::in | stringstream::out);
	
	map<string, set<string> >::iterator it_mp;
	set<string>::iterator it_vc;
	set<string>::iterator it_vc2;
	
	cin >> scenarios;
	escenario = 1;
	while(scenarios > 0) {
		cin >> p; cin >> n;
		getline(cin, tmp);	//no olvidarse de deshacerse del \n final
		//papers
		map<string, set<string> > cols; //este map contiene un elemento por cada autor, que especifica los autores que han trabajado junto a él (por eso usamos un set)
		set<string> cols_tmp;	//un autor no tiene por qué figurar dos veces como autor del paper
		
		for(i=0; i<p; i++) {
			getline(cin, tmp, ':');
			ss.str(tmp);
			getline(cin, tmp);	//nombre del paper, solo para deshacernos de el, no importa
			while(!ss.eof()) {
				getline(ss, apellido, ',');
				getline(ss, nombre, ',');
				if(apellido[0]==' ') 
					apellido.erase(0,1);
				
				cols_tmp.insert(apellido+","+nombre);
			}
			

			//a partir de los colaboradores en cols_tmp
			for(it_vc=cols_tmp.begin(); it_vc!=cols_tmp.end(); it_vc++) {
				it_mp = cols.find(*it_vc);
				if(it_mp == cols.end()) {
					set<string> my_set;
					it_mp = (cols.insert( pair<string,set<string> >(*it_vc, my_set) )).first;
				}	
				for(it_vc2=cols_tmp.begin(); it_vc2!=cols_tmp.end(); it_vc2++) {
					if(it_vc2 != it_vc)	//no insertamos a un autor como colaborador de sí mismo
						(it_mp->second).insert(*it_vc2);
				}
			}
			cols_tmp.clear();
			ss.clear(stringstream::goodbit);
		}
	
		
		//nombres, si hay repetidos imprimiríamos dos veces su erdos number en el output, ¿esta bien?
		vector<string> nombres(n);
		for(i=0; i<n; i++) {
			getline(cin, tmp);
			nombres[i] = tmp;
		}

			
		set<string> no_disponibles;
		set<string> siguientes[2];
		map<string, int> res;	//dado un autor este objeto devuelve su erdos number
		it_mp = cols.find("Erdos, P.");
		if(it_mp != cols.end()) {
			for(it_vc=(it_mp->second).begin(); it_vc!=(it_mp->second).end(); it_vc++) {
				res.insert(pair<string,int>(*it_vc, 1));
				siguientes[0].insert(*it_vc);
				no_disponibles.insert(*it_vc);
			}
			no_disponibles.insert("Erdos, P.");
			int erdos_number = 2;
			int quien_toca = 0;
			while(!siguientes[quien_toca].empty()) {
				for(it_vc=siguientes[quien_toca].begin(); it_vc!=siguientes[quien_toca].end(); it_vc++) {
					it_mp = cols.find(*it_vc);
					for(it_vc2=(it_mp->second).begin(); it_vc2!=(it_mp->second).end(); it_vc2++) { // para todos los colaboradores de ese tipo...
						if(no_disponibles.find(*it_vc2)==no_disponibles.end())  { //si aun no le fue asignado un erdos number...
							//cout << "agregamos a " << *it_vc2 << endl;
							res.insert(pair<string,int>(*it_vc2, erdos_number));
							siguientes[(quien_toca+1)%2].insert(*it_vc2);
							no_disponibles.insert(*it_vc2);
						}
					}
				}
				siguientes[quien_toca].clear();
				quien_toca = (quien_toca+1)%2;
				erdos_number++;
			}
		} /*else {
			//TODOS TIENEN INFINITY, o sea: res.empty == true
		}*/
		
		//imprimir respuesta:
		map<string, int>::iterator it_mp2;
		vector<string>::iterator it_nombres;
		cout << "Scenario " << escenario << endl;
		for(it_nombres=nombres.begin(); it_nombres!=nombres.end(); it_nombres++) {
			it_mp2 = res.find(*it_nombres);
			if(it_mp2 != res.end())
				cout << it_mp2->first << " " << it_mp2->second << endl;
			else {
				/*if(*it_nombres == "Erdos, P.") 
					cout << *it_nombres << " infinity" << endl;
				else*/
					cout << *it_nombres << " infinity" << endl;
			}
		}
		escenario++;
		scenarios--;
	}
	return 0;
}
