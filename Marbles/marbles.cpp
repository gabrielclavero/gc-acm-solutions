/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cmath>

using namespace std;

long gcd(long p, long q, long long *x, long long *y)
{
	long long x1, y1;
	long g;

	if(q > p) return(gcd(q,p,y,x));

	if(q == 0) {
		*x = 1;
		*y = 0;
		return p;
	}

	g = gcd(q, p%q, &x1, &y1);

	*x = y1;
	*y = (x1 - (long) floor(p/q)*y1);

	return g;
}

int main(void)
{
	long long n, c1, n1, c2, n2;
	long long x0, y0;
	
	cin >> n >> c1 >> n1 >> c2 >> n2;
	while(n != 0) {
		long d = gcd(n1, n2, &x0, &y0);     //x0*n1 + y0*n2 = d
		if(n%d == 0) {      //la congruencia tiene solucion cuando gcd(n1, n2) divide a n
            
			x0 = x0*(n/d);      //la diophantine ecuacion que buscamos resolver es x*n1 + y*n2 = n. Pero ya sabemos que x0*n1 + y0*n2 = d. Multiplica por n/d y listo
			y0 = y0*(n/d);
			
			
			long double n2_d = n2;
			long double d_d = d;     //para que multiplicar enteros por d quede en double
			long double overflow_tmp = -(x0*d_d);
			cout.setf(ios::fixed,ios::floatfield);
			
			overflow_tmp /= n2_d;
			
			long long tmp = (long long) ceil(overflow_tmp);
			overflow_tmp = (n*d_d);
			overflow_tmp /= (n1*n2_d);
			
			long double overflow_tmp2 = x0*d_d;
			overflow_tmp2 /= n2_d;
			overflow_tmp -= overflow_tmp2;
			long long tmp2 = (long long) floor(overflow_tmp);
			
			long long x1 = x0 + (tmp*n2)/d;
			long long y1 = (n-x1*n1)/n2;
			long long x2 = x0 + (tmp2*n2)/d;
			long long y2 = (n-x2*n1)/n2;

			if(x1 < 0 || y1 < 0 || x1>n || y1>n) {
				if(x2 >= 0 && x2 <=n && y2 >= 0 && y2 <= n)
				    cout << x2 << " " << y2 << endl;
				else
				    cout << "failed" << endl;
			} else {
			    if(x2 < 0 || y2 < 0 || x2>n || y2>n)
                    cout << x1 << " " << y1 << endl;
				else {
                    if(c1*x1+c2*y1 < c1*x2+c2*y2)
		    			cout << x1 << " " << y1 << endl;
					else
		    			cout << x2 << " " << y2 << endl;
				}
			}


			//cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << tmp << " " << tmp2 << endl;
			
		} else
      		cout << "failed" << endl;
		

        cin >> n;
        if(n==0) break;
        cin >> c1 >> n1 >> c2 >> n2;
	}
	return 0;
}
