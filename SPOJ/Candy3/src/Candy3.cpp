//============================================================================
// Name        : Candy3.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
typedef unsigned long long valtype;
int main() {

	valtype testcases;
	cin>>testcases;
	char dummy[10];

	for(valtype i = 0 ; i < testcases ; i++){
		cin.getline(dummy,2);
		valtype N,n;
		valtype sum = 0;
		cin>>N;
		for(valtype j = 0; j < N; j++){
			cin>>n;
			sum+=(n%N);
			//if(sum > N)
				//sum = sum%N;
		}
		if(sum%N==0)
			cout<<"YES\n";
		else cout<<"NO\n";
	}



	return 0;
}
