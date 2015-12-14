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
#include <map>
#include <cmath>

using namespace std;

bool es_blanco(string tmp);
int mapear_palabra(string palabra);
void sacar_blancos(string &s);

int main(void)
{
	int cases, i;
	string frase = "thequickbrownfoxjumpsoverthelazydog";
	int frase_mapeos[] = {33, 55, 55, 33, 55, 44, 33, 44, 33};
	
	cin >> cases;
	for(i=0; i<2; i++) {
		while(cin.peek()!='\n')
			cin.ignore();
		cin.ignore();
	}
	
	while(cases > 0) {;
		string tmp;
		vector<string> lineas;
		do {
			getline(cin, tmp);
			lineas.push_back(tmp);
		} while(!es_blanco(tmp) &&  !cin.eof());
		
		
		//itero a través de cada linea buscando las que puedan ser la encriptacion de "the quick brown fox jumps..."
		vector<string>::iterator it_main;
		stringstream ss(stringstream::in | stringstream::out);
		map<char,char> solucion;
		
		for(it_main=lineas.begin(); it_main!=lineas.end(); it_main++) {		//una iteracion por cada linea
			ss.str(*it_main);
			i=0;
			while(!ss.eof()) {	//una iteracion por cada palabra de la linea actual
				ss >> tmp;
				if(mapear_palabra(tmp)==frase_mapeos[i]) {
					i++;
					if(i==9) break;
				} else 
					break;
			}
			if(i==9) {
				while(!ss.eof()) { 	//verificamos que no haya habido mas palabras en esta linea
					if(!(ss.peek()== ' ') || (ss.peek() == '\t') || (ss.peek() == '\n')) break;
					ss.ignore();
				}
			}
			if(i==9 && ss.eof()) {	//mapeo consistente?
				//cout << *it_main << endl;
				tmp = *it_main;
				sacar_blancos(tmp);
				unsigned int k = 0;	//indice para el string frase
				for(unsigned int j=0; j<tmp.size(); j++) {
					if(solucion.find(tmp[j])==solucion.end()) {		//si el caracter aun no está mapeado
						solucion.insert(pair<char,char>(tmp[j], frase[k]));
						//cout << tmp[j] << " es correcto" << endl;
					} else {
						if(solucion.find(tmp[j])->second != frase[k]) break;
						//cout << tmp[j] << " es correcto" << endl;
					}
					k++;
				}
				if(k==tmp.size())  { //hay solucion
					break;
				}
			}
			ss.clear(stringstream::goodbit);
			solucion.clear();
		}
		
		if(solucion.size() > 0) {
			char c;
			for(it_main=lineas.begin(); it_main!=lineas.end(); it_main++) {
				for(unsigned int j=0; j<it_main->size(); j++) {
					c = (*it_main)[j];
					if((c != ' ') && (c != '\n') && (c != '\t'))
						cout << solucion.find(c)->second;
					else
						cout << c;
				}
				if(it_main!=lineas.end()-1 || cases!=1) cout << endl;
			}
		} else {
			cout << "No solution." << endl;
			if(cases!=1)cout << endl;
		}
		cases--;
	}				
	return 0;
}

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

//mapear una palabra a un entero único que lo represente según la cantidad de letras repetidas y la longitud
int mapear_palabra(string palabra)
{
	string s(palabra);
	int res = s.length();
	
	sort(s.begin(), s.end());
	
	string::iterator it;
	
	int tmp=1;
	for(it=s.begin()+1; it!=s.end(); it++) {
		if(*it==*(it-1))
			tmp++;
		else {
			res += (int) pow(10.0, tmp);
			tmp = 1;
		}
	}
	res += (int) pow(10.0, tmp);
	return res;
}
