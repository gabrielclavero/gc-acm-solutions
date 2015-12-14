/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(void)
{
	int cases, relatives, relatives2, tmp;
	vector<int> numbers;
	
	cin >> cases;
	
	while(cases > 0) {
		cin >> relatives;
		relatives2 = relatives;
		while(relatives > 0) {
			cin >> tmp;
			numbers.push_back(tmp);
			relatives--;
		}

		
		sort(numbers.begin(), numbers.end());
	
		//calcular la mediana de esos datos (o sea el numero optimo para la casa de vito)
		int mediana;
		if(numbers.size() % 2 == 0)
			mediana = (int) ceil((numbers[(int) ceil(numbers.size()/2.0)-1] + numbers[(int)ceil(numbers.size()/2)])/2.0);	//no olvides ponerle el denominador como punto flotante porque sino hace la division entera
		else 
			mediana = numbers[(int) floor(numbers.size()/2.0)];
		
		
		
		int res = 0;
		for(unsigned int i=0; i<numbers.size(); i++)
			res += abs(mediana-numbers[i]);
		
		cout << res << endl;
		
		numbers.clear();
		cases--;	
	}

	return 0;
}
