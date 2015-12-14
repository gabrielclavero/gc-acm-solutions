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
#include <cstdlib>

using namespace std;

//para qsort
int compare(const void *, const void *);
//para qsort final
int compare_final(const void*, const void*);
bool linea_blanca(string s);

int main(void)
{
	int cases, i;
	vector<string> entries;
	vector<string>::iterator it_vc;
	string tmp;
	
	cin >> cases;
	getline(cin, tmp); //\n dejado por el >>
	getline(cin, tmp);	//linea blanca inicial (cuidado que tal vez la linea blanca sea una empty line aunque aca no hay drama, chequealo en la funcion linea_blanca)
	while(cases > 0) {
		entries.clear();
		while(!cin.eof()) {
			getline(cin, tmp);
			if(!linea_blanca(tmp)) 
				entries.push_back(tmp);
			else 
				break;
		}
			
		vector<vector<int> > real_entries; //entradas formateadas
		vector<int> tmp_vc(4); //posicion 0: equipo, 1:problema, 2:minuto, 3:I, C, R, etc
		stringstream ss(stringstream::in | stringstream::out);
		char c;
		for(it_vc=entries.begin(); it_vc!=entries.end(); it_vc++) {
			c = *(it_vc->end()-1);	//ultimo caracter del string apuntado por it_vc
			if(c == 'I' || c == 'C') {
				ss.str(*it_vc);
				i=0;
				while(i<3) {
					ss >> tmp_vc[i];
					i++;
				}
				tmp_vc[i] = c
				real_entries.push_back(tmp_vc);
				//tmp_vc.clear();
				ss.clear(stringstream::goodbit);
			} else {
				ss.str(*it_vc);
				i = 0;
				while(i<3) {
					ss >> tmp_vc[i];
					i++;
				}
				tmp_vc[i] = 'c';
				real_entries.push_back(tmp_vc);
				ss.clear(stringstream::goodbit);
			}
		}
		
		
		//pasar todos las entradas a un arreglo de entradas para ordenar usando qsort
		int a_entries[real_entries.size()][4];
		vector<vector<int> >::iterator it_tmp1;
		int j = 0;
		for(it_tmp1=real_entries.begin(); it_tmp1!=real_entries.end(); it_tmp1++) {
			for(i=0; i<4; i++)
				a_entries[j][i] = (*it_tmp1)[i];
			j++;
		}
		//post: j es la cantidad de entradas

		qsort(a_entries, j, sizeof(int)*4, compare);
		
		
		int equipos_vistos[101]; //equipos ya chequeados
		for(i=1; i<=100; i++)
			equipos_vistos[i] = 0;
		
		short probs_resueltos[9];	//el i-ésimo problema fue resuelto por este equipo? Si: 1, NO: 0
		int penalty_time[9];	//tiempo de penalidad para el iésimo problema
		int total_penalty = 0;
		short total_resueltos = 0;
		int current_team;
		
		int finales[100][3];
		int equipos = 0;
		
		for(i=0; i<j; i++) {
			current_team = a_entries[i][0];
			if(equipos_vistos[current_team] == 1) continue;	//si ya lo chequeamos a este equipo seguimos buscando mas
			total_penalty = 0;
			total_resueltos = 0;
			for(int k=0; k<9; k++) {
				probs_resueltos[k] = 0;
				penalty_time[k] = 0;
			}
			equipos_vistos[current_team] = 1;
			for(int k=i; k<j; k++) {
				if(a_entries[k][0] == current_team) {
					if(a_entries[k][3] == (int) 'I')	//incorrect submission
						penalty_time[a_entries[k][1]-1] += 20;
					else if(a_entries[k][3] == (int) 'C') {	//correct submission
						if(probs_resueltos[a_entries[k][1]-1] == 0) {	
							probs_resueltos[a_entries[k][1]-1] = 1;
							total_penalty += penalty_time[a_entries[k][1]-1]+a_entries[k][2];
							total_resueltos += 1;
						}
					}
				}
			}
			finales[equipos][0] = current_team;
			finales[equipos][1] = total_resueltos;
			finales[equipos][2] = total_penalty;
			equipos++;
			//cout << current_team << " " << total_resueltos << " " << total_penalty << endl;
		}
		
		qsort(finales, equipos, sizeof(int)*3, compare_final);
		
		for(i=0; i<equipos; i++)
			cout << finales[i][0] << " " << finales[i][1] << " " << finales[i][2] << endl;
		
		cases--;
		if(cases)
			cout << endl;
	}
	return 0;
}

//para qsort. En nuestro caso a y b son arreglos de enteros (o sea int *)
int compare (const void *a, const void *b)
{
	int *array1 = (int *) a;
	int *array2 = (int *) b;
	
	if(array1[2] > array2[2])
		return 1;
	else if(array1[2] < array2[2])
		return -1;
	else 
		return 0;
}

int compare_final(const void *a, const void *b)
{
	if(((int *) a)[1] > ((int *) b)[1])	//comparacion por problemas resueltos
		return -1;	//en realidad debería ser 1 pero como estamos ordenando de mayor a menor hacemos asi
	else if(((int *) a)[1] < ((int *) b)[1])
		return 1;
	else {
		if(((int *) a)[2] < ((int *) b)[2])	//comparacion por penalty time
			return -1;
		else if(((int *) a)[2] > ((int *) b)[2])
			return 1;
		else {	
			if(((int *) a)[0] < ((int *) b)[0])	//comparacion por numero de equipo
				return -1;
			else if(((int *) a)[0] > ((int *) b)[0])
				return 1;
		}
	}
	return 0;
}

//devuelve true si s solo contiene espacios o está vacía
bool linea_blanca(string s)
{
	string::iterator it;
	bool blanco=true;
	for(it = s.begin(); it!=s.end(); it++)
		blanco = blanco && (*it==' ' || *it=='\t');
	
	if(!blanco) blanco = (s.size()==0);
	
	return blanco;
}
