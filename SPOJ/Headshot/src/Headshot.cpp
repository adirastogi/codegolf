//============================================================================
// Name        : Headshot.cpp
// Author      : Aditya
// Version     :
// Copyright   : SPOJ problem HEADSHOT : http://www.spoj.com/problems/HEADSHOT/
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;
#define SHOOT  1
#define ROTATE 2
#define EQUAL  3

int strategy(char* cyl, size_t size){

	double zeros = 0, safe_zeros= 0;
	for(int i=0; i< size;i++){
		if(cyl[i]=='0'){
			zeros++;
		if(cyl[(i+1)%size]=='0')
			safe_zeros++;
		}
	}
    double shoot = safe_zeros/zeros ;
    double rotate = zeros/double(size);

    //cout<<"shoot probabilitiy:"<<shoot<<"\n";
    //cout<<"rotate probability:"<<rotate<<"\n";

    if(shoot > rotate)
    	return SHOOT;
    else if(rotate > shoot)
    	return ROTATE;
    else return EQUAL;
}


int main() {
	char cylinder[101];
	//cout<<"Enter configuration\n";
	cin>>cylinder;
	switch(strategy(cylinder,strlen(cylinder))){
	case SHOOT:	cout<<"SHOOT";break;
	case ROTATE: cout<<"ROTATE";break;
	case EQUAL: cout<<"EQUAL"; break;
	}
	cout << "" << endl; // prints
	return 0;
}
