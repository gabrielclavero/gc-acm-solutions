/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main(void)
{
	int cases, n, tmp;
	string turtle;
	vector<string> original_stack, final_stack;
	vector<int> o_stack;
	
	cin >> cases;
	
	while(cases > 0) {
		cin >> n;
		tmp = n;
		while(isspace(cin.peek())) cin.ignore();
		while(n>0) {
			getline(cin, turtle);
			original_stack.push_back(turtle);
			n--;
		}
		while(tmp>0) {
			getline(cin, turtle);
			final_stack.push_back(turtle);
			tmp--;
		}
		
		//stack inicial pero en enteros, no con nombres de tortugas
		//notar que el stack final es 0, 1, 2, 3..., n-1
		for(int i=0; i<original_stack.size(); i++) {
			tmp = 0;
			while(final_stack[tmp] != original_stack[i]) {
      			//cout << final_stack[tmp]<< " " << original_stack[i] << endl;
				tmp++;
				//cout << tmp << endl;
			}
			o_stack.push_back(tmp);
		}
		
		//ALGORITMO
		
		//busqueda del candidato inicial: buscar aquellas tortugas que deban subir de posicion en el stack
		//y de entre esas elegir a la que tenga que quedar mas al fondo al final
		int candidato = -1;
		int indice;
		vector<int> turtles_to_move;
		do {
		
			candidato = -1;
			//notar como voy de abajo para arriba, me fijo cuántas tortugas debajo de mi debo subir (ya sea porque de entrada está mas bajo de lo que debería o porque
			//al subir otras que deben hacerlo ésta va a quedar mas abajo de lo que debe (por eso iteramos desde abajo para arriba)
			tmp = 0;    //esto cuenta las tortugas que deben ir subiendo
			for(int i=o_stack.size()-1; i>=0; i--) {
				if(o_stack[i] < i+tmp) {
					tmp++;
					if(o_stack[i] > candidato) {        //finalmente moveré la que al final deba estar mas abajo
						candidato = o_stack[i];     
						indice = i;
					}
				}
			}
			//mover posiciones
			if(candidato != -1) {
				for(int i=indice; i>0; i--)
					o_stack[i] = o_stack[i-1];
				o_stack[0] = candidato;

				cout << final_stack[candidato] << endl;
			}
		} while(candidato != -1);

		original_stack.clear(); final_stack.clear(); o_stack.clear();
		cout << endl;
		cases--;
	}
	return 0;
}
