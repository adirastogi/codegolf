//============================================================================
// Name        : Aglarond.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;
typedef int vtype;
vtype compare (const void * a, const void * b)
{
  return ( *(vtype*)a - *(vtype*)b );
}
vtype findMaxOns(vtype* numOns, vtype n, vtype m, vtype k,vtype smaller){
	qsort(numOns,n,sizeof(vtype),compare);
	vtype ans = 0;
	vtype x = (k < smaller)?k:smaller;

	for(vtype i = 0; i< n ; i++){
		if(i < x) numOns[i] = m - numOns[i];
		ans += numOns[i];
	}

	vtype r = (k-smaller);


	vtype smallend = (x==0)?0:x-1;
	vtype bigend = (x==n)?x-1:x;

	if(r>0 && r %2 ==1)
		ans = ans + m - 2*((numOns[smallend]<numOns[bigend])?numOns[smallend]:numOns[bigend]);

	return ans;
}
int main() {

	vtype testcases;
	cin>>testcases;
	char ch;
	for(vtype l =0; l<testcases; l++){
		vtype n, m, k;
		vtype smaller = 0;
		cin>>n>>m>>k;
		vtype numOn[55];
		for(vtype i=0; i<n;i++){
			numOn[i] = 0;
			for(vtype j = 0; j< m ; j++){
				cin>>ch;
				if(ch=='*')
					numOn[i]++;
			}
			if(numOn[i]<=m/2)
				smaller++;
		}

		vtype ans = findMaxOns(numOn,n,m,k,smaller);
		cout<<ans<<"\n";
	}


	return 0;
}
