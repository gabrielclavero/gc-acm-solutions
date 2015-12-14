/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool es_palindromo(unsigned long p);

int main(void)
{
	int n, its;
	unsigned long p, p2;
	stringstream ss(stringstream::in | stringstream::out);
	string tmp;
	
	cin >> n;
	
	while(n>0) {
		cin >> p;
		ss << p;
		//cout << p << " " << ss.str() << endl;
		tmp = ss.str();
		reverse(tmp.begin(), tmp.end());
		//cout << tmp << endl;
		ss.str(tmp);
		ss >> p2;
		ss.clear(stringstream::goodbit);
		p = p+p2;
		
		its = 1;

		while(!es_palindromo(p)) {
			//cout << p << " " << p2 << endl;
			its++;
			ss << p;
			tmp = ss.str();
			reverse(tmp.begin(), tmp.end());
			ss.str(tmp);
			ss >> p2;
			ss.clear(stringstream::goodbit);
			p = p+p2;
		}
		cout << its << " " << p << endl;
		tmp.clear();
		ss.str(tmp);
		//cout << ss.str() << endl;
		n--;
	}
	
	return 0;
}

bool es_palindromo(unsigned long p)
{
	stringstream ss(stringstream::in | stringstream::out);
	string tmp;
	
	ss << p;
	tmp = ss.str();
	
	for(int i=0; i<=tmp.length()-1; i++) {
		if(tmp[i] != tmp[tmp.length()-1-i]) return false;
	}
	return true;
}
