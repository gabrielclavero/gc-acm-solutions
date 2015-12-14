/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

char board[9][9];

struct rey
{
	int i;
	int j;
};
typedef struct rey rey;

//devuelve true si no hay piezas entre los casilleros (i1, j1), (i2, j2) en la fila o columna, segun lo que comparten (indicado por bool fila)
bool no_hay_piezas_straight(int i1, int j1, int i2, int j2, bool fila)
{
	bool res = true;
	if(fila) {
		for(int j=min(j1, j2)+1; j<max(j1, j2); j++) {
			if(board[i1][j] != '.') { res = false; break; }
		}
	} else {
		for(int i=min(i1, i2)+1; i<max(i1, i2); i++) {
			if(board[i][j1] != '.') { res = false; break; }
		}
	}
	return res;
}

bool no_hay_piezas_diag(int i1, int j1, int i2, int j2, bool subida)
{
	bool res = true;
	int i, j;
	if(i1 > i2) {
		i = i1;
		j = j1;
	} else {
		i = i2;
		j = j2;
	}
	if(subida) {
		i--;
		j++;
		while(i>min(i1, i2)) {
			if(board[i][j] != '.') { res = false; break; }
			i--;
			j++;
		}
	} else {
		i--;
		j--;
		while(i>min(i1, i2)) {
			//cout << board[i][j] << endl;
			if(board[i][j] != '.') { res = false; break; }
			i--;
			j--;
		}
	}
	return res;
}
	
int main(void)
{
	int i, j;
	long n = 1;
	rey rey_blanco;
	rey rey_negro;
	bool jaque_blanco, jaque_negro;
	bool seguir = false;
	
	while(1) {
		seguir = false;
		for(i=1; i<=8; i++)
			cin >> &(board[i][1]);
			
		
		//chequear si es el ultimo tablero	
		for(i=1; i<=8; i++) {
			for(j=1; j<=8; j++) {
				if(board[i][j] != '.') {
					seguir = true;
					break;
				}
			}
			if(seguir) break;
		}
		if(!seguir) return 0;
		
		//capturar posiciones de los reyes
		for(i=1; i<=8; i++) {
			for(j=1; j<=8; j++) {
				if(board[i][j] == 'k') {
					rey_negro.i = i;
					rey_negro.j = j;
				} else if(board[i][j] == 'K') {
					rey_blanco.i = i;
					rey_blanco.j = j;
				}
			}
		}
		
		//jaque al rey blanco
		jaque_blanco = false;
		for(i=1; i<=8; i++) {
			for(j=1; j<=8; j++) {
				switch(board[i][j]) {
					case 'p':
						if(rey_blanco.i == (i+1) && (rey_blanco.j == (j+1) || rey_blanco.j == (j-1)))
							jaque_blanco = true;
						break;
					case 'r':
						if(rey_blanco.i == i && no_hay_piezas_straight(rey_blanco.i, rey_blanco.j, i, j, true)) {
							jaque_blanco = true;
						} else if(rey_blanco.j == j && no_hay_piezas_straight(rey_blanco.i, rey_blanco.j, i, j, false)) {
							jaque_blanco = true;
						}	
						break;
					case 'n': 
						if( ((rey_blanco.i == i-1 || rey_blanco.i == i+1) && (rey_blanco.j == j-2 || rey_blanco.j == j+2)) ||
							((rey_blanco.i == i-2 || rey_blanco.i == i+2)  && (rey_blanco.j == j-1 || rey_blanco.j == j+1))
						) {
							jaque_blanco = true;
						}
						break;
					case 'b':
						if((rey_blanco.i + rey_blanco.j == i + j) && no_hay_piezas_diag(rey_blanco.i, rey_blanco.j, i, j, true)) {
							jaque_blanco = true;
						} else if((rey_blanco.i - rey_blanco.j == i-j) && no_hay_piezas_diag(rey_blanco.i, rey_blanco.j, i, j, false)) {
							jaque_blanco = true;
						}
						break;
					case 'q':
						if((rey_blanco.i + rey_blanco.j == i + j && no_hay_piezas_diag(rey_blanco.i, rey_blanco.j, i, j, true)) || (rey_blanco.i - rey_blanco.j == i-j  && no_hay_piezas_diag(rey_blanco.i, rey_blanco.j, i, j, false)) ||
							(rey_blanco.i == i && no_hay_piezas_straight(rey_blanco.i, rey_blanco.j, i, j, true)) || (rey_blanco.j == j && no_hay_piezas_straight(rey_blanco.i, rey_blanco.j, i, j, false)))
						{
							jaque_blanco = true;
						}
						break;
					default :	//'.' o piezas blancas
						continue;
				}
			}
		}
			
		jaque_negro = false;
		for(i=1; i<=8; i++) {
			for(j=1; j<=8; j++) {
				switch(board[i][j]) {
					case 'P':	//este caso es el unico distinto entre rey blanco y rey negro
						if(rey_negro.i == (i-1) && (rey_negro.j == (j+1) || rey_negro.j == (j-1)))
							jaque_negro = true;
						break;
					case 'R':
						if(rey_negro.i == i && no_hay_piezas_straight(rey_negro.i, rey_negro.j, i, j, true)) {
							jaque_negro = true;
						} else if(rey_negro.j == j && no_hay_piezas_straight(rey_negro.i, rey_negro.j, i, j, false)) {
							jaque_negro = true;
						}
						break;
					case 'N': 
						if( ((rey_negro.i == i-1 || rey_negro.i == i+1) && (rey_negro.j == j-2 || rey_negro.j == j+2)) ||
							((rey_negro.i == i-2 || rey_negro.i == i+2)  && (rey_negro.j == j-1 || rey_negro.j == j+1))
						) {
							jaque_negro = true;
						}
						break;
					case 'B':
						if((rey_negro.i + rey_negro.j == i + j) && no_hay_piezas_diag(rey_negro.i, rey_negro.j, i, j, true)) {
							jaque_negro = true;
						} else if((rey_negro.i - rey_negro.j == i-j) && no_hay_piezas_diag(rey_negro.i, rey_negro.j, i, j, false)) {
							jaque_negro = true;
						}
						break;
					case 'Q':
						if((rey_negro.i + rey_negro.j == i + j && no_hay_piezas_diag(rey_negro.i, rey_negro.j, i, j, true)) || (rey_negro.i - rey_negro.j == i-j  && no_hay_piezas_diag(rey_negro.i, rey_negro.j, i, j, false)) ||
							(rey_negro.i == i && no_hay_piezas_straight(rey_negro.i, rey_negro.j, i, j, true)) || (rey_negro.j == j && no_hay_piezas_straight(rey_negro.i, rey_negro.j, i, j, false)))
						{
							jaque_negro = true;
						}
						break;
					default :
						continue;
				}
			}
		}
					
		if(jaque_negro)
			cout << "Game #" << n << ": black king is in check." << endl;
		else if(jaque_blanco)
			cout << "Game #" << n << ": white king is in check." << endl;
		else
			cout << "Game #" << n << ": no king is in check." << endl;
		n++;
	}
	
	return 0;
}
