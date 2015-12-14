/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cctype>

using namespace std;

bool ceros(void);
inline void init_ints_r(void);

char ints[2][10];
char ints_r[2][10];
int dis[2];     //longitud en digitos de cada numero

int main(void)
{
	
	int i=0, j=0, carries, tmp, former_carry;
	bool b;
	char c;
	
	do {
		dis[0] = 0; dis[1] = 0;
		for(i=0; i<2; i++) {
			j=0;
			do {
				c = getchar();
				if(isdigit(c)) {
					ints[i][j] = c;
					dis[i]++;
				}
				j++;
			} while(isdigit(c));
		}
		init_ints_r();
		for(i=0; i<2; i++) {
            for(j=0; j<dis[i]; j++)
                ints_r[i][j] = ints[i][dis[i]-1-j];
		}

		
		b = ceros();
		if(!b) {
			carries = 0;
			former_carry = 0;
			//cout << dis[0] << " dis1: " << dis[1] << endl;
			for(i=0; i<10; i++) {
				tmp = (int) (ints_r[0][i]-'0') + (int) (ints_r[1][i]-'0') + former_carry;
				if(tmp>=10) former_carry = 1;
				else former_carry = 0;
				carries += former_carry;
			}
			if(!carries) printf("No carry operation.\n");
			else if(carries>1) printf("%i carry operations.\n", carries);
			else printf("%i carry operation.\n", carries);
		}
	} while(!b);

	return 0;
}

inline void init_ints_r(void)
{
    for(int i=0; i<2; i++) {
		for(int j=0; j<10; j++)
			ints_r[i][j] = '0';
	}
}

bool ceros(void)
{
	for(int i=0; i<2; i++) {
		for(int j=0; j<dis[i]; j++) {
		    if(ints_r[i][j] != '0') return false;
		}
	}
	return true;
}
