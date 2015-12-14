/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>

using namespace std;

int main(void)
{
	int cases, x, y, steps, partial_sum;
	
	cin >> cases;
	
	while(cases >0) {
		cin >> x; cin >> y;
		
		if(x == y) {
			cout << 0 << endl;
			cases--;
			continue;
		}
		partial_sum = 1;
		x++;
		steps = 1;
		int i = 1;
		while(x != y) {

			steps++;
  			if(x + (i+1) + partial_sum > y) { //seguir aumentando no se puede
			    if(x + i + partial_sum - i > y) { //seguir con ese i tampoco
				    partial_sum -= i;
			        i--;
					x += i;
				} else {
					x += i;
					//partial_sum -= i;
				}
				//bajando = true;
			} else {
				i++;
				partial_sum += i;
				x += i;
			}
		}
		
		cout << steps << endl;
		
		cases--;
	}
	
	return 0;
}
