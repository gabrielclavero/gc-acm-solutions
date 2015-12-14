/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <ctime>

using namespace std;

int n,k;
int a[257];
int sol[2][8][64];


//se fija si los alfiles en a[1..i] no se están atacando
//pre: los alfiles en 1..i-1 no se estan atacando
bool no_attackings(int i)
{
	int tmp1, tmp2;
	tmp1 = (a[i]-1)/n;
	for(int c=1; c<i; c++) {
        //if(a[c] == 4 && a[i]==9) cout << tmp1 << " " << tmp2 << endl;
		tmp2 = (a[c]-1)/n;
		if(a[i] == a[c]+ n*(tmp1 - tmp2)+(tmp1 - tmp2)) return false;   //diagonal hacia la izquierda
		if(a[i] == a[c] + n*(tmp1 - tmp2)-(tmp1 - tmp2) && (a[i]>n)) return false;
		
		
	}
	return true;
}

//tengo que agregar i alfiles
//voy por el j-ésimo
//casilleros: casilleros libres. Es en formato bit
//bool blancas: si es que estoy poniendo los alfiles blancos o los negros
int backtrack(int i, int j, long long casilleros, int blancas)
{
	if(i>0 && j == 1 && sol[blancas][n-1][i-1] != -1)
	    return sol[blancas][n-1][i-1];


	int respuesta = 0;
	
	if(j<=i) {
		for(int c=a[j-1]+1; c<=n*n-(i-j); c++) {    //vamos hasta n*n -(k-i) porque necesitamos agregar k-i alfiles despues de este
		
		    //veamos si el casillero en el que estoy es del tablero que me interesa
		    if(n % 2 == 0) {
		    	if(blancas) {
					if(((c-1)/n) % 2 == 0) {
						if(c % 2 == 1)
					    continue;
					} else {
						if(c%2 == 0)
						    continue;
					}
				} else {
                	if(((c-1)/n) % 2 == 0) {
						if(c % 2 == 0)
						    continue;
					} else {
						if(c%2 == 1)
					  	  continue;
					}
				}
			} else {
				if(blancas && n%2 == 0) continue;
				if(!blancas && n%2 == 1) continue;
			}
		    
		
			if(! (casilleros & ((long long)1<<(long long)(c-1))) ) {  //si el casillero está libre
				a[j] = c;

				long long tmp = casilleros;
				for(int h=1; h<=n-( (c-1)/n +1); h++) {   //desde la fila siguiente al casillero que acabamos de ocupar hasta la ultima fila, vamos a marcar los casilleros de las diagonales de abajo como no disponibles
				    int cas_der = c+h*n+h;
				    int cas_izq = c+h*n-h;
				    if((cas_der-1)/n == h+(c-1)/n)  //no nos tenemos que haber pasado de fila
						tmp = tmp | ((long long)1<<(long long)(cas_der-1));
				    if((cas_izq-1)/n == h+(c-1)/n)
						tmp = tmp | ((long long)1<<(long long)(cas_izq-1));
				}
				respuesta += backtrack(i, j+1, tmp, blancas);
			}
		}
	} else {
        /*if(j == 1)
	     	sol[blancas][n-1][i-1] = 1;*/
		return 1;

	}
	if(j == 1)
	     sol[blancas][n-1][i-1] = respuesta;
	return respuesta;
}

int main(void)
{
	int soluciones;
	int res[8][64];
	
	for(int i=0; i<8; i++)
	    for(int j=0; j<64; j++)
	        res[i][j] = -1;
	
	a[0] = 0;
	cin >> n >> k;
	
	for(int i=0; i<2; i++)
		for(int j=0; j<8; j++)
			for(int h=0; h<64; h++)
			    sol[i][j][h] = -1;

	clock_t tiempo = clock();

	while(n!=0 || k!=0) {
		soluciones = 0;
       	if(k>0) {
			if(res[n-1][k-1] == -1) {
				for(int i=k; i>=0; i--)
					soluciones += backtrack(i, 1, 0, 1)*backtrack(k-i, 1, 0, 0);
				res[n-1][k-1] = soluciones;
			}
			cout << res[n-1][k-1] << endl;
		} else {
		    cout << 1 << endl;
		}
		
        cin >> n >> k;
	}

	return 0;
}
