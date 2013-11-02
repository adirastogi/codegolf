//============================================================================
// Name        : Lebamboo.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to Codechef  LEBAMBOO
// Description : http://www.codechef.com/OCT13/problems/LEBAMBOO/
//============================================================================

#include <iostream>
#include <cstdio>
using namespace std;
int minTransforms(int a[] ,int b[],int size){

	int samecount = 0;
	int suma = 0; int sumb = 0;
	for (int i = 0; i < size ; ++i){
		suma += a[i];
		if(b[i]==a[i]) samecount++;
		sumb += b[i];
	}
	int dist = sumb-suma;
	//special case when all the elements are the same
	if(samecount==size) return 0;

	int incr = size-2;
	if(incr==0){
		//special case for 2 element array
		if(a[0]-b[0]==-(a[1]-b[1]))
			return ((a[0]-b[0]))>0?a[0]-b[0]:-(a[0]-b[0]);
		else return -1;

	}else if(incr==-1){
		if((a[0]-b[0])>1)
			return a[0]-b[0];
		else return -1;
	}else{
		if(dist < incr || dist%incr!=0)
			return -1;
		int maxsteps = dist / incr;
		for(int i = 0 ; i< maxsteps ; ++i){
			int redpos= 0; int reddist = b[0]-a[0];
			//calculate the element wich must be reduced
			for(int j=0 ; j<size ; ++j)
				if(b[j]-a[j]<reddist){
					reddist = a[j] -b[j];
					redpos = j;
				}
			//now reduce the array
			a[redpos] -= 2;
			for(int j=0; j< size ; ++j)
				a[j]++;

			//now match the array
			int k = 0;
			for(k=0;k<size && a[k]==b[k];++k);
			//if the array matches return the value of i;
			if(k==size)
				return i+1;
		}
	}
	return -1;

}
int main() {
	int ncases;
	//int x[] = {1};
	//int y[] = {3};
	//minTransforms(x,y,1);
	scanf("%d",&ncases);
	int a[52],b[52];
	while(ncases-->0){
		int size;
		scanf("%d",&size);
		for(int i=0; i< size ; ++i)
			scanf("%d",&a[i]);

		for(int i=0; i< size ; ++i)
			scanf("%d",&b[i]);

		printf("%d\n",minTransforms(a,b,size));

	}
	return 0;
}
