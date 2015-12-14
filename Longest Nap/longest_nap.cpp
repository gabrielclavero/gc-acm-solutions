/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int JORNADA_COMIENZO = 600;
const int JORNADA_FINAL = 1080;

bool comp(vector<int> a, vector<int> b)
{
	return (a[0] < b[0]);
}


int main(void)
{
	int s;
	int day = 1;
	int minutos;
	char tmp[2];
	string trash;
	vector<vector<int> > schedule;
	vector<int> tmp2;
	
	while(!cin.eof()) {
		cin >> s;
		if(cin.eof()) break;
		getline(cin, trash);
		
		if(s == 0) {
			cout << "Day #" << day << ": the longest nap starts at 10:00 and will last for 8 hours and 0 minutes." << endl;
			day++;
			schedule.clear();
			continue;
		}
		
		while(s>0) {
			//cout << trash << endl;
			for(int i=0; i<=1; i++) {
				if(i==1) cin.ignore();
				cin.read(tmp, 2);
				cin.ignore();	//ignorar el :
				minutos = (tmp[0]- '0')*10*60 + (tmp[1] - '0')*60;
				cin.read(tmp, 2);
				//cin.ignore();	//ignorar el ' '
				minutos += (tmp[0] - '0')*10 + (tmp[1] - '0');
				tmp2.push_back(minutos);
			}
			schedule.push_back(tmp2);
			tmp2.clear();
			while(cin.peek() != '\n' && cin.peek() != EOF) {	//ignorar el appointment
				cin.ignore();
			}
			cin.ignore();
			s--;
		}
		
		//algoritmo. Ahora tenemos todos los horarios en minutos, (por ej, las 10:00 sería 600 porque han pasado 600 minutos desde las 0 horas
		sort(schedule.begin(), schedule.end(), comp);
		
			
		//contemos los minutos que puede durar la longest nap
		int comienzo = -1;	//comienzo de la siesta mas larga
		minutos = 0;
		int horas, minutos_start;
		
		if(schedule.size() > 0)
			minutos = schedule[0][0] - JORNADA_COMIENZO;
		
		for(int i=1; i<schedule.size(); i++) {
			if(minutos < schedule[i][0] - schedule[i-1][1]) {
				minutos = schedule[i][0] - schedule[i-1][1];
				comienzo = i-1;
			}
		}
		

		if(JORNADA_FINAL - schedule[schedule.size()-1][1] > minutos) {
			minutos = JORNADA_FINAL - schedule[schedule.size()-1][1];
			comienzo = schedule.size()-1;
		}
		
		if(comienzo >=0) {
			horas = floor(schedule[comienzo][1]/60.0);
			minutos_start = schedule[comienzo][1]%60;
			cout << "Day #" << day << ": the longest nap starts at " << horas << ":";
			if(minutos_start < 10)
				cout << "0";
			cout << minutos_start << " and will last for ";
			
		} else {
			cout << "Day #" << day << ": the longest nap starts at 10:00 and will last for ";
		}
			
		horas = floor(minutos/60);
		minutos = minutos%60;
		if(horas > 0)
			cout << horas << " hours and " << minutos << " minutes." << endl;
		else
			cout << minutos << " minutes." << endl;		
		
		day++;
		schedule.clear();
	}
	
	return 0;
}
