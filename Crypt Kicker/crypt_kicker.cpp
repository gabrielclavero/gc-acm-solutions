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
#include <sstream>
#include <cmath>
#include <set>

using namespace std;

int mapear_palabra(string palabra);
map<char,char> recursion(vector<string>::iterator it, map<char,char> desenc, set<char> no_disponibles);
void mapear_caracteres(string pal_dict, string pal_enc, map<char,char>& desenc, set<char>& no_disponibles);
bool es_solucion(string pal_dict, string pal_enc, map<char,char> desenc, set<char> no_disponibles);

//Estas no preocupan si son variables globales puesto que no cambian durante el backtracking
vector<string> lineas;
multimap<int,string> mapeo_dict;	//GLOBAL: mapeo de palabras del diccionario, dado un int (basado en la longitud y cantidad de letras repetidas del string ) te devuelve las palabras que cumplen ese key
map<string,int> mapeo_encrypt;	//GLOBAL: mapeo de palabras encriptadas, dado un string te devuelve el int que puedes usar como key para ver las palabras en mapeo_dict que pueden asociarse con esta. No es multimap porque una palabra solo puede estar asociada a un entero de esos, asi que no tiene sentido agregar palabras repetidas

int main(void)
{
	int n, i;
	set<string> diccionario; //usamos un set porque no existen palabras repetidas en un diccionario (normalmente)
	
	string tmp;
	stringstream ss(stringstream::in | stringstream::out);
	
	cin >> n;
	for(i=0; i<n; i++) {
		cin >> tmp;
		diccionario.insert(tmp);
	}
	
	getline(cin, tmp);//el cin >> deja el ultimo \n libre, con esta sentencia nos deshacemos de él

	do {
		lineas.clear();
		mapeo_encrypt.clear();
		getline(cin, tmp);
		if(tmp.size()==0) { /*cout << endl;*/ continue; }
		ss.clear(stringstream::goodbit);
		ss.str(tmp);		
		while(!ss.eof()) {	
			ss >> tmp;
			lineas.push_back(tmp);
		}
		
		//COMPLETAR ESTRUCTURAS DE DATOS NECESARIAS PARA EL BACKTRACKING
		vector<string>::iterator it;
		set<string>::iterator it_dict;
		if(mapeo_dict.size() == 0) {	//este mapa se completa una vez por cada ejecucion del programa (usamos el mismo diccionario por cada ejecucion)
			for(it_dict=diccionario.begin(); it_dict!=diccionario.end(); it_dict++)
				mapeo_dict.insert(pair<int,string>(mapear_palabra(*it_dict), *it_dict));
		}
		for(it=lineas.begin(); it!=lineas.end(); it++)
			mapeo_encrypt.insert(pair<string, int>(*it, mapear_palabra(*it)));
			
		
		//DESENCRIPTAR, BACKTRACKING
		//USAR equal_range PARA OBTENER TODOS LOS ELEMENTOS CON UN KEY IGUAL A x
		map<char, char> desenc;		//mapeo solucion, o sea: dado un caracter te devuelve el caracter que lo reemplaza en el texto desencriptado
		set<char> no_disponibles; //conjunto de los caracteres que ya han sido asociados a un caracter encriptado y .:. no pueden usarse ya
		desenc = recursion(lineas.begin(), desenc, no_disponibles);
	
		//IMPRIMIR RESPUESTA
		//cout << "una por cada linea" << endl;
		if(desenc.size() > 0) { //hubo solucion, procedamos a imprimirla sabiendo que tenemos la solucion en desenc
			string::iterator it2;
			for(it=lineas.begin(); it!=lineas.end(); it++) {
				for(it2=it->begin(); it2!=it->end(); it2++)
					cout << desenc.find(*it2)->second;
				if(it!=lineas.end()-1)
					cout << " ";
			}
		} else {
			for(it=lineas.begin(); it!=lineas.end(); it++) {
				for(unsigned int i=0; i<it->length(); i++)
					cout << "*";
				if(it!=lineas.end()-1)
					cout << " ";
			}
		}
		cout << endl;
	} while(!cin.eof());
		
	return 0;
}

//desenc es la solucion parcial
map<char,char> recursion(vector<string>::iterator it, map<char,char> desenc, set<char> no_disponibles)
{
	if(it!=lineas.end()) {
		multimap<int, string>::iterator it2;
		pair<multimap<int, string>::iterator,multimap<int, string>::iterator> rango;
		
		rango = mapeo_dict.equal_range(mapeo_encrypt.find(*it)->second);
		map<char,char> desenc_tmp;
		set<char> no_disponibles_tmp;
		bool flag = false;
		for(it2=rango.first; it2!=rango.second; it2++) {	//para cada palabra en el diccionario que puedas usarla para desencriptar la actual...
			desenc_tmp.clear(); desenc_tmp = desenc;	//recuperamos la solucion parcial en caso de que el subarbol explorado no haya tenido exito y debamos subir (backtrackear)
			no_disponibles_tmp.clear(); no_disponibles_tmp = no_disponibles;	
			flag = false;
			if(es_solucion(it2->second, *it, desenc, no_disponibles)) {
				mapear_caracteres(it2->second, *it, desenc_tmp, no_disponibles_tmp);
				it++;
				desenc_tmp = recursion(it, desenc_tmp, no_disponibles_tmp);
				if(desenc_tmp.size() > 0) { //si llegamos a una solucion siguiendo esa rama del grafo...
					flag = true;	
					break;
				} else it--;	//backtracking
			}
		}
		//si ninguna de las ramas llevaba a una solución devolvemos el map vacío a fin de avisar a los nodos superiores del fracaso
		if(flag)
			return desenc_tmp;
		else { 
			desenc_tmp.clear();
			return desenc_tmp;
		}		
	} else
		return desenc;
}

void mapear_caracteres(string pal_dict, string pal_enc, map<char,char>& desenc, set<char>& no_disponibles)
{
	string::iterator it_enc, it_dict = pal_dict.begin();
	for(it_enc = pal_enc.begin(); it_enc!=pal_enc.end(); it_enc++) {
		if(desenc.find(*it_enc)==desenc.end()) {	//si la letra no está desencriptada ya... (si está desencriptada es precondicion de la funcion que el mapeo sea consistente)
			desenc.insert(pair<char,char>(*it_enc, *it_dict));
			no_disponibles.insert(*it_dict);
		}
		it_dict++;
	}
}

//pre: pal_dict y pal_enc tienen la misma longitud y misma cantidad de letras repetidas de a dos y de a tres y de a uno, etc
//devuelve true si pal_dict puede ser la desencriptacion de pal_enc
bool es_solucion(string pal_dict, string pal_enc, map<char,char> desenc, set<char> no_disponibles)	//el ultimo parámetro se pasa por valor, importante
{
	string::iterator it_enc, it_dict = pal_dict.begin();
	for(it_enc = pal_enc.begin(); it_enc!=pal_enc.end(); it_enc++) {
		if(desenc.find(*it_enc)!=desenc.end()) {	//si la letra ya estaba mapeada...
			if(desenc.find(*it_enc)->second != *it_dict)
				return false;
		} else {
			if(no_disponibles.find(*it_dict) == no_disponibles.end()) {	//si la letra solucion está disponible para mapearse todavía...
				desenc.insert(pair<char,char>(*it_enc, *it_dict));
				no_disponibles.insert(*it_dict);
			} else
				return false;
		}
		it_dict++;
	}
	return true;
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
