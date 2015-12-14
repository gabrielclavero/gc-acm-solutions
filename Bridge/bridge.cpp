/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int main(void)
{
	int cases, n, tmp_i;
	vector<int> cross_times;
	string tmp;
	stringstream res(stringstream::in | stringstream::out);
	int n_rapidos; //cantidad de personas rapidas en el lado opuesto
	int mas_rapido1, mas_rapido2;
	int tiempo;
	
	cin >> cases;
	
	while(cases > 0) {
		cross_times.clear();
		while(!isdigit(cin.peek()))
		    cin.ignore();
	    
	    cin >> n;

	    while(n > 0) {
			cin >> tmp_i;
			cross_times.push_back(tmp_i);
			n--;
		}
		sort(cross_times.begin(), cross_times.end());
		reverse(cross_times.begin(), cross_times.end());
		
		//algoritmo
		if(cross_times.size()>1) {
			tiempo = 0;
			n_rapidos = 0;
			if(cross_times.size()>=2) {
				mas_rapido1 = cross_times[cross_times.size()-1];
				mas_rapido2 = cross_times[cross_times.size()-2];
			}
			//tiempo += mas_rapido2;
			cross_times.erase(cross_times.end()-2, cross_times.end());
			while(cross_times.size() != 0 || n_rapidos != 2) {

				if(cross_times.size() >= 2 || n_rapidos < 2) {
					if(n_rapidos == 0) {
						if(cross_times.size() >= 2) {
	                        if(mas_rapido2 + mas_rapido1 + cross_times[0] + mas_rapido2 <
								cross_times[0] + mas_rapido1 + cross_times[1] + mas_rapido1)
							{
								n_rapidos = 0;
								tiempo += mas_rapido2 + mas_rapido1 + cross_times[0] + mas_rapido2;
								
								res << mas_rapido1 << " " << mas_rapido2 << "\n"
									<< mas_rapido1 << "\n"
									<< cross_times[1] << " " << cross_times[0] << "\n"
									<< mas_rapido2 << "\n";
									
								cross_times.erase(cross_times.begin(), cross_times.begin()+2);
							} else {
								tiempo += cross_times[0] + mas_rapido1 + cross_times[1] + mas_rapido1;
								n_rapidos = 0;
								
								res << mas_rapido1 << " " << cross_times[0] << "\n"
								    << mas_rapido1 << "\n"
								    << mas_rapido1 << " " << cross_times[1] << "\n"
								    << mas_rapido1 << "\n";
								    
								cross_times.erase(cross_times.begin(), cross_times.begin()+2);
							}
						} else {
							if(cross_times.size()==1) {
								tiempo += cross_times[0] + mas_rapido1 + mas_rapido2;
								res << mas_rapido1 << " " << cross_times[0] << "\n"
									<< mas_rapido1 << "\n"
									<< mas_rapido1 << " " << mas_rapido2 << "\n";
							} else {
								tiempo += mas_rapido2;
								res << mas_rapido1 << " " << mas_rapido2 << "\n";
							}
							cross_times.clear();
							n_rapidos = 2;
						}
					} else if(n_rapidos == 2) {
						n_rapidos = 1;
						//cross_times.push_back(mas_rapido1);
						tiempo += mas_rapido1;
						res << mas_rapido1 << "\n";
					} else if(n_rapidos == 1) {
						if(cross_times.size() >= 2) {
							if(cross_times[0] + mas_rapido2 + mas_rapido2 <
								cross_times[0] + mas_rapido1 + cross_times[1] + mas_rapido1 + (cross_times.size()-2>0)*mas_rapido1)  //si cruzar los dos mas lentos y volver el segundo mas rapido es mejor..
							{
								n_rapidos = 0;
								tiempo += (cross_times[0] + mas_rapido2);
								
								res << cross_times[1] << " " << cross_times[0] << "\n"
								    << mas_rapido2 << "\n";
								
								cross_times.erase(cross_times.begin(), cross_times.begin()+2);
							} else {
								tiempo += (cross_times[0] + mas_rapido1 + cross_times[1]);
								
								res << mas_rapido1 << " " << cross_times[0] << "\n"
								    << mas_rapido1 << "\n"
								    << mas_rapido1 << " " << cross_times[1] << "\n";
								
								cross_times.erase(cross_times.begin(), cross_times.begin()+2);
								if(cross_times.size()>0) {  //si aun debemos traer otro mas vuelve el mas rapido sino no
									n_rapidos = 1;
									tiempo += mas_rapido1;
									res << mas_rapido1 << "\n";
								} else n_rapidos = 2;
							}
						} else {
							if(cross_times.size()==1) {
								tiempo += cross_times[0];
								res << mas_rapido1 << " " << cross_times[0] << "\n";
							} else {
								tiempo += mas_rapido1;
								res << mas_rapido1 << "\n";
							}
							cross_times.clear();
							n_rapidos = 2;
						}
					}
				}
			}
		} else {
			tiempo = cross_times[0];
			res << cross_times[0] << endl;
		}
		cout << tiempo << endl;
		cout << res.str();
		res.str(tmp);
	    cases--;
		if(cases>0) cout << endl;
	}
	return 0;
}
