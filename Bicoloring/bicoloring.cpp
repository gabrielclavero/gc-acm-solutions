/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <queue>

using namespace std;

int vertices;

int grafo[200][200];
int colores[200];

typedef struct marcas {
	int ord[200];
	int cont;
} marcas;

void inicializar(marcas *mark)
{
	mark->cont = 0;
	for(int i=0; i<200; i++)
		mark->ord[i] = 0;
}

bool visitado(marcas *mark, int n)
{
	return mark->ord[n] != 0;
}

void visitar(marcas *mark, int n, int color)
{
	mark->cont += 1;
	mark->ord[n] = mark->cont;
	colores[n] = color;
}

void bfs(void)
{
	queue<int> q;
	marcas mark;
	int color = 1;
	
	inicializar(&mark);
	visitar(&mark, 0, color);
	q.push(0);
	
	//color = ((color+1) %3) + ((color+1)%2); //cuando cambio de nivel cambio el color con el que pinto a los vertices
	
	while(!q.empty()) {
		color = ((colores[q.front()]+1)%3) + ((colores[q.front()]+1)%2);
		for(int i=0; i<vertices; i++) {
			if(grafo[q.front()][i] == 1 && !visitado(&mark, i)) {
				visitar(&mark, i, color);
				q.push(i);
			}
		}
		q.pop();
	}
}

bool coloreo_propio(void)
{
	for(int i=0; i<vertices; i++) {
		for(int j=i+1; j<vertices; j++) {
			if(grafo[i][j] == 1 && colores[i] == colores[j]) return false;
		}
	}
	return true;
}

int main(void)
{
	int e, x, y;
	
	cin >> vertices;
	while(vertices != 0) {
		for(int i=0; i<200; i++)
		    for(int j=0; j<200; j++)
		        grafo[i][j] = 0;
		for(int i=0; i<200; i++) colores[i] = 0;

		cin >> e;
		
		while(e>0) {
			cin >> x >> y;
			grafo[x][y] = grafo[y][x] = 1;
			e--;
		}
		
		bfs();
		if(coloreo_propio())
		    cout << "BICOLORABLE." << endl;
		else
		    cout << "NOT BICOLORABLE." << endl;

		cin >> vertices;
	}

	return 0;
}
