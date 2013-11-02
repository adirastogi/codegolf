//============================================================================
// Name        : Eqbox.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to SPOJ EQBOX:
// Description : http://www.spoj.com/problems/EQBOX/
//============================================================================

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
#define tol 1e-10
int contained(double a, double b , double x , double y){
	double cosa = double(x*x -y*y)/(double(x*x + y*y));
	double sina = double(2*x*y)/double(x*x +y*y);
	double r = sqrt(x*x + y*y)/2;
	double cosb = double(a)/(sqrt(a*a + b*b));
	double sinb = double(b)/(sqrt(a*a + b*b));
	double px = abs(r*(cosa*cosb - sina*sinb));
	double py = abs(r*(sina*cosb + sinb*cosa));
	double d1 = double(a)/2-px;
	double d2 = double(b)/2-py;
	if(d1 > 0 && d2  > 0)
		return 1;
	else return 0;
}
int contained2(double a , double b , double x , double y){

	double t;
	if(b>a)t=a,a=b,b=t;

	if(y>x)t=x,x=y,y=t;

	if(a==x && y==b)
		return 0;

	double t1 = x*x - y*y;
	double t2 = x*x + y*y;
	if(t2<b*b)
		return 1;
	double t3 = 2*x*y;
	double t4 = sqrt(t2 -b*b);


	double v1 = (t1*t4 - b*t3)/(t2);
	double v2 = (t3*t4 + b*t1)/(t2);
	//swap x & y and then compare the coordinates
	t1 = -t1;
	double v3 = (t1*t4 - b*t3)/(t2);
	double v4 = (t3*t4 + b*t1)/(t2);

	//double d1 = sqrt(v1*v1 + v2*v2)/2;
	//double d2 = sqrt(v3*v3+ v4*v4)/2;
	//double d = sqrt(t2)/2;


	if(fabs(v1)<= a && fabs(v2) <= b)
		return 1;
	else if(fabs(v3) <= a && fabs(v4) <= b)
		return 1;
	else return 0;

}
int contained3(double a, double b , double c , double x, double y){

}
int main() {

	int x , y , a, b;
	int ncases;
	a =1 ; b=1; x=1; y = 1;
	contained2(a,b,x,y);
	scanf("%d",&ncases);
	//ncases = 0;
	for(int i=0; i< ncases; ++i){
		scanf("%d%d%d%d",&a, &b,&x,&y);
		if(contained2(a,b,x,y)==1)
			printf("Escape is possible.\n");
		else printf("Box cannot be dropped.\n");
	}
	return 0;
}
