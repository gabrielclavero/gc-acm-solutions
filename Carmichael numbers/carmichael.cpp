/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <set>

using namespace std;

int pre[15];
int bounds[] = {3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767};

int main(void)
{
	int n, exp, i;
	unsigned long x;
	bool carmichael;
	set<int> primes;
	
	//leemos primero los numeros primos hasta 64999 de la consola (Estan en primes.txt)
	i = 1;
	while(!cin.eof()) {
		cin >> n;
		//cout << n << endl;
		primes.insert(n);
		i++;
	}
	cout << i << endl;
		

	for(int n=3; n<=64999; n++) {
		if(primes.find(n) != primes.end()) continue;
		carmichael = true;
		for(int a=2; a<n; a++) {
			x = a;  //a%n = a
			//n1 = n - (n%2);
			exp = 1;
			i = 0;
			while(exp*2 <= n) {
				x = (x*x) % n;
				pre[i] = x;
				exp *= 2;
				i++;
				//cout << x << endl;
			}
			while(exp < n) {
				int dif = n-exp;
				if(dif == 1) {
					x = (x*a) % n;
					exp = n;
				} else {
					i = 0;
					while(dif > bounds[i]) i++;
					if(i==0)
						exp = exp + 2;
					else
						exp = exp + (bounds[i] + 1) - (bounds[i-1] + 1);
					x = (x*pre[i]) % n;
				}
			}
			//cout << x << endl;
			if(x != a) {
				carmichael = false;
				break;
			}
		}
		//cout << n << endl;
		if(carmichael) cout << n << " carmichael" << endl;
		//else cout << "no carmichael" << endl;

		//cin >> n;
	}
	
	return 0;
}
