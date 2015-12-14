/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


char caracter_izq(char c);
char rows[] = {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};

int main(void)
{
	vector<string> input;
	vector<string>::iterator it;
	string::iterator it_s;
	
	string tmp;
	
	while(!cin.eof()) {
		getline(cin, tmp);
		input.push_back(tmp);
	}
	
	
	for(it=input.begin(); it!=input.end(); it++) {
		for(it_s=it->begin(); it_s!=it->end(); it_s++)
			cout << caracter_izq(*it_s);
		
		if(it!=input.end()-1) cout << endl;
	}
	return 0;
}

char caracter_izq(char c)
{
	if(c==' ') return c;

	for(int i=1; i<47; i++) {
		if(rows[i]==c) return rows[i-1];
	}
	return 0;
}
