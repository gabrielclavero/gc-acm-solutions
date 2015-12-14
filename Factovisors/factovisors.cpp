/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

vector<int> primos[2];

void prime_factorization(unsigned long x, int in)
{
	unsigned long i, c;

   	primos[in].clear();
	c = x;
	while((c%2) == 0) {
		c = c/2;
		primos[in].push_back(2);
	}

	i = 3;
	while(i <= (sqrt(c)+1)) {
		if((c%i) == 0) {
			primos[in].push_back(i);
			c = c/i;
		} else {
		    i = i+2;
		}
	}

	if(c > 1)
		primos[in].push_back(c);
}

int main(void)
{
	int m, n;
	
	while(!cin.eof()) {
		cin >> n; cin >> m;

		if(m == 0)
			cout << "0 does not divide " << n << "!" << endl;
		else if(m <= n || m == 1)
		    cout << m << " divides " << n << "!" << endl;
		else if(n <= 1 && m > n)
		    cout << m << " does not divide " << n << "!" << endl;
		else {
			/*nos interesa ver si p1*....*pk = m divide a n!. Como p1, .. pk son primos esto sucederá sii
			p1..pk aparecen en la factorizacion en primos de algun i en 1..n. Pero si p1 = p2 por ej. entonces p1 tiene que
			aparecer dos veces*/

   			prime_factorization(m, 0);
   			
			//borramos los primos que son menores que n, pero si aparecen mas de una vez los borramos solo una vez ojo.
			vector<int> borrados;
			int i=0;
			while(i != primos[0].size()) {
				int tmp = primos[0][i];
				if(tmp < n) {
				    primos[0].erase(primos[0].begin()+i);
				    borrados.push_back(tmp);
				    while(i<primos[0].size() && primos[0][i] == tmp) i++;
				} else
				    break;
			}

			int j=n;
			while(primos[0].size() > 0 && j>=2) {
				//cout << j << endl;
				bool salir = false;
				for(int i=0; i<borrados.size(); i++) {
				    if(borrados[i] == j) {
						salir = true;
						break;
					}
				}
				if(salir) {
					j--;
					continue;
				}

				if(primos[0][primos[0].size()-1] > j) break;
				prime_factorization(j, 1);
				

				int i=primos[0].size()-1;
				
				while(i >= 0 && primos[1].size() > 0) {
					int c = primos[1].size()-1;
					while(c >= 0 && primos[0][i] != primos[1][c]) c--;
					if(c!=-1) {
						primos[0].erase(primos[0].begin()+i);
						primos[1].erase(primos[1].begin()+c);
						i--;
					} else {
						int c = i;
						while(c>0 && primos[0][c] == primos[0][c-1]) c--;
						i = c-1;
					}
				}
				j--;
			}

			if(primos[0].size() == 0)
			    cout << m << " divides " << n << "!" << endl;
			else
			    cout << m << " does not divide " << n << "!" << endl;
		}
		
		while(!cin.eof() && !isdigit(cin.peek())) cin.ignore();
		
	}

	return 0;
}
