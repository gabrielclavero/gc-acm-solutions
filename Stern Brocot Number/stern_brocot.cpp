/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(void)
{
	long double m, n, nodoL_n, nodoL_d, nodoR_n, nodoR_d, nodo_n, nodo_d;   //nodo_L es el numerador (_n) o denominador (_d) del nodo izquierdo a considerar, nodo es el nodo actua, y nodoR el derecho
	string res;
	
	cin >> m; cin >> n;
	while((m != 1.0) || (n != 1.0)) {
		res.clear();
		
		long double tmp = m/n;
		nodoL_n = 0.0; nodoL_d = 1.0;
		nodoR_n = 1.0; nodoR_d = 0.0;
		nodo_n = 1.0; nodo_d = 1.0;
		long double nodo = nodo_n/nodo_d;
		while(fabs(tmp - nodo) > 0.0000000001) {
			if(tmp < nodo) {    //nos movemos a la derecha del arbol en la busqueda binaria. Asi que nuestro nuevo nodo derecho es el nodo actual
				res.push_back('L');
				nodoR_n = nodo_n;
				nodoR_d = nodo_d;
				nodo_n += nodoL_n;  //la formula del libro (m+m')/(n+n')
				nodo_d += nodoL_d;
			} else {
				res.push_back('R');
				nodoL_n = nodo_n;
				nodoL_d = nodo_d;
				nodo_n += nodoR_n;
				nodo_d += nodoR_d;
			}
			
			nodo = nodo_n/nodo_d;

		}
		cout << res << endl;
		cin >> m; cin >> n;
	}

	return 0;
}
