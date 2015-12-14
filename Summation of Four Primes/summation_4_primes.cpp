/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>

using namespace std;

bool is_prime(unsigned long x)
{
	unsigned long i, c;

	if(x < 2) return false;

	c = x;
	while((c%2) == 0) {
		if(x != 2)
		    return false;
		else
		    return true;
		c = c/2;
	}

	i = 3;
	double tmp = sqrt(c);
	while(i <= tmp+1) {
		if((c%i) == 0) {
			if(x != i) return false;
			else return true;
			c = c/i;
			tmp = sqrt(c);
		} else {
		    i = i+2;
		}
	}

	if(c != x)
		return false;
	else
	    return true;
}

int main(void)
{

	int n;
	
	while(!cin.eof()) {
		cin >> n;
		
		if(n<8)  //8 es el menor n tal que puede ser escrito con 4 primos
			cout << "Impossible." << endl;
		else {
			if(n%2 == 0) {
			    cout << "2 2 ";
			    n = n-4;
			} else {
			    cout << "2 3 ";
			    n = n-5;
			}
			//ahora solo tengo que ver la forma de escribir n con 2 numeros primos. La conjetur de Goldbach me dice que se puede, pues n es par
			for(int i=2; i<=10000000; i++) {
				if(is_prime(i) && is_prime(n-i)) {
				    cout << i << " " << n-i << endl;
				    break;
				}
			}
		}
		while(!cin.eof() && !isdigit(cin.peek())) cin.ignore();
	}
	
	
	return 0;
}
