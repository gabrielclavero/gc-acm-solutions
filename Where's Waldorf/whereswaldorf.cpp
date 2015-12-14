/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(void)
{
	int cases, m, n, k;
	int i, j;
	string::iterator it_s;
	
	
	cin >> cases;
	//ignoramos el \n
	//for(i=1; i<=2; i++) {
		while(cin.peek()!='\n') cin.ignore();
		cin.ignore();
	//}
	while(cases > 0) {
		//ignoramos la linea blanca (el \n no porque el ultimo output fue sacado con getline (que saca el \n) si estamos en la segunda iteracion o mas
		while(cin.peek()!='\n') cin.ignore();
			cin.ignore();
		
		cin >> m; cin >> n;
		char **grid = new char* [m];
		for(i=0; i<m; i++) 
			grid[i] = new char [n];
		
		for(i=0; i<m; i++) {
			for(j=0; j<n; j++)
				cin >> grid[i][j];
		}
		
		
		cin >> k;
		while(cin.peek()!='\n') cin.ignore();
		cin.ignore();
		
		string* words = new string [k];
		for(i=0; i<k; i++)
			getline(cin, words[i]);

		
		
		//SOLUCION
		int **res = new int* [k];
		for(i=0; i<k; i++)
			res[i] = new int [2];
		
		//vamos poniendo todas las letras de la grilla en uppercase, total, es lo mismo
		for(i=0; i<m; i++) {
			for(j=0; j<n; j++)
				grid[i][j] = toupper(grid[i][j]);
		}
		
		
		//compararemos las palabras con las 8 direcciones posibles en la grilla comenzando desde las 12 hasta las 11 por ahi, en direccion de las manecillas del reloj
		int length;
		int c;
		bool lo_encontre = false;
		for(int t=0; t<k; t++) {	//una iteracion por cada palabra a encontrar
			lo_encontre = false;
			length = words[t].size();
			c = 0;
			for(i=0; i<m; i++) {
				if(lo_encontre) break;
				//cout << "buscando a : " << words[t] << endl;
				for(j=0; j<n; j++) {
					c=0;
					if(grid[i][j] == toupper(words[t][c])) {		//si la primera letra es igual a la primera  de la palabra, comenzar a buscar en las 8 direcciones
						//vertical arriba
						if(i+1>=length) {
							c++;

							while(c<length) {
								//cout << grid[i-c][j] << endl;
								if(grid[i-c][j] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//diagonal arriba derecha
						c=0;
						if(i+1>=length && n-j>=length) {
							c++;
							while(c<length) {
								if(grid[i-c][j+c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//horizontal derecha
						c=0;
						if(n-j>=length) {
							c++;
							while(c<length) {
								if(grid[i][j+c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//diagonal abajo derecha
						c=0;
						if(m-i>=length && n-j>=length) {
							c++;
							while(c<length) {								
								if(grid[i+c][j+c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						
						//vertical abajo
						c=0;
						if(m-i>=length) {
							c++;
							while(c<length) {
								//cout << "letra: " << grid[i+c][j] << endl;
								if(grid[i+c][j] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//diagonal abajo izquierda
						c=0;
						if(m-i>=length && j+1>=length) {
							c++;
							while(c<length) {
								if(grid[i+c][j-c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//horizontal izquierda
						c=0;
						if(j+1>=length) {
							c++;
							while(c<length) {
								if(grid[i][j-c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
						//diagonal arriba izquierda
						c=0;
						if(i+1>=length && j+1>=length) {
							c++;
							while(c<length) {
								if(grid[i-c][j-c] != toupper(words[t][c])) break;
								else c++;
							}
						}
						if(c==length) { res[t][0] = i+1; res[t][1] = j+1; lo_encontre = true; break;  }
						
					}
				}
			}
		}
		
		//imprimir solucion
		for(i=0; i<k; i++)
			cout << res[i][0] << " " << res[i][1] << endl;
		
		if(cases > 1)
			cout << endl;
		
		
		//liberar memoria, pero no hace falta, es un programita ACM
		
		cases--;
	}
	
	return 0;
}
