/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;


int main()
{
	//imprimir trailing zeroes
	cout << fixed;
	cout << setprecision(3);

	int n;
	pair<float,float> gopher, dog, tmp;
	vector<pair<float, float> > holes;

	while(!cin.eof()) {
		cin >> n;

		cin >> gopher.first >> gopher.second >> dog.first >> dog.second;

		holes.clear();
		while(n>0) {
			cin >> tmp.first >> tmp.second;

			holes.push_back(tmp);
			--n;
		}

		//calcular la distancia de cada gopher hole con la posición del gopher y el perro. 
		pair<float, float> gopher_hole_vector, dog_hole_vector;
		bool escaped = false;
		for(int i=0; i<holes.size(); ++i) {
			gopher_hole_vector.first = holes[i].first - gopher.first;
			gopher_hole_vector.second = holes[i].second - gopher.second;

			dog_hole_vector.first = holes[i].first - dog.first;
			dog_hole_vector.second = holes[i].second - dog.second;

			double gopherDistance = sqrt((double) gopher_hole_vector.first * gopher_hole_vector.first + gopher_hole_vector.second * gopher_hole_vector.second);
			double dogDistance = sqrt((double) dog_hole_vector.first * dog_hole_vector.first + dog_hole_vector.second * dog_hole_vector.second);

			if(dogDistance / 2.0 >= gopherDistance) {
				cout << "The gopher can escape through the hole at (" << holes[i].first << "," << holes[i].second << ")." << endl;
				escaped = true;
				break;
			}
		}

		if(!escaped)
			cout << "The gopher cannot escape." << endl;

		while(!isdigit(cin.peek()) && !cin.eof()) cin.ignore();
	}


	return 0;
}