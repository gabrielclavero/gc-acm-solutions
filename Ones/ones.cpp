/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

int main(void)
{
	unsigned int long n, d, ones;

	while(!cin.eof()) {
		cin >> n;
		
		if(((n%2) == 0) || ((n%5) == 0))
		{
			//cout << 0 << endl;
			continue;
		}
		ones = 1;
		d = 1;
		while((d%n) != 0) {
			d = (d%n)*10 + 1;
			ones++;
		}
		cout << ones << endl;
		while(!isdigit(cin.peek()) && !cin.eof()) cin.ignore();
	}
		
	
	return 0;
}
