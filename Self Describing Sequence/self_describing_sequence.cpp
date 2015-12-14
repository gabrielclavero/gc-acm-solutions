/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAX = 700000;

int k = 1;
//int k_2 = 1;
int f[MAX];     //valores de f(k) calculado. El primero es f(1) = 1. Además los valores menores que k los podemos borrar
int pos = 1;        //primera posicion del numero a probar en la secuencia. Para i=1 la primera posicion es en 1
int f_ks;   //f_ks me indica hasta dónde se extiende el valor actual de f(k) para el k que estemos considerando

int f_rec(int n)
{
	int pos_tmp;
	while(1) {
		
		if(n > pos+f[k]-1) {  //caso en que el k considerado no es f(n)
			//pos_tmp = pos;
		    pos = pos+f[k];
		    
		    //k_2++;
		    k++;
		    if(k > f_ks) {
				
				f[k] = f[k-1]+1;
				f_ks = f_ks + f[f[k]];
			} else {
			    f[k] = f[k-1];
			}
			
		} else
		    return k;
	}
}

int main(void)
{
	int n = 2000000000;
	vector<int> cases;
	vector<int> backup;
	map<int, int> res;
	
	f[1] = 1;
	f_ks = 1;
	
	
	cin >> n;

	
	while(n!=0) {
		cases.push_back(n);
		backup.push_back(n);
		
		cin >> n;
	}
	sort(backup.begin(), backup.end());
	for(int i=0; i<backup.size(); i++)
		res.insert(pair<int, int>(backup[i], f_rec(backup[i])));

	for(int i=0; i<cases.size(); i++) {
		
	    cout << res[cases[i]] << endl;
	}

	
	return 0;
}
