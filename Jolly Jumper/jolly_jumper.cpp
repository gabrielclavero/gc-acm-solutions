/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

int main(void)
{
	int i,n,tmp;
	int sequence[3000];
	set<int> valores;

	
	cin >> n;
	while(!cin.eof()) {
		for(i=0; i<n; i++) 
			cin >> sequence[i];
			
			
		for(i=1; i<n; i++) {
			tmp = abs(sequence[i]-sequence[i-1]);
			if(tmp >= 1 && tmp <=n-1)
				valores.insert(tmp);	//insertamos al conjunto el valor absoluto de la diferencia entre elementos consecutivos solo si el valor esta en el rango requerido
		}
	
		//como el set no permite elementos repetidos y solo agregamos numeros entre 1 y n-1, valores contendrá todos los numeros de 1 hasta n-1 sii |valores| = n-1
		if((int) valores.size()==n-1)
			cout << "Jolly" << endl;
		else 
			cout << "Not jolly" << endl;
		
		valores.clear();
		cin >> n;
	}
	
		
	return 0;
}
