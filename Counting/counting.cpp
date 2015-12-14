/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

const int MAXDIGITS = 1000;
const int PLUS = 1;
const int MINUS = -1;

typedef struct {
	char digits[MAXDIGITS];
	int signbit;
	int lastdigit;
} bignum;

bignum bc[1001];
bignum uno, dos, cinco, trece;

void print_bignum(bignum *n);
void zero_justify(bignum *n);
void digit_shift(bignum *n, int d);
void initialize_bignum(bignum *c);
int compare_bignum(bignum *a, bignum *b);
void subtract_bignum(bignum *a, bignum*b, bignum *c);
void add_bignum(bignum *a, bignum *b, bignum *c);
void multiply_bignum(bignum *a, bignum *b, bignum *c);
void divide_bignum(bignum *a, bignum *b, bignum *c);

void f(int n)
{
	bignum tmp, tmp2;
	
	for(int i=4; i<=n; i++) {
		multiply_bignum(&dos, &bc[i-1], &tmp);
		add_bignum(&tmp, &bc[i-2], &tmp2);
		add_bignum(&tmp2, &bc[i-3], &bc[i]);
	}
}

int main(void)
{
	int n_int, i, tmp;
	char c;
	stringstream ss(stringstream::in | stringstream::out);
	
	bignum res;
	
	//casos base
	initialize_bignum(&uno);
	initialize_bignum(&dos);
	initialize_bignum(&cinco);
	initialize_bignum(&trece);
	uno.digits[0] = 1;
	dos.digits[0] = 2;
	cinco.digits[0] = 5;
	trece.digits[0] = 3;
	trece.digits[1] = 1;
	trece.lastdigit = 1;
	bc[1] = dos;
	bc[2] = cinco;
	bc[3] = trece;
	
	f(1000);
	
	while(!cin.eof()) {
        cin >> n_int;
        
		print_bignum(&bc[n_int]);

        while(!isdigit(cin.peek()) && !cin.eof()) cin.ignore();
	}
		

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

    initialize_bignum(c);
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

void multiply_bignum(bignum *a, bignum *b, bignum *c)
{
	bignum row;
	bignum tmp;
	int i, j;

	initialize_bignum(c);

	row = *a;

	for(i=0; i<=b->lastdigit; i++) {
		for(j=1; j<=b->digits[i]; j++) {
			add_bignum(c, &row, &tmp);
			*c = tmp;
		}
		digit_shift(&row, 1);
	}
	c->signbit = a->signbit * b->signbit;

	zero_justify(c);
}

void divide_bignum(bignum *a, bignum *b, bignum *c)
{
	bignum row;
	bignum tmp;
	int asign, bsign;
	int i, j;

	initialize_bignum(c);

	c->signbit = a->signbit * b->signbit;

	asign = a->signbit;
	bsign = b->signbit;

	a->signbit = PLUS;
	b->signbit = PLUS;

	initialize_bignum(&row);
	initialize_bignum(&tmp);

	c->lastdigit = a->lastdigit;

	for(i=a->lastdigit; i>=0; i--) {
		digit_shift(&row, 1);
		row.digits[0] = a->digits[i];
		c->digits[i] = 0;
		while(compare_bignum(&row, b) != PLUS) {
			c->digits[i]++;
			subtract_bignum(&row, b, &tmp);
			row = tmp;
		}
	}
	zero_justify(c);

	a->signbit = asign;
	b->signbit = bsign;
}
