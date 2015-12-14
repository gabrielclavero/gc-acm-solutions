/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>

using namespace std;

template<std::size_t N, std::size_t M>
void minimal_cost(int (&m)[N][M], const vector<int> &c, const int left, const int right)
{
	int min = c.back() * c.size();
	for(int i=left+1; i<right; ++i) {
		int cost_for_this_slice = (c[right] - c[left]) + m[c[left]][c[i]] + m[c[i]][c[right]];
		min = cost_for_this_slice < min ? cost_for_this_slice : min;
	}

	m[c[left]][c[right]] = min;

	return;
}

int m[1000][1000]; //m[i][j] = costo de la mejor solución entre i y j. Es decir entre las posiciones i y j en la madera. 

int main()
{
	int l, n, tmp;
	vector<int> c;

	

	cin >> l;
	while(l != 0) {
		cin >> n;
		c.clear();

		c.push_back(0);

		while(n > 0) {
			cin >> tmp;
			c.push_back(tmp);
			--n;
		}

		c.push_back(l);

		if(c.size() == 2) {
			cout << "The minimum cutting is 0." << endl;
		} else if(c.size() == 3) {
			cout << "The minimum cutting is " << l << "." << endl;
		} else {

			//inicializar
			for(int i=0; i<1000; ++i) {
				for(int j=0; j<1000; ++j) {
					m[i][j] = -1;
				}
			}

			//los que yo puedo completar fácil son las posiciones entre las cuales hay 0 cortes, por ejemplo si tengo que 
			//cortar en posicion 6 y en posicion 10 y ninguna en el medio, entonces m[6][10] = 0
			for(int i=1; i<c.size(); ++i) {
				m[c[i-1]][c[i]] = 0;
			}

			//otro costo que puedo calcular rápidamente es el costo entre dos posiciones que tienen sólo un corte en el medio. 
			//El costo en este caso es la distancia que hay entre ambas posiciones.
			for(int i=2; i<c.size(); ++i) {
				m[c[i-2]][c[i]] = c[i] - c[i-2];
			}

			//calcular el resto con programación dinámica. Calcular  primero costos entre zonas que tienen dos cortes posibles en el medio, después 3, y así hasta terminar
			for(int b=2; b<c.size(); ++b) {	//b de brecha
				for(int i=b+1; i<c.size(); ++i) {
					minimal_cost(m, c, i - b - 1, i);
				}
			}

			cout << "The minimum cutting is " << m[0][l] << "." << endl;


		}

		cin >> l;
	}


	return 0;
}

