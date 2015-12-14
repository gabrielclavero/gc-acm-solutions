/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> f;

//f(n) = f(n-1) + zonas que resultan de añadir el punto n
int rec_f(int n)
{
	if(f.size() >= n+1) return f[n];

    //algoritmo
	int tmp = rec_f(n-1);
	if(n>=3) tmp += 2; //unir los puntos vecinos a n me genera dos zonas mas
	
	//resto de los nodos: solo consideramos las lineas que se cruzan en nuestro camino
	//que son las que conectan los puntos que están entre el n y después del nodo destino (todo en sentido de las agujas del reloj) sin contar al n como destino
	
	
	/*for(int i=1; i<=n-3; i++) {
		//vecinos entre nodo destino (i) y n son los 0 =< j < i
		tmp += (i*(n-3-i+1))+1;
	}*/
	//ese bucle comentado es igual a esto:
	tmp += (int) ((n*n*n)/6.0 - n*n + (17.0/6.0)*n - 4.0);
	
	
	f.push_back(tmp);
	
	return f[n];
}

int main(void)
{
	int s, n;
	
	//casos base
	f.push_back(1);
	f.push_back(1);
	f.push_back(2);
	
	cin >> s;
	while(s>0) {
		cin >> n;
		
		cout << rec_f(n) << endl;
		
		
		s--;
	}
	
	return 0;
}
