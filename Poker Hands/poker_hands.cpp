/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <stack>
#include <cstdlib>
#include <cctype>

using namespace std;

/*Este programa mantiene una jerarquía de valores enteros para cada mano y los almacena en una pila, por eso
si ambos jugadores tienen un poker por ej, entonces ambos tendrán a 21 en el tope de la pila, así que los
desempatamos buscando el segundo valor de la pila que en el caso del poker es el valor de una de las 4 cartas
del poker, y así vamos comparando tratando de desempatar hasta que uno gane o las pilas se vacíen (empate)*/

const int STRAIGHT_FLUSH = 22;
const int POKER = 21;
const int FULL = 20;
const int FLUSH = 19;
const int STRAIGHT = 18;
const int PIERNA = 17;
const int DOBLE_PAR = 16;
const int PAR = 15;

//para qsort
int compare(const void *, const void *);

int compare (const void *a, const void *b)
{
	if(*(int *)a > *(int *)b)
		return 1;
	else if(*(int *)a < *(int *)b)
		return -1;
	else
		return 0;
}

stack<int> valor_mano(int values[], char suits[])
{
	int i;
	bool flush = true;
	bool tmp = true;	//para evaluar qué partida tenemos
	stack<int> res;
	
	for(i=0; i<4; i++)
		flush = flush && (suits[i]==suits[i+1]);	//tambien podríamos comparar el primero con todos

	//ordenar el arreglo de valores de las cartas nos facilitará la tarea de encontrar qué mano tenemos, por ej en el caso de tener poker las cuatro cartas iguales estarán al comienzo o al final del arreglo
	qsort(values, 5, sizeof(int), compare);
	
	//escalera real
	if(flush) {
		for(i=0; i<4; i++)
			tmp = tmp && (values[i]+1 == values[i+1]);
		if(tmp) {
			res.push(values[4]);
			res.push(STRAIGHT_FLUSH);
			//cout << "escalera real" << endl;
			return res;
		}
	}
	//poker
	tmp = true;
	if(values[0] != values[1]) {
		for(i=1; i<4; i++)
			tmp = tmp && (values[i] == values[i+1]);
	} else {
		for(i=0; i<3; i++)
			tmp = tmp && (values[i] == values[i+1]);
	}
	if(tmp) {
		res.push(values[2]);	//el valor del medio siempre es una carta que participó del poker, y aquí damos su valor para comparar
		res.push(POKER);
		//cout << "poker" << endl;
		return res;
	}
	//full house
	tmp = true;
	if(((values[0] == values[1]) && (values[0] == values[2]) && (values[3] == values[4]))
		|| ((values[2]==values[3]) && (values[2]==values[4]) && (values[0] == values[1]))
	) {
		res.push(values[2]);
		res.push(FULL);
		//cout << "full" << endl;
		return res;
	}
	//flush
	if(flush) {
		for(i=0; i<5; i++)
			res.push(values[i]);
		res.push(FLUSH);
		//cout << "flush" << endl;
		return res;
	}
	//straight
	tmp = true;
	for(i=0; i<4; i++)
		tmp = tmp && (values[i]+1 == values[i+1]);
	if(tmp) {
		res.push(values[4]);
		res.push(STRAIGHT);
		//cout << "straight" << endl;
		return res;
	}
	//pierna
	if(((values[0] == values[1]) && (values[0] == values[2])) || ((values[2]==values[3]) && (values[2]==values[4]))) {
		res.push(values[2]);
		res.push(PIERNA);
		//cout << "pierna" << endl;
		return res;
	}
	//dos pares
	if((values[0]==values[1]) && (values[2]==values[3])) {
		if(values[0] > values[2]) {
			res.push(values[4]);
			res.push(values[2]);
			res.push(values[0]);//cout << "doble par" << endl;
			res.push(DOBLE_PAR);
			return res;
		} else {
			res.push(values[4]);
			res.push(values[0]);
			res.push(values[2]);
			res.push(DOBLE_PAR);//cout << "doble par" << endl;
			return res;
		}
	} else if((values[1]==values[2]) && (values[3]==values[4])) {
		if(values[1] > values[3]) {
			res.push(values[0]);
			res.push(values[3]);
			res.push(values[1]);
			res.push(DOBLE_PAR);//cout << "doble par" << endl;
			return res;
		} else {
			res.push(values[0]);
			res.push(values[1]);
			res.push(values[3]);
			res.push(DOBLE_PAR);//cout << "doble par" << endl;
			return res;
		}
	} else if((values[0]==values[1]) && (values[3]==values[4])) {
		if(values[0] > values[3]) {
			res.push(values[2]);
			res.push(values[3]);
			res.push(values[0]);
			res.push(DOBLE_PAR);//cout << "doble par" << endl;
			return res;
		} else {
			res.push(values[2]);
			res.push(values[0]);
			res.push(values[3]);
			res.push(DOBLE_PAR);//cout << "doble par" << endl;
			return res;
		}
	}
	//par ---------------------------------------------(SI HAY WA, CHECAR ESTA ZONA)
	tmp = false;
	for(i=0; i<4; i++) {
		tmp = tmp || (values[i] == values[i+1]);
		if(tmp) {
			for(int j=0; j<5; j++)
				res.push(values[j]);
			res.push(values[i]);
			res.push(PAR);//cout << "par" << endl;
			return res;
		}
	}
	//highest card
	for(i=0; i<5; i++)
		res.push(values[i]);
	//cout << "carta alta" << endl;
	return res;
}

int main(void)
{
	int i;
	char hands[2][5][2];	//fila indica el jugador Black (fila 0) o jugador White (fila 1), despues las 5 columnas indican las cartas (representadas por dos char)
	int values_a[5];	//a = jugador Black
	int values_b[5];
	char suits_a[5];
	char suits_b[5];
	stack<int> valor_mano_a;
	stack<int> valor_mano_b;
	
	do {
		for(i=0; i<10; i++) {
			cin >> hands[i/5][i%5];	//llenamos los dos arrays, checa como saltamos a la segunda fila a partir de i=5
			if(cin.eof())
				break;
		}
		if(i<9)	break;	//el ultimo input no contenia 10 cartas, salte. (no podriamos usar if(cin.eof()) porque éste tambien se activa en la ultima linea aunque leamos 10 cartas
		
		//cargar valores de las cartas y los palos en unos arrays mas convenientes
		for(i=0; i<5; i++) {
			if(isdigit(hands[0][i][0])) 
				values_a[i] = hands[0][i][0] - '0';		//convertir char (un unico char, no un char *) a int
			else {
				switch(hands[0][i][0]) {
					case 'T':
						values_a[i] = 10;
						break;
					case 'J':
						values_a[i] = 11;
						break;
					case 'Q':
						values_a[i] = 12;
						break;
					case 'K':
						values_a[i] = 13;
						break;
					case 'A':
						values_a[i] = 14;
						break;
				}
			}
		}
		for(i=0; i<5; i++) {
			if(isdigit(hands[1][i][0])) 
				values_b[i] = hands[1][i][0] - '0';		//convertir char (un unico char, no un char *) a int
			else {
				switch(hands[1][i][0]) {
					case 'T':
						values_b[i] = 10;
						break;
					case 'J':
						values_b[i] = 11;
						break;
					case 'Q':
						values_b[i] = 12;
						break;
					case 'K':
						values_b[i] = 13;
						break;
					case 'A':
						values_b[i] = 14;
						break;
				}
			}
		}
			
		for(i=0; i<5; i++)
			suits_a[i] = hands[0][i][1];
		for(i=0; i<5; i++)
			suits_b[i] = hands[1][i][1];
			
		
		valor_mano_a = valor_mano(values_a, suits_a);
		valor_mano_b = valor_mano(values_b, suits_b);
		
		int res = 0;
		while(!valor_mano_a.empty()) {
			//cout << "black tiene: " << valor_mano_a.top() << " white tiene: " << valor_mano_b.top() << endl;
			if(valor_mano_a.top() > valor_mano_b.top()) {
				res = 1; 
				break;
			} else if(valor_mano_a.top() < valor_mano_b.top()) {
				res = -1;
				break;
			}
			valor_mano_a.pop();
			valor_mano_b.pop();
		}
			
		if(res > 0)
			cout << "Black wins." << endl;
		else if(res < 0)
			cout << "White wins." << endl;
		else
			cout << "Tie." << endl;
		
		while(!valor_mano_a.empty())
			valor_mano_a.pop();
		while(!valor_mano_b.empty())
			valor_mano_b.pop();
		
	} while(!cin.eof());
			
	
	return 0;
}
