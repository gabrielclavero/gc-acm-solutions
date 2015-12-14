/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

int factorial(int x)
{
	int i = 2;
	int res = 1;
	if(x<=1) return res;
	
	while(i<=x) {
		res *= i;
		i++;
	}
	
	return res;
}

int combinatorial(int n1, int n2)
{
	return (factorial(n1)/(factorial(n2)*factorial(n1-n2)));
}

int main(void)
{
	int n, k, i, tmp;
	vector<int> xs;
	
	while(!cin.eof()) {
		cin >> n; cin >> k;
		i = k;
		while(i>0) {
			cin >> tmp;
			xs.push_back(tmp);
			i--;
		}
		
		
		int res = 1;
		int disp = 0;   //cantidad de posiciones disponibles de los n factores (x1 + .... + xk)*(x1 + .... + xk)*....*(x1 + .... + xk)
		for(i=0; i<xs.size(); i++) {
			res *= combinatorial(n-disp, xs[i]);
			disp += xs[i];
		}

		cout << res << endl;
		xs.clear();
		
		while(!isdigit(cin.peek()) && !cin.eof()) cin.ignore();
	}
	
	//cout << combinatorial(10, 5) << endl;
	
	return 0;
}
