/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>

using namespace std;

int main(void)
{
	int t, n, p, i;
	int h_param[100];
	int dias_perdidos[3651];	//no usaremos el elemento 0. dias_perdidos[i] = 0 sii el dia i no hubo huelga, = 1 otherwise
	int dia_actual, res;
	
	cin >> t;	//casos
	while(t > 0) {
		cin >> n;	//dias
		cin >> p;	//parties
		for(i=0; i<p; i++)
			cin >> h_param[i];
			
		for(i=1; i<=n; i++)
			dias_perdidos[i] = 0;
		for(i=0; i<p; i++) {
			dia_actual = h_param[i];
			while(dia_actual<=n) {
				if((dia_actual % 7 != 6) && (dia_actual % 7 != 0))
					dias_perdidos[dia_actual] = 1;
				dia_actual += h_param[i];
			}
		}
		
		res = 0;
		for(i=1; i<=n; i++) {
			//if(dias_perdidos[i]==1) cout << i << endl;
			res += dias_perdidos[i];
		}
		
		cout << res << endl;
		t--;
	}
}
