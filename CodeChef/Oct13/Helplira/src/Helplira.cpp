//============================================================================
// Name        : Helplira.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to Codechef HELPLIRA
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
int main() {

	int n ;
	double minarea =0;double maxarea = 0;
	int minpos = 0; int maxpos = 0;
	int x1,x2,x3,y1,y2,y3;
	scanf("%d",&n);
	int i=0;
	for(i=0; i< n; ++i){
		scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
		/* Move the origin to the first vertex to reduce number of multiplications*/
		x2 -= x1;
		y2 -= y1;
		x3 -= x1;
		y3 -= y1;
		double area = std::abs(double(x2*y3-x3*y2))/2;
		if(i==0){
			maxarea = minarea = area;
		}
		//printf("%f \n",area);
		if(area>=maxarea){
			maxarea = area;
			maxpos = i+1;
		}
		if(area<=minarea){
			minarea = area;
			minpos = i+1;
		}

	}
	printf("%d %d",minpos,maxpos);
	return 0;
}
