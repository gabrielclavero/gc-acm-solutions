/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double truncar_2(double);
int calc_ctvs_sobrantes(double, int);

int calc_ctvs_sobrantes(double prom, int n)
{
	double m = prom*100.0;
	m = floor(m);
	m /= 100.0;
	m = (prom-m)*100.0*n;
	m = truncar_2(m);//si aplicamos directamente ceil sin antes no considerar los decimales poco significativos podemos obtener una respuesta incorrecta
	return (int) ceil(m);
}

double truncar_2(double n)
{	
	/*C++ redondea por defecto para arriba al parecer, o sea, 3.549 con precision 2 quedaría 3.55,
	para que redondee truncando simplemente, debemos usar otra cosa.*/
	n *= 100.0;
	n = floor(n);
	return n/100.0;
}

/*este programa asume que la entrada para n será un entero y que las entradas para gastos serán
decimales
Probar casos en que el promedio de 5.009 por ej, la cosa es que el ultimo valor decimal este cercano al 9*/
int main(void)
{
	int n;
	vector<double> gastos;
	
	cout.setf(ios::fixed);//necesario para que precision sea la cantidad de digitos decimales DESPUES de la coma
	cout.precision(2);
	
	int i;
	double f_tmp;
	double total_gastos = 0;
	double prom, prom_trunc;
	int ctvs_sobrantes;
	double res = 0;
	
	cin >> n;
	while(n!=0) {
		f_tmp = 0; total_gastos = 0; res = 0; prom = 0; prom_trunc = 0; ctvs_sobrantes = 0;
		gastos.clear();
		for(i=0; i<n; i++) {	//leemos los gastos de cada estudiante
			cin >> f_tmp;
			total_gastos += f_tmp;
			gastos.push_back(f_tmp);
		}
		sort(gastos.begin(), gastos.end());
		
		prom = (double) total_gastos/n;
		prom_trunc = truncar_2(prom); //prom pasa a indicar lo que cada estudiante debe pagar
		ctvs_sobrantes = calc_ctvs_sobrantes(prom, n);
		
		i=0;
		while(gastos[i] < prom && i<n) {
		//for(i=0; i<=floor((n-1)/2); i++)
			res += prom_trunc - gastos[i];
			i++;
		}
		if((n-i) >= ctvs_sobrantes) res = res;
		else res += (ctvs_sobrantes-(n-i))/100.00; //cuidado con usar unsigned ints aca y con poner 100 en lugar de 100.00 (queremos que devuelva un double, no un int)
		
		cout << "$" << res << endl;
		cin >> n;
	}
	
	return 0;
}
