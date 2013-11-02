//============================================================================
// Name        : Abccd.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
using namespace std;



//brute force backtracking solution
int  color(char** a, int idx, char choice, int count[4],int n){

	//reached past the end while coloring so return 1;
	if(idx==(2*n)+1)
		return 1;

	char original_choice = choice;
	do{
		if(a[1][idx-1]!=choice && a[0][idx]!=choice && (count[choice-'A']+1)<=n){
				count[choice-'A']++;
				char old = a[1][idx];
				a[1][idx] =choice;
				if(color(a,idx+1,'A' + ((choice-'A')+1)%4,count,n)==1){
					return 1;
				}
				else {
					count[choice-'A']--;
					a[1][idx] = old;
				}
		}
	    choice = 'A' + ((choice-'A')+1)%4;
	}while(choice!=original_choice);

	return 0;

}

//simple O(n) solution. This uses the fact than in any 2x2 subarray of the
//original array , there will be two distinct colors in the top row. So if we pick
//the remaining two colors for the lower row, then inside the 2x2 square we have 1
//cell of each color and therefore in N such squares(making a total of 4*N cells)
//we have N cells of each color. while filling the bottom row for the ith cell, we
//check if it is the same color as the (i-1)th row, if so , then we swap the ith and (i+1)th
//cell and the array comes back into order
char table[4] = {1,2,4,8};
void colorN(char** a, int n){

    for(int i=1; i< n<<1; i+=2){
    	char e = table[a[0][i]-'A'] + table[a[0][i+1]-'A'];
    	switch(e){
    	case 3:{a[1][i]='C'; a[1][i+1]='D'; break;}
    	case 5:{a[1][i]='B'; a[1][i+1]='D'; break;}
    	case 9:{a[1][i]='B'; a[1][i+1]='C'; break;}
    	case 6:{a[1][i]='A'; a[1][i+1]='D'; break;}
    	case 10:{a[1][i]='A'; a[1][i+1]='C'; break;}
    	case 12:{a[1][i]='A'; a[1][i+1]='B'; break;}
    	}
    	if(a[1][i-1]==a[1][i])
    		swap(a[1][i],a[1][i+1]);

    }
}

int main() {

	int n;
	scanf("%d",&n);
	char* str[2];
	str[0] = new char[2*n+2];
	str[1] = new char[2*n+2];
	str[0][0] = str[1][0]='E';
//	int count[4] = {0,0,0,0};
	scanf("%s",&str[0][1]);
//	for(int i=1 ; i<=2*n ; i++)
//		count[str[0][i]-'A']++;
	colorN(str,n);
//	color(str,1,str[0][1]+1,count,n);
	str[1][2*n+1]=0;
	printf("%s",&str[1][1]);
	delete[] str[0];
	delete[] str[1];

	return 0;
}
