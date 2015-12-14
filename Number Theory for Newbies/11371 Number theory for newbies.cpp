/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main(void)
{
	long long int n;	//n es distinto de cero
	long long int a, b;
	stringstream ss(stringstream::in |stringstream::out);
	string s;
	
	cin >> n;
	
	do {	
		ss << n;
		ss >> s;
		ss.clear(stringstream::goodbit);
		
		//busqueda del maximo
		sort(s.begin(), s.end());
		reverse(s.begin(), s.end());
		
		ss << s;
		ss >> a;
		ss.clear(stringstream::goodbit);
		//cout << a << endl;
	
		//busqueda del minimo
		ss << n;
		ss >> s;
		ss.clear(stringstream::goodbit);
	
		/*busquemos el numero mas chico formado por digitos de n (el mas grande ya lo buscamos). El problema es que no tiene que tener ceros adelante, de manera que lo buscaremos
		así: el primer digito de nuestro numero será el digito mas chico de n distinto de 0, los demas digitos iran de menor a mayor*/
		char min = '9';
		int ubicacion;
		for(int i=0; i<s.size(); i++) {
			if(s[i] != '0' && s[i]<=min) {
				min = s[i];
				ubicacion = i;
			}
		}
		s.erase(ubicacion, 1);
		sort(s.begin(), s.end());
		
		s.insert(s.begin(), min);
		
		//cout << s << endl;
		ss << s;
		ss >> b;
		ss.clear(stringstream::goodbit);
		
		//imprimir solucion
		cout << a << " - " << b << " = " << a-b << " = 9 * " << (a-b)/9 << endl;
		s.clear();
		cin >> n;
	} while(!cin.eof());
	
	
	return 0;
	
}
