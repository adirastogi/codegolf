//============================================================================
// Name        : Abcdef.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to SPOJ ABDEF: www.spoj.com/problems/ABCDEF/
// Description : Calculate the combinations on both the RHS and the LHS and then binary
//				 search for matches for each value in the LHS array in the RHS array
//============================================================================

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int combsRHS[1000005];
int combsLHS[1000005];
int set[105];
//this calculates combinations of type d(e+f)
int generateCombs(int set[], int size,int&l ,int&m){
	l = -1;m = -1;
	//printf("Printing RHS\n");
	for(int i=0; i<size ;++i){
		for(int j=0 ; j<size; ++j)
			for(int k=0 ; k < size; ++k){
				if(set[i]!=0)
					combsRHS[++l] = set[i]*(set[j]+set[k]);
				combsLHS[++m] = set[i]*set[j] + set[k];
				//printf("%d,%d,%d:%d\n",set[i],set[j],set[k],combsRHS[l]);
			}
	}
	return l;
}

int binsearch(int a[], int beg, int end,int key,int& lastmatch, int size){
	int l = beg;
	int h = end;
	int m = 0;
	while(l<=h){
		m = (l+h)/2;
		if(a[m]==key)
			break;
		else if (key<a[m])
			h = m-1;
		else l = m+1;
	}
	//if found then count the number of occurences and update the last good match
	if(a[m]==key){
		lastmatch=m;
		int i=m-1,j=m+1;
		int countup = 0;
		int countdown = 0;
		while(a[i]==key && i>=0)
			countup++,i--;
		while(a[j]==key && j<=size)
			countdown++,j++;
		return countup+countdown +1;
	}else{
		return 0;
	}
}
int compareAndCalculate(int set[],int size){
	int rsize,lsize;
	generateCombs(set,size,rsize,lsize);
	//sort the array to facilitate binary search
	std::sort(combsRHS,combsRHS+rsize+1);
	//for each element genrated in the lhs loop. search for it in the rhs array, multiply
	//by the number of occurrences of that element in the rhs array
	//printf("Printing LHS\n");
	int lastmatch = rsize;
	int totalCount = 0;
	for(int i=0; i<size ;++i)
		for(int j=0 ; j<size; ++j)
			for(int k=0 ; k < size; ++k){
				int lhsval = set[i]*set[j]+set[k];
				int matchCount = 0;
				//printf("%d,%d,%d:%d\n",set[i],set[j],set[k],lhsval);
				if(lhsval<=combsRHS[lastmatch]){
					matchCount = binsearch(combsRHS,0,lastmatch,lhsval,lastmatch,rsize);
				}else{
					matchCount = binsearch(combsRHS,lastmatch+1,rsize,lhsval,lastmatch,rsize);
				}
				totalCount += matchCount;
			}
	return totalCount;
}
int compareAndCalculate2(int set[],int size){
	int rsize,lsize;
	generateCombs(set,size,rsize,lsize);
	//sort the array to facilitate binary search
	std::sort(combsRHS,combsRHS+rsize+1);
	std::sort(combsLHS,combsLHS+lsize+1);
	//for each element generated in the lhs loop, search for it in the rhs array, multiply
	//by the number of occurrences of that element in the rhs array
	int i=0;
	int lastmatch = rsize;
	int totalCount = 0;
	while(i<=lsize){
		int matchCount = 0;
		if(combsLHS[i]<=combsRHS[lastmatch]){
			matchCount = binsearch(combsRHS,0,lastmatch,combsLHS[i],lastmatch,rsize);
		}else{
			matchCount = binsearch(combsRHS,lastmatch+1,rsize,combsLHS[i],lastmatch,rsize);
		}
		//skip till the next distinct value
		int cSame = 1;
		while(combsLHS[i]==combsLHS[i+1] && i<lsize)
			cSame++,i++;
		totalCount += matchCount*cSame;
		i++;
	}
	return totalCount;
}
int main() {
//	cout << "Solving the SPOJ problem Abcdef" << endl; // prints Solving the SPOJ problem Abcdef
//	int set[] = {0,1};
//	cout<<"\n"<<compareAndCalculate2(set,2)<<"\n";
	int nelems;
	scanf("%d",&nelems);
	for(int i=0; i<nelems ; i++)
		scanf("%d",&set[i]);
	int count = compareAndCalculate2(set,nelems);
	printf("%d",count);
	return 0;
}
