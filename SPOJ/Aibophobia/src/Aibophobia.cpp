//============================================================================
// Name        : Aibophobia.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
//============================================================================
#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
/*
* This is a memory efficient lcs method that takes only min(len(x),len(y))
* memory to calculate the length of the lcs. It does it by keeping track of the row
* along which the c[i,j]  values are being calculated and an additional variable to hold
* the value calculated for c[i,j-1] . At the same time , once c[i,j] has been calculated,
* the previous_iteration array is updated with the previous value. At the end of the inner loop,
* this array is thus ready for recycling in the next iteration in the outer loop. This procedure
* can only return length of the lcs and cannot keep track of the lcs in order to be memory efficient;
*/
typedef int lentype;
typedef int idxtype;
int efficient_lcs_length(char * x , char* y){

	lentype m = strlen(x);
	lentype n = strlen(y);
	int slen , llen;
	char * small_str, *large_str;
	if(m < n){
		small_str = x;
		large_str = y;
		slen = m;
		llen = n;
	}else{
		small_str = y;
		large_str = x;
		slen = n;
		llen = m;
	}


	lentype* prev_iteration = new lentype[slen+1];
	lentype  prev_val = 0, current_val =0;
	idxtype i , j;

	for(i = 0; i< slen+1 ; i++ )
		prev_iteration[i] = 0;

	for(i = 0 ; i < llen ; i ++){
		for(j = 1 ; j < slen+1 ; j++){
			if(large_str[i]==small_str[j-1]){
				current_val = prev_iteration[j-1] + 1;
			}else if(prev_val > prev_iteration[j])
				current_val = prev_val;
			else
				current_val = prev_iteration[j];
			prev_iteration[j-1] = prev_val;
			prev_val = current_val;
		}
		prev_iteration[j-1] = current_val;
		prev_val = 0;
	}
	lentype len = prev_iteration[slen];
	delete[] prev_iteration;
	return len;
}
/*
 * This function returns the minimum number of characters to be inserted to
 * make the string a palindrome
 */
lentype min_insert_palindrome(char* str){
	lentype l = strlen(str);
	char* revstr = new char[strlen(str)+1];
	for(idxtype i=0 ; i < l ; i++)
		revstr[l-1-i] = str[i];
	revstr[l] = NULL;
	lentype val = l - efficient_lcs_length(str,revstr);
	delete[] revstr;
	return val;
}
int main(){

	int numcases = 0;
	char buffer[6110];

	cin>>numcases;

	for(int i= 0 ; i<numcases ; i++){
		cin>>buffer;
		cout<<min_insert_palindrome(buffer)<<"\n";
	}

	return 0;
}
