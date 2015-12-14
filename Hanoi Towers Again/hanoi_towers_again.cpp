/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int res[51];

int f(int n_pegs, int ball, vector<vector<int> > &pegs)
{
	int res=0, max=0;

	bool ya = false;
	for(int i=0; i<pegs.size(); i++) {

		if(pow(floor(sqrt(pegs[i][pegs[i].size()-1] + ball)), 2) ==  pegs[i][pegs[i].size()-1] + ball) {
			pegs[i].push_back(ball);
			res = f(n_pegs, ball+1, pegs);
			if(res > max) max = res;
			//pegs[i].pop_back();
			ya = true;
			break;
		}
	}
	if(!ya) {
		if(pegs.size() < n_pegs) {
			vector<int> tmp(1, ball);
			pegs.push_back(tmp);
			max = f(n_pegs, ball+1, pegs);
			//pegs.pop_back();
			//cout << copy_pegs[0][0] << endl;		
		}		
	}
	if(max > ball-1) return max;
	else return ball-1;
}

int main(void) 
{
	int t, n;
	vector<vector<int> > pegs;
	
	for(int i=1; i<=50; i++) {
		res[i] = f(i, 1, pegs);
		pegs.clear();
	}		
	
	cin >> t;
	while(t > 0) {
		cin >> n;
		
		cout << res[n] << endl;
		
		t--;
	}
	
	return 0;
}
