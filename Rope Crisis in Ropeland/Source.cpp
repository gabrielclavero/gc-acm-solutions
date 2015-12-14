/**
*
* Author: Gabriel Clavero
* Homepage: https://github.com/gabrielclavero/gc-acm-solutions
*
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPSILON = 0.00000001;

struct Point 
{
	double x;
	double y;
	bool intersect;

	Point(double a, double b)
	: x(a), y(b)
	{

	}

	Point()
	{

	}
};

struct Line 
{
	double a;
	double b;
	double c;
};

void points_to_line(Point p1, Point p2, Line *l) 
{
	if(p1.x == p2.x) {
		l->a = 1;
		l->b = 0;
		l->c = -p1.x;
	} else {
		l->b = 1;
		l->a = -(p1.y - p2.y)/(p1.x - p2.x);
		l->c = -(l->a * p1.x) - p1.y;
	}
}

void point_and_slope_to_line(Point p, double m, Line *l)
{
	l->a = -m;
	l->b = 1;
	l->c = m * p.x - p.y;
}

bool parallelQ(Line l1, Line l2)
{
	return ( (fabs(l1.a - l2.a) <= EPSILON) && (fabs(l1.b-l2.b) <= EPSILON) );
}

bool same_lineQ(Line l1, Line l2)
{
	return ( parallelQ(l1, l2) && (fabs(l1.c - l2.c) <= EPSILON) );
}

void intersection_point(Line l1, Line l2, Point &p)
{
	p.intersect = true;

	if(same_lineQ(l1, l2)) {
		p.x = p.y = 0.0;
		return;
	}

	if(parallelQ(l1, l2) == true) {
		p.intersect = false;
		return;
	}

	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

	if(fabs(l1.b) > EPSILON)
		p.y = -(l1.a * p.x + l1.c) / l1.b;
	else
		p.y = -(l2.a * p.x + l2.c) / l2.b;
}

void closest_point(Point p_in, Line l, Point &p_c)
{
	Line perp;

	if(fabs(l.b) <= EPSILON) {
		p_c.x = -l.c;
		p_c.y = p_in.y;
		return;
	}

	if(fabs(l.a) <= EPSILON) {
		p_c.x = p_in.x;
		p_c.y = -l.c;
		return;
	}

	point_and_slope_to_line(p_in, 1/l.a, &perp);
	intersection_point(l, perp, p_c);
}

double distanceBetweenPoints(Point a, Point b)
{
	double x = b.x - a.x;
	double y = b.y - a.y;

	return sqrt(x*x + y*y);
}

bool are_lines_equal(Line &l1, Line &l2)
{
	if(fabs(l1.a - l2.a) <= EPSILON &&
		fabs(l1.b - l2.b) <= EPSILON &&
		fabs(l1.c - l2.c) <= EPSILON)
	{
		return true;
	}

	return false;
}

const double PI = 3.141592653589793238463;

int main()
{
	int n;
	Point a, b;
	double r;

	cin >> n;

	cout << fixed;
	cout << setprecision(3);

	while(n>0) {
		cin >> a.x >> a.y >> b.x >> b.y >> r;

		Line l;
		points_to_line(a, b, &l);
		
		Point c;	//punto en l más cercano a (0,0) 
		closest_point(Point(0,0), l, c);

		if(distanceBetweenPoints(Point(0,0), c) + EPSILON < r
			&& c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) && c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y) ) 
		{
			//encontrar la distancia entre a y el punto central del circulo
			double d1 = distanceBetweenPoints(Point(0,0), a);

			//encontrar distancia entre a y el punto de intersección entre la recta tangente y el circulo
			double x1 = sqrt(d1*d1 - r*r);

			//encontrar ángulo entre segmento op (donde p es el punto de intersección de la recta tangente con el circulo) y segmento oa, donde o es el origen.
			double B1 = asin((sin(PI/2) * x1) / d1);

			//lo mismo para el otro punto
			double d2 = distanceBetweenPoints(Point(0,0), b);
			double x2 = sqrt(d2*d2 - r*r);
			double B2 = asin((sin(PI/2) * x2) / d2);

			
			//considerar primero caso especial en el que la recta formada por los puntos a y b pasa por el origen (es decir que aob no es un triángulo)

			//ver si la linea l y la linea formada por ao son iguales. Si lo son, abo están en la misma recta, sino forman un triángulo
			Line l2;
			points_to_line(a, Point(0,0), &l2);

			if(are_lines_equal(l, l2)) 
			{
				//calcular distancia recorrida sobre el círculo
				double length_on_circle = (2 * PI - PI - B1 - B2) * r;

				cout << x1 + length_on_circle + x2 << endl;
			} 
			else 
			{
				//en el caso de que esos 3 puntos no formen una recta computamos la longitud de soga de las dos formas posibles de pasarla y vemos la menor

				//primero calcular el ángulo del triángulo aob (el ángulo en o)
				double alpha = acos(distanceBetweenPoints(c, a) / distanceBetweenPoints(a, Point(0,0)));
				double angle1 = PI - alpha - PI/2;

				alpha = acos(distanceBetweenPoints(c, b) / distanceBetweenPoints(b, Point(0,0)));
				double angle2 = PI - alpha - PI/2;

				double angleAOB = angle1+angle2;

				//Lengths
				double length_on_circle1 = (2 * PI - angleAOB - B1 - B2) * r;
				
				double length_on_circle2 = (angleAOB - B1 - B2) * r;

				cout << x1 + min(length_on_circle1, length_on_circle2) + x2 << endl;

			}

		}
		else	//no hubo intersección
		{
			cout << distanceBetweenPoints(a, b) << endl;
		}


		--n;
	}


	return 0;
}