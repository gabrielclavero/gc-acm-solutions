/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool es_blanco(string tmp);
void sacar_blancos(string &s);
int unos(string s);
int ceros(string s);

string recursion(string files, vector<string>::iterator fragmento, multiset<string> disponibles);

multimap<pair<int,int>,string> matchs; //dado un par de enteros x e y, matchs devuelve un string que necesita concatenarse con un string de x ceros e y unos para formar el patron de bits original
vector<string> fragmentos;

int main(void)
{
	int cases;
	string::iterator it_st;
	vector<string>::iterator it_vc;
	
	cin >> cases;
	
	for(int i=0; i<2; i++) {
		while(cin.peek()!='\n')
			cin.ignore();
		cin.ignore();
	}
	
	while(cases > 0) {
		string tmp;
		
		getline(cin, tmp);
		while(!es_blanco(tmp)) {
			sacar_blancos(tmp);
			fragmentos.push_back(tmp);
			if(cin.eof()) break;
			getline(cin, tmp);
		}
		
		string total;
		for(it_vc=fragmentos.begin(); it_vc!=fragmentos.end(); it_vc++)
			total += *it_vc;
			
		int length_output, unos_output=0, ceros_output=0;	//longitud, cantidad de unos y cantidad de ceros que aparecen en el bit pattern de los archivos originales
		
		length_output = total.length()/(fragmentos.size()/2);	//longitud del output es la longitud de todo concatenado dividido N
		
		for(it_st=total.begin(); it_st!=total.end(); it_st++) {
				if(*it_st == '1') unos_output++;
				else if(*it_st == '0') ceros_output++;
		}
		unos_output = unos_output/(fragmentos.size()/2);
		ceros_output = ceros_output/(fragmentos.size()/2);
		
			
		//COMPLETAMOS EL MAPA matchs (ver variables globales del programa)		
		for(it_vc=fragmentos.begin(); it_vc!=fragmentos.end(); it_vc++) 
			matchs.insert( pair<pair<int,int>,string> ( pair<int,int> (ceros_output - ceros(*it_vc), unos_output - unos(*it_vc)), *it_vc ) );
			

			
		//BACKTRACKING PURO, SALGAMOS EN CUANTO ENCONTREMOS LA SOLUCION (QUE SIEMPRE EXISTE)

		//Variables Necesarias
		string files;	// el patron de bits de los archivos originales que estamos considerando como el correcto hasta el momento
		multiset<string> disponibles;	//fragmentos que aun no han encontrado su pareja, podría usar un array de bits en lugar de esto pero, no importa, son a lo sumo 288 elementos
		
		for(it_vc=fragmentos.begin(); it_vc!=fragmentos.end(); it_vc++)
			disponibles.insert(*it_vc);
		disponibles.erase(disponibles.find(*fragmentos.begin()));
		
		//parametros: solucion parcial, fragmento actual en consideracion, conjunto de fragmentos no asignados
		
		files = recursion(files, fragmentos.begin(), disponibles);
		
		cout << files << endl;
		
		if(cases!=1) cout << endl;
		
		matchs.clear();
		fragmentos.clear();
		cases--;
	}
			
			
	return 0;
}

string recursion(string files, vector<string>::iterator fragmento, multiset<string> disponibles)
{
	if(fragmento==fragmentos.end()) 
		return files;
	else {
		pair<multimap<pair<int,int>,string>::iterator,multimap<pair<int,int>,string>::iterator> it_matchs;
		pair<int,int> par_u_c;
		multimap<pair<int,int>,string>::iterator it_mp;
			
		multiset<string>::iterator it_ms;
		
		//buscamos sus candidatos
		par_u_c = pair<int,int>(ceros(*fragmento), unos(*fragmento));
		it_matchs = matchs.equal_range(par_u_c);
		
		if(files.size() != 0) {		//sino estamos en el primer nodo
			
			for(it_mp=it_matchs.first; it_mp!=it_matchs.second; it_mp++) {	//por cada fragmento de archivo que pueda ser la pareja de éste
				it_ms = disponibles.find(it_mp->second);
				if(it_ms != disponibles.end()) {	//si el candidato está disponible
					if((files == *fragmento+(it_mp->second)) || (files == it_mp->second+(*fragmento))) {	//si puede ser solucion...
						disponibles.erase(it_ms);
						
						//pasamos al siguiente fragmento que aun no haya encontrado pareja
						fragmento++;
						if(fragmento!=fragmentos.end()) {
							while(disponibles.find(*fragmento) == disponibles.end()) {
								fragmento++;
								if(fragmento == fragmentos.end()) return files;
							}
						} else
							return files;
						
						files = recursion(files, fragmento, disponibles);
						if(files.size() > 0)
							break;	//solucion!
						
						disponibles.insert(it_mp->second);
					}
				}
			}
			if(it_mp==it_matchs.second) //no hubo solucion en este nodo con ninguno de los candidatos
				files.clear();
		}
		else {
			vector<string>::iterator tmp = fragmento;
			//cout << *fragmento << endl;
			for(it_mp=it_matchs.first; it_mp!=it_matchs.second; it_mp++) {	//por cada fragmento de archivo que pueda ser la pareja de éste
				it_ms = disponibles.find(it_mp->second);
				disponibles.erase(it_ms);		//usamos un iterador en vez de un string para borrar solo uno y notodos los elementos con esa clave
				files = *fragmento+(it_mp->second);
				//cout << files << endl;
				//pasamos al siguiente fragmento que aun no haya encontrado pareja
				tmp++;
				if(tmp!=fragmentos.end()) {
					while(disponibles.find(*tmp) == disponibles.end()) {
						tmp++;
						if(tmp == fragmentos.end()) return files;
					}
				} else
					return files;
				
				files = recursion(files, tmp, disponibles);
				if(files.size() > 0) break;
				else {
					files = (it_mp->second)+(*fragmento);
					//cout << files <<"al reves" << endl;
					//pasamos al siguiente fragmento que aun no haya encontrado pareja
					tmp++;
					if(tmp!=fragmentos.end()) {
						while(disponibles.find(*tmp) == disponibles.end()) {
							tmp++;
							if(tmp == fragmentos.end()) return files;
						}
					} else
						return files;
					
					files = recursion(files, tmp, disponibles);
					if(files.size() > 0) break;
					disponibles.insert(it_mp->second);
				}
			}
		}
		
	}
	return files;
}

//devuelve true si tmp es una string formada totalmente por caracteres espacios (tabulaciones, espacios o nuevas lineas)
bool es_blanco(string tmp)
{
	for(unsigned int i=0; i<tmp.size(); i++) {
		if((tmp[i] != ' ') && (tmp[i] != '\t') && (tmp[i] != '\n')) return false;
	}
	return true;
}

void sacar_blancos(string &s)
{
	string::iterator it;
	for(it=s.begin(); it<=s.end()-1; it++) {
		if(*it==' ' || *it=='\t' || *it=='\n')
			s.erase(it);
	}
	if(s.size() > 0) {
		it = s.end()-1;
		if(*it==' ' || *it=='\t' || *it=='\n')
			s.erase(it);
	}
}

int unos(string s)
{
	unsigned int i;
	int res = 0;
	for(i=0; i<s.size(); i++) {
		if(s[i] == '1') res++;
	}
	return res;
}
int ceros(string s)
{
	unsigned int i;
	int res = 0;
	for(i=0; i<s.size(); i++) {
		if(s[i] == '0') res++;
	}
	return res;
}
