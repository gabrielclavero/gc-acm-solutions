/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(vector<int> a, vector<int> b)
{
	if (b[0]*a[1] > a[0]*b[1]) 
		return true;
	else if(b[0]*a[1] < a[0]*b[1]) 
		return false;
		
	return (a[2] < b[2]);
}

int main(void)
{
	int cases, n, tmp;
	vector<vector<int> > jobs;
	vector<int> tmp_v;
	
	cin >> cases;
	while(cases > 0) {
		while(cin.peek() != '\n') 
			cin.ignore();
		cin.ignore();
		
		if(cin.eof()) break;
		
		cin >> n;
		int i=1;
		while(n > 0) {
			cin >> tmp;	//t
			tmp_v.push_back(tmp);
			cin >> tmp;		//s
			tmp_v.push_back(tmp);
			tmp_v.push_back(i);
			jobs.push_back(tmp_v);
			tmp_v.clear();
			n--;
			i++;
		}
	
		sort(jobs.begin(), jobs.end(), comp);

			
		for(int i=0; i<jobs.size(); i++) {
			if(i!=jobs.size()-1) 
				cout << jobs[i][2] << " ";
			else
				cout << jobs[i][2];
		}
		
		cout << endl;
		
		jobs.clear();
		cases--;
		
		if(cases >0)
			cout << endl;
	}
	
	return 0;
}
