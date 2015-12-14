/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>

using namespace std;

int f[14][14][14];  //f[i][n][p] = cantidad de maneras de formar una fila de i personas teniendo n personas a escoger y tal que p personas tengan la vista libre hacia el frente

void llenar_tabla()
{
	for(int i=0; i<=13; i++) {
	    for(int j=0; j<=13; j++) {
			for(int k=0; k<=13; k++) {
				if(i==1 && k==1) f[i][j][k] = j;
				else f[i][j][k] = 0;
			}
		}
	}

	//con 0 personas en la fila
	for(int j=0; j<=13; j++) {
		for(int k=0; k<=13; k++) {
			if(k == 0) f[0][j][k] = 1;
			else f[0][j][k] = 0;
		}
	}
	
	//con 1 persona en la fila
	for(int j=0; j<=13; j++) {
		for(int k=0; k<=13; k++) {
			if(k==1) f[1][j][k] = j;
			else f[1][j][k] = 0;
		}
	}
	
	//en p=1 es una persona con la vista sin bloquear (siempre es la del primer lugar, este es un caso especial)
	for(int n=2; n<=13; n++) {
	    for(int m=n; m<=13; m++) {
			for(int p=1; p<=n; p++) {
				int tmp = 0;
				if(p == 1) {
					tmp = f[n][m-1][1];    //todas las formas de construir esas filas sin usar al tipo mas alto
					for(int x=0; x<=n-1; x++) //ahora sumamos las que sí lo usan (como p=1, el unico lugar donde puede estar este tipo es en el primer lugar)
						tmp += f[n-1][m-1][x];
							
					f[n][m][p] = tmp;
				} else {
					tmp = f[n][m-1][p];     //todas las formas de construir filas de long. n y con p tipos que tienen vision no bloqueada y sin usar al tipo mas alto
					//ahora sumamos las filas que sí usan al tipo mas alto. Este puede estar inicialmente en cualquiera de los n lugares, pero según el valor de p podemos descartar casos.
					//Ademas recordá que el tipo mas alto tiene la vision no bloqueada donde sea que se ubique y que solo las personas que estan paradas delante de el tienen posibilidades de no estar bloqueadas
					for(int i=p; i<=n; i++) {   //el i es el indice de la posicion en la fila del tipo mas alto
						int tmp2 = 0;
						for(int x=0; x<=n-i; x++)
							tmp2 += f[n-i][m-i][x];
						tmp += f[i-1][m-1][p-1]*tmp2;
					}
					f[n][m][p] = tmp;
				}
			}
		}
	}
	
}
				



int main(void)
{
	int t, n, p, r;
	
	llenar_tabla();
	
	cin >> t;
	while(t>0) {
		cin >> n >> p >> r;
		
		int res = 0;
		for(int i=p; i<=n+1-r; i++)
			res += f[i-1][n-1][p-1] * f[n-i][n-i][r-1];

		cout << res << endl;
		
		//cout << f[n][p][r] << endl;
		
		t--;
	}
	return 0;
}
