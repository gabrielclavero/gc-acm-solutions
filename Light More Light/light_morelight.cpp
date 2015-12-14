/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	unsigned long n, divisores;
	
	cin >> n;
	while(n !=0) {
		double tmp = sqrt((double) n);
		if(fabs(floor(tmp) - tmp) <= 0.0001 && (n % (int) tmp == 0))
		    cout << "yes" << endl;
		else
		    cout << "no" << endl;

		cin >> n;
	}

	return 0;
}
