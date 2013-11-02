//============================================================================
// Name        : Buildtow.cpp
// Author      : Aditya
// Version     :
// Copyright   : SPOJ problem BUILDTOW : http://www.spoj.com/problems/BUILDTOW/
// Description : The problem asks us to compute the sum(F(n)^2) -(0+1), where F(n) is the
//				 nth fibonacci number and n = 1,2,... , F(1) = 0. The sum formula derived
//				 for this is the following relation :
//						S(n) = 1/5*( F(2n-1) + F(2n+1) + (-1)^n) -1
//				 This sum can be computed in O(lgn) time using the following recurrence relation
//				 to compute F(2n+1) and F(2n-1) :
//						[ 1 1 ]^(2n-1) = [ F(2n+1) F(2n) ]
//						[ 1 0 ]          [ F(2n)  F(2n-1)]
//============================================================================

#include <iostream>
#include <cassert>
using namespace std;
#define MODULO 1000000007
/*the multiplicative modulo inverse of 5*/
#define MODINV 400000003
#define MATMUL(a,b,c)    \
{	(c)[0][0] = (((a)[0][0]%MODULO)*((b)[0][0]%MODULO) + ((a)[0][1]%MODULO)*((b)[1][0]%MODULO))%MODULO;	\
	(c)[0][1] = (((a)[0][0]%MODULO)*((b)[0][1]%MODULO) + ((a)[0][1]%MODULO)*((b)[1][1]%MODULO))%MODULO;	\
	(c)[1][0] = (((a)[1][0]%MODULO)*((b)[0][0]%MODULO) + ((a)[1][1]%MODULO)*((b)[1][0]%MODULO))%MODULO;	\
	(c)[1][1] = (((a)[1][0]%MODULO)*((b)[0][1]%MODULO) + ((a)[1][1]%MODULO)*((b)[1][1]%MODULO))%MODULO;	\
}

typedef unsigned long long vtype ;

/*calculates the  nth power of the fibonacci matrix*/
void fibnmod(vtype n, vtype fib[][2]){

	if(n==1 || n==0){
		fib[0][0] = fib[0][1] = fib[1][0] =1;
		fib[1][1] = 0;
		return ;
	}

	if(n%2==0){
		vtype f[2][2] = {{0,0},{0,0}};
		fibnmod(n/2,f);
		MATMUL(f,f,fib);
		return;
	}
	else{
		vtype f1[2][2] = {{0,0},{0,0}};
		vtype f2[][2] = {{1,1},{1,0}};
		fibnmod(n-1,f1);
		MATMUL(f1,f2,fib);
		return;
	}
}

/*calculates S(n)*/
vtype sumfibn(vtype N){
	vtype n = N+2;
	vtype fib[2][2] = {{0,0},{0,0}};
	fibnmod(2*n-1,fib);
	vtype s1 = (fib[0][0]%MODULO+ fib[1][1]%MODULO);
	vtype sum = 0;

	if(n%2==0)sum = ((s1 -(4%MODULO))*MODINV)%MODULO;
	else sum = ((s1 -(6%MODULO))*MODINV)%MODULO;

	return sum;
}

/*calculates the modulo multiplicative inverse of a(mod b)*/
vtype modinv(vtype a, vtype b){
	long long x = 0,y=1;
	long long lastx=1, lasty=0;
	long long q = 0,c=0;
	while (b != 0){
	    q= a/b;
	    c = a%b;
	    a = b;
	    b = c;
	    c = lastx-q*x;
	    lastx = x;
	    x =c ;
	    c = lasty -q*y;
	    lasty = y;
	    y = c;
	}
	return lastx;
}


int main() {
	int numcases;
	vtype n;
	cin>>numcases;
	for(int i=0;i<numcases;i++){
		cin>>n;
		cout<<"$"<<sumfibn(n)<<"\n";
	}
	return 0;
}
