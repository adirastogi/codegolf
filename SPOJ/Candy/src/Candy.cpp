//============================================================================
// Name        : Candy.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
typedef long valuetype;
int main() {

	valuetype N;
	while(1){
		valuetype sum= 0,equal = 0, ans = 0;
		cin>>N;
		if(N==-1)break;
		valuetype values[10000];
		for(valuetype i=0;i<N;i++){
			cin>>values[i];
			sum+=values[i];
		}
		if(sum%N!=0)
			ans = -1;
		else{
			equal = sum/N;
			for(valuetype i = 0; i < N ; i++){
				if(values[i]<equal)
					ans += (equal-values[i]);
			}
		}
		cout<<ans<<"\n";
	}


	return 0;
}
