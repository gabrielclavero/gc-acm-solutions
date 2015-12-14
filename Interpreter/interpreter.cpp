/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

int ram[1000];
int regs[10];
int i;

bool hay_espacios(string s)
{
	return (count(s.begin(), s.end(), ' ') > 0) || (count(s.begin(), s.end(), '\t') > 0);
}

void setear_regs(void)
{
	for(int i=0; i<10; i++)
		regs[i] = 0;
}
void setear_ram(void)
{
	for(int i=0; i<1000; i++)
		ram[i] = 0;
}

int ejecutar_comando(int comando, int d, int n, int j)
{
	j++;
	//cout << comando << " " << d << " " << n << " " << j << endl;
	switch(comando) {
		case 1:
			if(d == 0 && n == 0)	//el resto de numeros 1ab con a,b digitos != 0 no son instrucciones validas, solo datos comunes en ram
				j = -1;
			else
				j = -2;		//para indicar que no se ejecuto ninguna instruccion (solo habia un dato alli, no es normal mezclar datos en sector de codigo de programa pero supongo que asi es aca)
			break;
		case 2:
			regs[d] = n;
			break;
		case 3:
			regs[d] = (regs[d]+n) % 1000;
			break;
		case 4:
			regs[d] = (regs[d]*n) % 1000;
			break;
		case 5:
			regs[d] = regs[n];
			break;
		case 6:
			regs[d] = (regs[d] + regs[n]) % 1000;
			break;
		case 7:
			regs[d] = (regs[d]*regs[n]) % 1000;
			break;
		case 8:
			/*if(n < i) */
				regs[d] = ram[regs[n]];
			/*else
				regs[d] = 0;*/
			break;
		case 9:
			ram[regs[n]] = 	regs[d];
			break;
		case 0:
			if(regs[n] != 0) j = regs[d];
			break;
		default:
			j = j;
	}
	return j;
}

	
int main(void)
{
	int n, j, res;
	string s;
	stringstream ss(stringstream::in | stringstream::out);
	
	cin >> n;

	getline(cin, s);
	getline(cin, s); //la linea blanca que sigue al n
	/*leer contenido de la RAM*/
	while(n>0) {
		i = 0;
		setear_ram();
		if(s.size() > 0) { //si la linea blanca tenia espacios, ya los leimos y ahora leeremos el \n
			getline(cin, s);
		}
		getline(cin, s);	//leemos el numero
		while(!hay_espacios(s) && s.size() > 0)	{ /*asumimos que la blank line puede tener espacios, tabulaciones, o \n nomas*/
			/*convertir string a int*/
			ss.str(s);
			ss >> ram[i];
			/*fin de convertir string a int*/
			ss.clear(stringstream::goodbit);	//preparar al stream ss para el siguiente >>
			getline(cin, s);
			i++;
		}
		/*pos: hay i palabras de ram inicializadas en las direcciones 0,i-1, y desde i hasta 1000 estan en 000*/
	
		
		setear_regs();
		int tmp;
		j=0; res=0;	//res indica cantidad de comandos ejecutados, j indica la direccion del comando proximo a ejecutarse
		while(j!=-1) {
			tmp = ejecutar_comando((int) floor(ram[j]/100.0), (int) floor(ram[j]/10.0)%10, ram[j]%10, j);
			if(tmp!=-2) {
				res++;
				j = tmp;
			} else {
				j = j+1;
			}

		}
		cout << res << endl;
		n--;
		if(n!=0) cout << endl;
	}
	
	return 0;
}
