/*
 * Histogra2.cpp
 *
 *  Created on: 16-Mar-2013
 *      Author: vader
 */


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

#define MAXLEN 1000000
#define MAXLOGN 20
#define INDEX 0
#define PREV  1
#define HEIGHT 0
#define AREA 1
using namespace std;
typedef  long long vtype;
typedef pair<int,int> bar;

void createTable(int **M , int* A, int N){


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


int minPos(int **M, int* A, int i, int j){
	int p =1;
	int l = j-i+1;
	int k=0;
	while(l>>=1){
		k++;
	}
	p=p<<k;
	if(A[M[i][k]] <= A[M[j-p+1][k]])
		return M[i][k];
	else return M[j-p+1][k];

}

/*
 * Function that offers an O(nlgn) solution to the problem. The solution works by dividing the histogram
 * array at its smallest element. The max area under the histogram is then given by
 * 			max (area_left_subhistogram, area-right_subhistogram, len*height of samllest element).
 * To get the minimum in each sub-histogram in O(1) time we build a lookup table in O(nlgn) time as described here :
 * 			http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor.
 * The table entry M[i][j] represents the index of the min element in the range starting at i and of length
 * 2^j. The overall complexity thus comes out to be O(nlgn).
 */
vtype largestRectangle(int **M,int* hist, int i , int j){
	if(j<i)
		return 0;

	if(j==i)
		return hist[i];

	int len = j-i+1;

	int minpos = minPos(M,hist,i,j);
	vtype middle_area = vtype(hist[minpos])*vtype(len);
	vtype left_area = largestRectangle(M,hist,i,minpos-1);
	vtype right_area = largestRectangle(M,hist,minpos+1,j);
	return max(max(middle_area,left_area),right_area);
}

/* Function that gives O(n) solution to the problem. The idea is that the maximum are rectangle completely
 * containing a bar will have height equal to the height of the bar. So if we calculate the maximum area
 * rectangle for each bar, we can get the global maximum. Also the maximum are rectangle for each bar will
 * be bounded by the 2 nearest neighbors that are smaller than the bar. So if we find that range, we can
 * calculate the area for the bar. To do this we use a stack to keep track of the currently unsolved bar at
 * the top. Each element in the stack also stores a pointer to the first element that was seen before this
 * element and is smaller that the element. For each current element processed from the hist we compare it
 * against the element at the top of the stack. If the element is smaller, we can emd the rectangle of the
 * element tracked on the top of the stack and so we pop it. If the current element is larger, then we can
 * continue to grow the rectangle and so we push it to the stack. we do nothing for duplicate elems as their
 * ans is going to be the same and will be calculated when the last duplicate elem is pushed on the stack.
 * This way we reach the solution in O(n) time.
 */
vtype largestReactangle(vtype *hist[2] , int n){

	int *stack[2];
	stack[INDEX] = new int[n+2];
	stack[PREV] = new int[n+2];
	int top = 0, current_bar = 1;

	//push the sentinel element on top of the stack
	stack[INDEX][top] = stack[PREV][top] = 0;

	//push the sentinel element at the end of the histogram
	hist[HEIGHT][n+1] = hist[AREA][n+1] = -1;
	hist[HEIGHT][0] = hist[AREA][0] = -1;


	while(current_bar <=n+1 && top >=0){
		if(hist[HEIGHT][current_bar] < hist[HEIGHT][stack[INDEX][top]]){
			vtype width = vtype(vtype(current_bar)-vtype(stack[PREV][top]))-1;
			hist[AREA][stack[INDEX][top]] = width*vtype(hist[HEIGHT][stack[INDEX][top]]);
			top--;
		}else if(hist[HEIGHT][current_bar] > hist[HEIGHT][stack[INDEX][top]]){
			top++;
			stack[INDEX][top] = current_bar;
			stack[PREV][top] = stack[INDEX][top-1];
			current_bar++;
		}else{
			//set the area fpr the last duplicate to zero
			hist[AREA][stack[INDEX][top]] = 0;
			stack[INDEX][top] = current_bar;
			current_bar++;
		}
	}

	//get the max area from the histogram
	int maxpos = 1;
	for(int i=1; i <=n ;i++)
		maxpos = (hist[AREA][i] > hist[AREA][maxpos])?i:maxpos;

	delete[] stack[0];
	delete[] stack[1];

	return hist[AREA][maxpos];

}




void solveNlgN(){
	int n;
	while(1){
		scanf("%d",&n);
		int* hist = new int[n+1];
		int **M = new int*[n+1];
		for(int i=0;i<n+1;i++)
			M[i] = new int[MAXLOGN];

		if(n==0)
			break;
		for(int i=0 ; i<n ;i++){
			scanf("%d",&hist[i]);
		}

		createTable(M,hist,n);
		cout<<largestRectangle(M,hist,0,n-1)<<"\n";

		delete[] hist;
		for(int i=0; i <n+1 ; i++)
			delete[] M[i];
		delete[] M;
	}
}

void solveLinear(){

	int n;
	while(1){
		scanf("%d",&n);
		if(n==0)
			break;
		vtype* hist[2];
		hist[0] = new vtype[n+3];
		hist[1] = new vtype[n+3];
		for(int i =1 ; i<= n ; i++)
			scanf("%lld",&hist[HEIGHT][i]);
		cout<<largestReactangle(hist,n)<<"\n";

		delete[] hist[0];
		delete[] hist[1];
	}

}

int main(){

	//solveNlgN();
	solveLinear();



	return 0;
}

