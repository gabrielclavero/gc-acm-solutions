/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>

using namespace std;

int beads[2000];

typedef struct Elem {
	int valor;
	Elem *next;
	
	Elem()
	{
		next = NULL;
	}
} Elem;

typedef struct List {
	Elem *first;
	
	List() 
	{
		first = NULL;
	}
} List;

List *grafo[51];
int valencias[51];

void construir_grafo(int n_beads)
{
	for(int i=0; i<51; i++) {
		if(grafo[i] != NULL) delete grafo[i];
		valencias[i] = 0;
	}
		

	for(int i=0; i<51; i++)
		grafo[i] = new List;
	
	for(int i=0; i<n_beads*2; i+=2) {
		//if(beads[i] == beads[i+1]) continue;
		Elem *e = new Elem;
		e->valor = beads[i+1];
		if(grafo[beads[i]]->first == NULL)
			grafo[beads[i]]->first = e;
		else {
			Elem *tmp = grafo[beads[i]]->first;
			while(tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = e;
		}
		valencias[beads[i]] += 1;
		
		//if(beads[i] != beads[i+1]) continue;
		Elem *e2 = new Elem;
		e2->valor = beads[i];
		if(grafo[beads[i+1]]->first == NULL)
			grafo[beads[i+1]]->first = e2;
		else {
			Elem *tmp = grafo[beads[i+1]]->first;
			while(tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = e2;
		}
		valencias[beads[i+1]] += 1;
	}
}

List *tour = NULL;


void find_tour(int u)
{
	//cout << u << endl;
	Elem *e = grafo[u]->first;
	Elem *tmp;
	while(e != NULL) {
		grafo[u]->first = grafo[u]->first->next;
		valencias[u]--;
		
		Elem *e2 = grafo[e->valor]->first;
		if(e2->valor == u)
			grafo[e->valor]->first = grafo[e->valor]->first->next;
		else {
			while(e2->next->valor != u)
				e2 = e2->next;
			tmp = e2->next;
			e2->next = e2->next->next;
			delete tmp;
		}
		valencias[e->valor]--;
		find_tour(e->valor);
		tmp = e;
		if(valencias[u] > 0)
			e = e->next;
		else
			e = NULL;
		delete tmp;
	}
	Elem *nuevo = new Elem;
	nuevo->valor = u; 
	nuevo->next = tour->first;
	tour->first = nuevo;
		
	//cout <<"salimos de " << u << endl;
}

int main(void)
{
	int t, n, n_beads, n_case = 1;

	for(int i=0; i<51; i++) grafo[i] = NULL;
	
	cin >> t;
	while(t > 0) {
		cin >> n;
		
		n_beads = n;
		n *= 2;
		while(n > 0) {
			cin >> beads[n_beads*2-n];
			n--;
		}
		
		//construir grafo en donde los vertices son los colores y las aristas son los beads
		construir_grafo(n_beads);
		
		
		bool flag = true;
		for(int i=1; i<51; i++) {
			if((valencias[i] % 2) != 0) {
				flag = false;
				break;
			}
		}
		if(!flag) {
			cout << "Case #" << n_case << endl;
			cout << "some beads may be lost" << endl;
		} else {
			//encontrar ciclo euleriano
			if(tour != NULL)
				delete tour;
			tour = NULL;
			tour = new List;
			find_tour(beads[0]);
			cout << "Case #" << n_case << endl;
			Elem *e = tour->first;
			int p = e->valor;
			int last;
			while(e->next != NULL) {
				cout << e->valor << " " << e->next->valor << endl;
				last = e->next->valor;
				e = e->next;
			}
			//cout << p << " " << last << endl;
		}
		
		n_case++;
		t--;
		if(t>0) cout << endl;
	}
	return 0;
}
