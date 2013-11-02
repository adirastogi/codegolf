//============================================================================
// Name        : Arrgame2.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to Codechef  ARRGAME2
// Description : http://www.codechef.com/OCT13/problems/ARRGAME2/
//============================================================================

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int binsearch(int a[], int size,int key){
	int l = 0;
	int h = size-1;
	int m = 0;
	while(l<=h){
		m = (l+h)/2;
		if (key<=a[m])
			h = m-1;
		else l = m+1;
	}
	//get to the last match of less than if not found or the first match if found
	int k = m;
	if(a[m]!=key){
		return l;
	}
	else return m;
}
inline double expectedKisses(int x[], int y[], int size){
	std::sort(x,x+size);
	//std::sort(y,y+size);
	//calculate number of 1s and 2s
	int num1s = binsearch(x,size,2);
	int num2s = binsearch(x,size,3)-num1s;
	long long numpairs = 0;
	for(int i=0; i<size ; ++i){
		int numless = 0;
		if(y[i]==3)continue;
		else if(y[i]==1){
			//count all elements greater than 1
			numless += (size-num1s);
		}
		else if(y[i]==4 || y[i]==2){
			//only matches greater equal to 3 are acceptable
			int pos1 = binsearch(x,size,4);
			if(pos1-1>=0 && (x[pos1-1]==2 || x[pos1-1]==1))continue;
			else{
				numless = pos1-num2s-num1s;
			}
		}else {
			//all matches except 1s
			int pos1 = binsearch(x,size,y[i]);
			numless = pos1-num1s;
		}
		numpairs +=numless;

	}
	return double(numpairs)/double(size);
}
int main() {
	int ncases;
	int x[100010];int y[100010];
	//int a[] = {2,3};
	//int b[]= {1,4};
	//double ans = expectedKisses(a,b,2);
	scanf("%d",&ncases);
	while(ncases-->0){
		int n;
		scanf("%d",&n);
		for(int i=0; i<n ; ++i)
			scanf("%d",&x[i]);
		for(int i=0; i<n ; ++i)
			scanf("%d",&y[i]);
		printf("%.6f\n",expectedKisses(x,y,n));

	}
}
