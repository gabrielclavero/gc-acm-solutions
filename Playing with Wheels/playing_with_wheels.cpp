/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NODOS = 10000;

int grafo[NODOS][8];    //cada nodo tiene 8 vecinos (los que obtengo al apretar los botones) y hay 10000 vertices porque hay 10000 estados posibles de la maquina
int distancias[NODOS];

typedef struct marcas {
	int ord[NODOS];
	int cont;
} marcas;

void inicializar(marcas *mark)
{
	mark->cont = 0;
	for(int i=0; i<NODOS; i++)
		mark->ord[i] = 0;
}

bool visitado(marcas *mark, int n)
{
	return mark->ord[n] != 0;
}

void visitar(marcas *mark, int n, int distancia)
{
	mark->cont += 1;
	mark->ord[n] = mark->cont;
	distancias[n] = distancia;
}

void bfs(int nodo, int target)
{
	queue<int> q;
	marcas mark;
	int distancia = 0;

	inicializar(&mark);
	visitar(&mark, nodo, distancia);
	q.push(nodo);

	while(!q.empty()) {
		distancia = distancias[q.front()]+1;
		for(int i=0; i<8; i++) {
			if(grafo[q.front()][i] != -1 && !visitado(&mark, grafo[q.front()][i])) {
				visitar(&mark, grafo[q.front()][i], distancia);
				q.push(grafo[q.front()][i]);
				//cout << grafo[q.front()][i] << " " << distancia << endl;
				if(grafo[q.front()][i] == target) return;
			}
		}
		q.pop();
	}
}

void crear_grafo(void)
{
	int um, c, d, u, tmp;
	for(int i=0; i<NODOS; i++) {
		tmp = i;
		um = tmp/1000;
		tmp = tmp % 1000;
		c = tmp/100;
		tmp = tmp % 100;
		d = tmp/10;
		u = tmp%10;
		
		grafo[i][0] = ((um+1)%10)*1000 + c*100 + d*10 + u;
		grafo[i][1] = ((um+10-1)%10)*1000 + c*100 + d*10 + u;
		grafo[i][2] = um*1000 + ((c+1)%10)*100 + d*10 + u;
		grafo[i][3] = um*1000 + ((c+10-1)%10)*100 + d*10 + u;
		grafo[i][4] = um*1000 + c*100 + ((d+1)%10)*10 + u;
		grafo[i][5] = um*1000 + c*100 + ((d+10-1)%10)*10 + u;
		grafo[i][6] = um*1000 + c*100 + d*10 + ((u+1)%10);
		grafo[i][7] = um*1000 + c*100 + d*10 + ((u+10-1)%10);
	}
}

int main(void)
{
	int cases, initial, target, x, y, z, w, n;
	vector<int> forbidden;
	
	cin >> cases;
	while(cases > 0) {
		cin >> x >> y >> z >> w;
		initial = x*1000 + y*100 + z*10 + w;
		cin >> x >> y >> z >> w;
		target = x*1000 + y*100 + z*10 + w;

        crear_grafo();
        
        for(int i=0; i<NODOS; i++)
			distancias[i] = -1;

		forbidden.clear();
		cin >> n;
		while(n>0) {
			cin >> x >> y >> z >> w;
			forbidden.push_back(x*1000 + y*100 + z*10 + w);
			n--;
		}
		
		//borro del grafo los vecinos prohibidos, de ambas listas de adyacencia
		for(int i=0; i<forbidden.size(); i++) {
			for(int j=0; j<8; j++) {
				int vecino = grafo[forbidden[i]][j];
				for(int k =0; k<8; k++)
					if(grafo[vecino][k] == forbidden[i]) grafo[vecino][k] = -1;
                grafo[forbidden[i]][j] = -1;
			}
		}
		
		if(initial == target) {
			bool no_forb = true;
			for(int i=0; i<forbidden.size(); i++) {
				if(forbidden[i] == initial) {
					no_forb = false;
					break;
				}
			}
			if(no_forb)
				cout << 0 << endl;
			else
			    cout << -1 << endl;
		} else {
			bfs(initial, target);
			cout << distancias[target] << endl;
		}

		cases--;
	}

	return 0;
}
