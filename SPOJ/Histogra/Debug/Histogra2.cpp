/*
 * Histogra2.cpp
 *
 *  Created on: 16-Mar-2013
 *      Author: vader
 */


#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXLEN 1000000
#define MAXLOGN 20
using namespace std;
typedef  long long vtype;

void createTable(int M[MAXLEN][MAXLOGN], int A[MAXLEN], int N){


	int i, j;

	//initialize M for the intervals with length 1
	for (i = 0; i < N; i++)
		M[i][0] = i;
	//compute values from smaller to bigger intervals
	for (j = 1; 1 << j <= N; j++)
		for (i = 0; i + (1 << j) - 1 < N; i++)
			if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
				M[i][j] = M[i][j - 1];
			else
				M[i][j] = M[i + (1 << (j - 1))][j - 1];

}

int minPos(int M[MAXLEN][MAXLOGN], int A[MAXLEN], int i, int j){
	int p =1;
	int l = j-1+1;
	int k=0;
	while(l>>=2)
		k++;
	p=p<<(k+1);
	if(A[M[i][k]] <= A[M[j-p+1][k]])
		return A[M[i][k]];
	else return A[M[j-p+1][k]];

}

vtype largestRectangle(int M[MAXLEN][MAXLOGN],int hist[], int i , int j){
	if(j<i)
		return 0;

	if(j==i)
		return hist[i];

	int len = j-i+1;

	//calculate the position of the smallest bar in the histogram.
//	int minpos = i;
//	vtype min = hist[minpos];
//	for(int k=i ; k<=j ; k++){
//		if(hist[k] < min)
//			minpos = k;
//	}
	int minpos = minPos(M,hist,i,j);
	vtype middle_area = hist[minpos]*len;
	vtype left_area = largestRectangle(M,hist,i,minpos-1);
	vtype right_area = largestRectangle(M,hist,minpos+1,j);
	return max(max(middle_area,left_area),right_area);
}

int main(){
	int hist[1000];
	int M[1000][MAXLOGN];
	int n;
	while(1){
		cin>>n;
		if(n==0)
			break;
		for(int i=0 ; i<n ;i++){
			cin>>hist[i];
		}
		memset(M,0,sizeof(int)*1000*MAXLOGN);
		createTable(M,hist,n);
		cout<<largestRectangle(M,hist,0,n-1)<<"\n";

	}
	return 0;
}

