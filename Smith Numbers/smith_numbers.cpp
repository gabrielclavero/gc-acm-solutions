/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> primos;

void prime_factorization(unsigned long x)
{
	unsigned long i, c;

   	primos.clear();
	c = x;
	while((c%2) == 0) {
		c = c/2;
		primos.push_back(2);
	}

	i = 3;
	while(i <= (sqrt(c)+1)) {
		if((c%i) == 0) {
			primos.push_back(i);
			c = c/i;
		} else {
		    i = i+2;
		}
	}

	if(c > 1)
		primos.push_back(c);
}

int suma_digitos(unsigned int n)
{
	int divisor = 1000000000;
	int suma = 0;
	while(divisor >= 1) {
		suma += n/divisor;        //division entera
		n = n%divisor;
		divisor /= 10;
	}
	return suma;
}

int main(void)
{
	unsigned int cases, n, suma_factores;
	
	cin >> cases;
	while(cases > 0) {
		cin >> n;
		
		bool smith = false;
		while(!smith) {
			n++;    //asumimos que lo vamos a encontrar antes de 2^32-1
			prime_factorization(n);
			if(primos.size() != 1) {    //n era primo si no se cumple esto
			    //suma de los factores
			    suma_factores = 0;
			    for(int i=0; i<primos.size(); i++)
					suma_factores += suma_digitos(primos[i]);


				if(suma_digitos(n) == suma_factores)
				    smith = true;
			}
		}
		cout << n << endl;
		
		cases--;
	}
	
	return 0;
}
