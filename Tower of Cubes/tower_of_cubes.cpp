/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <queue>

using namespace std;

int cubes[500][6];
int grafo[500*6][500*6]; 
//los nodos del grafo son los cubos en cada una de las 6 posiciones diferentes
//grafo[i*6 + k] es el arreglo de vecinos del cubo i+1 con la cara k hacia arriba. k=0 significa que la front esta hacia arriba, luego back, left, rigt, top y bottom

int in_degree[500*6];

void topOrder(int n, int *a) 
{
	queue<int> zeroin;
	
	for(int i=0; i<n*6; i++)
		if(in_degree[i] == 0) zeroin.push(i);
		
	int j = 0;
	while(!zeroin.empty()) {
		int x = zeroin.front();
		zeroin.pop();
		a[j] = x;
		j++;
		for(int i=0; i<n*6; i++) {
			if(grafo[x][i]) {
				in_degree[i]--;
				if(in_degree[i] == 0) zeroin.push(i);
			}
		}
	}
}

int main(void)
{
	int n, n_case = 1;
	
	cin >> n;
	while(n != 0) {
		int n_c = n;
		while(n_c > 0) {
			for(int i=0; i<6; i++) 
				cin >> cubes[n-n_c][i];
			n_c--;
		}

		//Construir el grafo
		//primero reseteamos el grafo
		for(int i=0; i<500*6; i++)
			for(int j=0; j<500*6; j++)
				grafo[i][j] = 0;
		
		for(int i=0; i<500*6; i++)
			in_degree[i] = 0;
		
		//completar la matriz de adyacencia
		for(int i=n-1; i>0; i--) {
			for(int k=0; k<6; k++) {
				for(int j=i-1; j>=0; j--) {
					for(int h=0; h<6; h++) {
						if(cubes[j][h] == cubes[i][k]) {
							grafo[i*6 + k][j*6 + h + 1*((h+1)%2) + (-1)*(h%2) ] = 1;	//los nodos tienen en cuenta cuál cara esta hacia arriba. Ese truquito en la segunda indexacion es para manipular las caras del cubo cual va arriba y cual abajo
							in_degree[j*6 + h + 1*((h+1)%2) + (-1)*(h%2) ]++;
						}
					}
				}
			}
		}
	
		
		int *a = new int[n*6];
		
		topOrder(n, a);
		
		//doble arreglo, primera posicion: maxima distancia a ese nodo en el grafo, segunda posicion: cual es el nodo anterior en ese camino de maxima distancia hasta este nodo
		int **length_to = new int *[n*6];
		for(int i=0; i<n*6; i++) {
			length_to[i] = new int[2];
			length_to[i][0] = 0;
			length_to[i][1] = -1;
		}
		
		for(int i=0; i<n*6; i++) {
			for(int j=0; j<n*6; j++) {
				//cout << i << " " <<  j << " " << a[i] << endl;
				if(grafo[a[i]][j]) {
					if(length_to[j][0] <= length_to[a[i]][0] + 1)
						length_to[j][0] = length_to[a[i]][0] + 1;
						length_to[j][1] = a[i];
				}
			}
		}
		
		
		int max = 0;
		for(int i=1; i<n*6; i++) 
			if(length_to[i][0] > length_to[max][0])
				max = i;
		
		cout << "Case #" << n_case << endl;
		n_case++;
		cout << length_to[max][0] + 1 << endl;
		int i = max;
		while(1) {
			cout << i/6 + 1 << " ";
			switch(i%6) {
				case 0:
					cout << "front";
					break;
				case 1:
					cout << "back";
					break;
				case 2:
					cout << "left";
					break;
				case 3:
					cout << "right";
					break;
				case 4:
					cout << "top";
					break;
				case 5:
					cout << "bottom";
					break;
			}
			cout << endl;
			if(length_to[i][1] == -1) break;
			
			i = length_to[i][1];
		}
		
		cin >> n;
		if(n!=0) cout << endl;
	}
	return 0;	
}
