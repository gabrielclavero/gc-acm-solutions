/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>

using namespace std;

double nodos[100][2];
bool intree[100];	//true si el iesimo nodo esta en el MST

double distancia(double x1, double y1, double x2, double y2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

//este prim va a devolver la suma de la longitud de todas las aristas en el MST
double prim(int n_vertices)
{
	double distancias[100];	//minima distancia al nodo i-esimo desde un nodo en el MST
	int ultimo = 0;	//ultimo nodo agregado al MST (minimum spanning tree)
	double suma_aristas = 0.0;
	
	for(int i=0; i<n_vertices; i++) {
		intree[i] = false;
		distancias[i] = -1.0;
	}
			
	intree[0] = true;
	
	int agregados = 1;
	
	while(agregados != n_vertices) {
		int minimo = -1;
		for(int i=0; i<n_vertices; i++) {
			if(intree[i]) continue;
			
			double dist_tmp = distancia(nodos[ultimo][0], nodos[ultimo][1], nodos[i][0], nodos[i][1]);
			if(distancias[i] == -1)
				distancias[i] = dist_tmp;
			else if(dist_tmp < distancias[i])
				distancias[i] = dist_tmp;
				
			if(minimo == -1 || distancias[minimo] > distancias[i]) minimo = i;
		}
		
		intree[minimo] = true;
		agregados++;
		ultimo = minimo;
		suma_aristas += distancias[minimo];
	}
	
	return suma_aristas;
}

int main(void)
{
	int cases, n;
	
	cout.setf(ios::fixed);//necesario para que precision sea la cantidad de digitos decimales DESPUES de la coma
	cout.precision(2);
	
	cin >> cases;
	while(cases > 0) {
		cin >> n;
		int n_vertices = n;
		while(n>0) {
			for(int i=0; i<2; i++)
				cin >> nodos[n_vertices-n][i];
			n--;
		}
		
		
		cout << prim(n_vertices) << endl;
		
		cases--;
		if(cases > 0) cout << endl;
	}
	
	return 0;
}
