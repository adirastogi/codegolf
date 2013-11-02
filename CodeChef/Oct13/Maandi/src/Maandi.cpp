//============================================================================
// Name        : Maandi.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to Codechef  MAANDI
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
inline int has4or7(int x){
	while(x!=0){
		if(x%10==4 || x%10==7)
			return 1;
		x = x/10;
	}
	return 0;
}
int main() {
	int ncases;
	int n;
	scanf("%d",&ncases);
	//generateNums();
	while(ncases-->0){
		scanf("%d",&n);
		int count = 0;
		int root = sqrt(n);
		for (int i=1; i<= root ; ++i){
			if(n%i==0){
				int k = n/i;
				//printf("%d,%d,",i,k);
				if(has4or7(k))count++;
				if(has4or7(i))count++;
			}
		}
		printf("%d\n",count);
	}
	return 0;
}
