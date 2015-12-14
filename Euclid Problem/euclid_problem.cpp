/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

long gcd(long p, long q, long *x, long *y)
{
	long x1, y1;
	long g;
	
	if(q > p) return(gcd(q,p,y,x));
	
	if(q == 0) {
		*x = 1;
		*y = 0;
		return p;
	}
	
	g = gcd(q, p%q, &x1, &y1);
	
	*x = y1;
	*y = (x1 - (long) floor(p/q)*y1);
	
	return g;
}

int main(void)
{
	long a, b, x, y;
	
	cin >> a; cin >> b;
	while(!cin.eof()) {
		//cin.ignore();
		
		long g = gcd(a, b, &x, &y);
		cout << x << " " << y << " " << g << endl;
		
		
		cin >> a; cin >> b;
		//cout << a << b << endl;
	}
	
	return 0;
}
