/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <string>
#include <iostream>
#include <ctime>
#include <queue>

using namespace std;

const int HDIV = 533879;

struct Elem
{
	string s;
	struct Elem *next;
	int ind;
};

typedef struct List
{
	struct Elem *first;
} List;

List hash_table[HDIV];
string diccionario[25000];
int *grafo[25000];

int in_degree[25000];

inline int f(const string &s)
{
	int hash = 0;
	for(int i=0; i<s.length(); i++) {
		hash = hash*31 + s[i] - 'a';
		if(hash >= HDIV) hash %= HDIV;
	}
	return hash;
}

void topOrder(int n, int *a)
{
	queue<int> q;
	for(int i=0; i<n; i++)
	    if(in_degree[i] == 0) q.push(i);

	int j=0;
	while(!q.empty()) {
		a[j] = q.front();
		j++;
		for(int i=1; i<=grafo[q.front()][0]; i++) {
			in_degree[grafo[q.front()][i]] -= 1;
			if(in_degree[grafo[q.front()][i]] == 0) q.push(grafo[q.front()][i]);
			
		}
		q.pop();
	}


}

int main(void)
{
	int i;
	char c;
	
	for(i=0; i<HDIV; i++)
		hash_table[i].first = NULL;
		
	for(i=0; i<25000; i++)
	    in_degree[i] = 0;
		

	clock_t time = clock();
	
	int j = 0;
	//while(j<25000) {
	while(!cin.eof()) {
		cin >> diccionario[j];
		
		struct Elem *e = new struct Elem;
		e->s = diccionario[j];
		e->ind = j;
		e->next = NULL;
		
		int tmp = f(diccionario[j]);
		if(hash_table[tmp].first == NULL)
			hash_table[tmp].first = e;
		else {
			e->next = hash_table[tmp].first;
			hash_table[tmp].first = e;
		}
		
		j++;
	}

	/*for(i=0; i<j; i++)
	    cout << diccionario[i] << endl;*/

	struct Elem *p;
	int n = j;
	int vecinos[900];
	for(i=0; i<n; i++) {
		int k = 0;
		for(j=0; j<diccionario[i].length(); j++) {  //vecinos borrando una letra
			string tmp = diccionario[i];
			tmp.erase(j, 1);
			if(tmp > diccionario[i]) {          //solo es vecino si está despues que esta palabra en el orden lexicografico
				p = hash_table[f(tmp)].first;
				while(p != NULL) {
					if(p->s == tmp)
				    	break;
					else
				    	p = p->next;
				}
				if(p != NULL) {
			    	vecinos[k] = p->ind;
			    	k++;
			    	in_degree[p->ind] += 1;
				}
			}
		}
		
		for(j=0; j<diccionario[i].length(); j++) {  //vecinos cambiando una letra
		    string tmp = diccionario[i];
		    for(char c='a'; c != 'z'+1; c++) {
			    //if(diccionario[i][j] == c) continue;
			    tmp[j] = c;
			    if(tmp > diccionario[i]) {          //solo es vecino si está despues que esta palabra en el orden lexicografico
					p = hash_table[f(tmp)].first;
					while(p != NULL) {
						if(p->s == tmp)
				    		break;
						else
				    		p = p->next;
					}
					if(p != NULL) {
			    		vecinos[k] = p->ind;
			    		k++;
			    		in_degree[p->ind] += 1;
					}
				}
			}
		}

		for(j=0; j<=diccionario[i].length(); j++) {
            string tmp = diccionario[i].substr(0, j) + 'a' + diccionario[i].substr(j, diccionario[i].length());
			for(char c='a'; c != 'z'+1; c++) {
				tmp[j] = c;
				if(tmp > diccionario[i]) {
                	p = hash_table[f(tmp)].first;
                	while(p != NULL) {
						if(p->s == tmp)
				    		break;
						else
				    		p = p->next;
					}
					if(p != NULL) {
			    		vecinos[k] = p->ind;
			    		k++;
			    		in_degree[p->ind] += 1;
					}
				}
			}
		}
		
		
		if(k!=0) {
   			grafo[i] = new int[k+1];
			grafo[i][0] = k;            //cantidad de vecinos primero
			for(int v=1; v<=k; v++)
			    grafo[i][v] = vecinos[v-1];
		} else {
            grafo[i] = new int[1];
            grafo[i][0] = 0;
		}
		
		/*cout << "vecinos de " << diccionario[i] << endl;
		for(int v=1; v<=k; v++)
		    cout << diccionario[grafo[i][v]] << " ";
		cout << endl;*/
	}
	
	//ya tenemos el grafo armado, ahora usando topological sorting buscaremos el longest path en este grafo (el cual es un DAG)
	int *a = new int[n];
	topOrder(n, a);
	
	/*for(int i=0; i<n; i++) cout << a[i] << " ";
	cout << endl;*/

	int *length_to = new int[n];
	for(int i=0; i<n; i++) length_to[i] = 0;

	for(int i=0; i<n; i++) {
		for(int j=1; j<=grafo[a[i]][0]; j++) {
			if(length_to[ grafo[a[i]][j] ] <= length_to[a[i]] + 1)
				length_to[ grafo[a[i]][j] ] = length_to[a[i]] + 1;
		}
	}
	
	int res = length_to[0];
	for(int i=1; i<n; i++)
	    if(length_to[i] > res) res = length_to[i];
	
	cout << res+1 << endl;




	return 0;
}
