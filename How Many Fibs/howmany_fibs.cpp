/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>

using namespace std;

const int MAXDIGITS = 1000;
const int PLUS = 1;
const int MINUS = -1;

typedef struct {
	char digits[MAXDIGITS];
	int signbit;
	int lastdigit;
} bignum;

void print_bignum(bignum *n);
void zero_justify(bignum *n);
void digit_shift(bignum *n, int d);
void initialize_bignum(bignum *c);
int compare_bignum(bignum *a, bignum *b);
void subtract_bignum(bignum *a, bignum*b, bignum *c);
void add_bignum(bignum *a, bignum *b, bignum *c);

int g=3;
bignum fib[500];

void fibonacci_rec(void)
{
	add_bignum(&(fib[g-2]), &(fib[g-1]), &(fib[g]));
	g++;
	//print_bignum(&c);
	if(g!=499) fibonacci_rec();
}

int main(void)
{
	initialize_bignum(fib);
	initialize_bignum(&(fib[1]));
	initialize_bignum(&(fib[2]));
	fib[0].digits[0] = 0;
	fib[1].digits[0] = 1;
	fib[2].digits[0] = 2;
	
	fibonacci_rec(); //llenar la tabla de valores de fibonacci hasta 10^100 aprox.
	
    bignum n[2];
    int i; char c;
    while(1) {
		initialize_bignum(n);
		initialize_bignum(&(n[1]));
		for(int j=0; j<2; j++) {
            i = 0;
			while(isdigit(c = getchar())) {
				n[j].digits[i] = c-'0';
				n[j].lastdigit++;
				i++;
			}
		}
		n[0].lastdigit--;
		n[1].lastdigit--;
		int tmp;
		for(int j=0; j<2; j++) {
			for(i=n[j].lastdigit; i>=(n[j].lastdigit+1)/2; i--) {  //dar vuelta el arreglo porque bignum considera el primer digito como el menos significativo
		    	if((i == (n[j].lastdigit+1)/2) && (n[j].lastdigit) % 2 == 0) break;
				tmp = (n[j]).digits[i];
				(n[j]).digits[i] = (n[j]).digits[n[j].lastdigit-i];
				(n[j]).digits[n[j].lastdigit-i] = tmp;
			}
		}
		
		//print_bignum(n);
		//print_bignum(&(n[1]));
		
		if(n[0].lastdigit == 0 && n[1].lastdigit == 0 && n[0].digits[0] == 0 && n[1].digits[0] == 0) break;
		
		if(compare_bignum(&n[0], &n[1]) == -1) {
			cout << 0 << endl;
			continue;
		}
		
		//algoritmo
		//encontrar un fib >=a (del enunciado) en la tabla:
		i = 1;
		bool found_it = false;
		while(!found_it) {
			found_it = (compare_bignum(&(fib[i]), n) <= 0);    //compare_bignum devuelve 0 si son iguales o -1 si el primero es mayor que el segundo
			i++;
			//print_bignum(&fib[i]);
		}
		int res = 0;
		i--;
		found_it = false;
		int tmp_b;
		while(!found_it) {
			tmp_b = (compare_bignum(&n[1], &(fib[i])));
            found_it = (tmp_b >= 0);
			i++;
			if(tmp_b <= 0) res++;
			//print_bignum(&fib[i]);
		}
		cout << res << endl;
	}
	
	//cout << compare_bignum(&(fib[3]), fib) << endl;
	
	return 0;
}

void print_bignum(bignum *n)
{
	int i;
	if(n->signbit == MINUS) printf("- ");
	for(i=n->lastdigit; i>=0; i--)
		printf("%c", '0'+n->digits[i]);

	printf("\n");
}

void zero_justify(bignum *n)
{
	while((n->lastdigit > 0) && (n->digits[n->lastdigit] == 0))
	    n->lastdigit--;

	if((n->lastdigit == 0) && (n->digits[0] == 0))
	    n->signbit = PLUS;
}

void digit_shift(bignum *n, int d)
{
	int i;

	if((n->lastdigit == 0) && (n->digits[0] == 0)) return;

	for(i=n->lastdigit; i>=0; i--)
	    n->digits[i+d] = n->digits[i];

	for(i=0; i<d; i++) n->digits[i] = 0;

	n->lastdigit = n->lastdigit + d;
}

void initialize_bignum(bignum *c)
{
	for(int i=0; i<MAXDIGITS; i++)
		(c->digits)[i] = 0;

	c->signbit = PLUS;
	c->lastdigit = 0;
}

int compare_bignum(bignum *a, bignum *b)
{
	int i;

	if((a->signbit == MINUS) && (b->signbit==PLUS)) return PLUS;
	if((a->signbit == PLUS) && (b->signbit==MINUS)) return MINUS;

	if(b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
	if(a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

	for(i = a->lastdigit; i>=0; i--) {
		if(a->digits[i] > b->digits[i])
		    return(MINUS*a->signbit);
		if(b->digits[i] > a->digits[i])
		    return (PLUS*a->signbit);
	}
	return 0;
}


void subtract_bignum(bignum *a, bignum*b, bignum *c)
{
	int borrow;
	int v, i;

	if((a->signbit == MINUS) ||(b->signbit == MINUS)) {
		b->signbit = -1 * b->signbit;
		add_bignum(a, b, c);
		b->signbit = -1 * b->signbit;
		return;
	}

	if(compare_bignum(a, b) == PLUS) {
		subtract_bignum(b,a,c);
		c->signbit = MINUS;
		return;
	}

	c->lastdigit = max(a->lastdigit, b->lastdigit);
	borrow = 0;

	for(i=0; i<=(c->lastdigit); i++) {
		v = (a->digits[i] - borrow - b->digits[i]);
		if(a->digits[i] > 0)
		    borrow = 0;
		if(v<0) {
			v = v+ 10;
			borrow = 1;
		}
		c->digits[i] = (char) v % 10;
	}
	zero_justify(c);
}

void add_bignum(bignum *a, bignum *b, bignum *c)
{
	int carry, i;

	initialize_bignum(c);

	if(a->signbit == b->signbit) c->signbit = a->signbit;
	else {
		if(a->signbit == MINUS) {
			a->signbit = PLUS;
			subtract_bignum(b, a, c);
			a->signbit = MINUS;
		} else {
			b->signbit = PLUS;
			subtract_bignum(a,b,c);
			b->signbit = MINUS;
		}
		return;
	}

	c->lastdigit = max(a->lastdigit, b->lastdigit)+1;
	carry = 0;

	for(i=0; i<=(c->lastdigit); i++) {
		c->digits[i] = (char) (carry+a->digits[i]+b->digits[i]) % 10;
		carry = (carry + a->digits[i] + b->digits[i]) / 10;
	}

	zero_justify(c);
}
