//============================================================================
// Name        : Integer1.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <cstdio>
#include <cassert>
using namespace std;
typedef unsigned long long vtype;
typedef unsigned long long LL;
//LL get2(LL n, LL exp)
//{
//	LL t = pow((double)n, 1.0/exp);
//	LL i,j,k;
//	LL t1=1, t2=1;
//	for(i=0;i<exp;i++)
//	{
//		t1*=(t);
//		if((1ULL<<63) / t2 < t + 1)
//		continue;
//		t2*=(t+1);
//
//	}
//	//cout<<n<<" "<<t1<<" "<<t2<<endl;
//	if(t2==n && t2 > 0)
//	{
//		return t+1;
//	}
//	else if(t1<=n)
//	return t;
//	return 1;
//}
long double nthroot(vtype num,vtype n){

	long double x = pow(num,1/double(n));
	long double xfloor = floor(x);
	long double xceil  = ceil(x);
	long double cpower = pow(xceil,n);
	long double fpower = pow(xfloor,n);
	if(fpower==num)
		return xfloor;
	else if(cpower==num)
		return xceil;
	else if(fpower < num && cpower < num)
		return xceil;
	else if(cpower > num && fpower >  num)
		return xfloor-1;
	else return xfloor;
}
//long double nthroot2(vtype num, vtype i){
//	if(i==1)
//		return num;
//	if(i==2)
//		return sqrt(num);
//	return exp(log(num)/i);
//}
//vtype intpow(vtype num, vtype i){
//	if(i==1)
//		return num;
//	if(i==2)
//		return num*num;
//
//	vtype l = intpow(num,i/2);
//    if(i%2==0) return l*l;
//    else return num*l*l;
//
//}
//vtype ipow(vtype a, vtype k){
//    double x;
//
//    if (k == 1)
//        return a;
//    if (k == 2)
//        return a * a;
//
//    x = ipow(a, k>>1);
//    if (k & 1)
//        return a * x * x;
//    else
//        return x *x;
//}


vtype powerCount(vtype num){

	if(num==1)
		return 0;

	vtype power[68];
	for(int i=0 ; i < 68 ;i++)
		power[i] = 0;
	vtype sum = 0, powergteq2 = 0; int i;
	for(i = 2; i <= 63 ; i++){
		vtype p = nthroot(num,i);
		//vtype p1 = floor(nthroot2(num,i));
        //cout<<"\n got value for i:"<<i<<" p:"<<p;
		//assert(p ==p3);

		//assert(pow(p,i)==intpow(p,i));
		//assert(pow(p,i)<=num);


		//long double verify1 = pow(p,i);
		//long double verify2 = pow(p+1,i);
		//assert(verify1<=num && verify2 > num);

		if(p >= 2)
			power[i] = p-1;
		else break;
	}
	i--;
	for(int k = i; k >= 2 ; k--){
		int l = (i-k)/k;
		for(int j = k+(k*l); j > k; j-=k){
				power[k] = power[k] - power[j];
		}
		sum+=k*power[k];
		powergteq2+=power[k];
	}



	vtype t = num - powergteq2 -1;
	vtype rv = t + sum;

	return rv;

}


int main() {

	vtype a , b, powercount;

	//while(1)
	{
		//cin>>a>>b;
        //a= 10000000000000000;
        //b = a-1;
		if(a==0 && b ==0)
			break;
        else{
			vtype v1 = powerCount(b);
			vtype v2 = powerCount(a-1);
			powercount =  v1-v2;
		}
		cout<<powercount<<"\n";

	}

	return 0;
}

