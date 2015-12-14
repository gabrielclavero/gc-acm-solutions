/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int cambios[2][53];
string cartas[53] = {"nada", "2 of Clubs", "3 of Clubs", "4 of Clubs", "5 of Clubs", "6 of Clubs", "7 of Clubs", "8 of Clubs", "9 of Clubs", "10 of Clubs", "Jack of Clubs", "Queen of Clubs", "King of Clubs", "Ace of Clubs", "2 of Diamonds", "3 of Diamonds", "4 of Diamonds", "5 of Diamonds", "6 of Diamonds", "7 of Diamonds", "8 of Diamonds", "9 of Diamonds", "10 of Diamonds", "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds", "Ace of Diamonds", "2 of Hearts", "3 of Hearts", "4 of Hearts", "5 of Hearts", "6 of Hearts", "7 of Hearts", "8 of Hearts", "9 of Hearts", "10 of Hearts", "Jack of Hearts", "Queen of Hearts", "King of Hearts", "Ace of Hearts", "2 of Spades", "3 of Spades", "4 of Spades", "5 of Spades", "6 of Spades", "7 of Spades", "8 of Spades", "9 of Spades", "10 of Spades", "Jack of Spades", "Queen of Spades", "King of Spades", "Ace of Spades"};

void inicializar_cambios(void);

int main(void)
{
	int cases, n, i, j;
	int shuffles[101][53];
	vector<int> aplicados;	//si bien podríamos usar char aca ya que los elementos estarán en el rango 1-100, usamos int para no cargar espacios en blanco por error (un ' ' es un char pero no un int, y así podremos usar tranquilamente el cin >>)
	
	cin >> cases;
	
	while(cases > 0) {
		aplicados.clear();
		cin >> n;
		for(i=1; i<=n; i++) {
			for(j=1; j<=52; j++)
				cin >> shuffles[i][j];
		}

		
		string tmp;
		getline(cin, tmp);//el cin >> deja el ultimo \n libre creo, con esta sentencia nos deshacemos de él		
		int tmp_int = 0;	
		stringstream ss(stringstream::in | stringstream::out);
		do {
			tmp_int = 0;
			ss.clear(stringstream::goodbit);
			getline(cin, tmp);
			//cout << tmp << endl;
			ss.str(tmp);
			ss >> tmp_int;
			if(tmp_int!=0) aplicados.push_back(tmp_int);	//si tmp_int quedó igual a cero es porque no pudimos leer ningun entero de esa linea de input, (tambien podría ser que la linea contenia un 0 pero la especificacion del input no lo permite)
		} while(tmp_int!=0 && !cin.eof());
		
			
		//algoritmo
		inicializar_cambios();
		
		vector<int>::iterator it;
		int quien_toca = 1;
		for(it=aplicados.begin(); it!=aplicados.end(); it++) {
			for(i=1; i<=52; i++)
				cambios[quien_toca%2][i] = cambios[(quien_toca+1)%2][shuffles[*it][i]];
			quien_toca = (quien_toca+1)%2;
		}
		//pos: en cambios[(quien_toca+1)%2] queda el orden final de las cartas luego de todos los shuffles

		//imprimir respuesta
		quien_toca = (quien_toca+1)%2;
		for(i=1; i<=52; i++)
			cout << cartas[cambios[quien_toca][i]] << endl;
		
		cases--;
		if(cases>0) cout << endl;
	}
	return 0;
}

void inicializar_cambios(void)
{
	for(int i=1; i<=52; i++)
		cambios[0][i] = i;	//ordenamos de 1 a 52 el array, cada uno haciendo referencia a una carta en particular
}
