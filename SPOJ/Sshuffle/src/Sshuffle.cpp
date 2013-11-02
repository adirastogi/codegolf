//============================================================================
// Name        : Sshuffle.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to SPOJ SSHUFFLE:
// Description : http://www.spoj.com/problems/SSHUFFLE/
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;
typedef int vtype;
static int scount = 0;
int dnum[10][10][10][10];
/* This basically uses the following DP state variable :
 * num[i][j][p][q] = number of ways of matching character i in string j(0 or 1)
 * starting with position p in string 0 and position q in string 1. It is necessary to keep
 * track of the starting positions of each string because the matching inside each string
 * must select elements from that string in order. Moreover, the values for p and q can extend
 * to 1 + length of each string as the selected subsequence from each string can also be empty and
 * a value pf 1 + length denoting that the particular substring being considered is empty.
 * Also , the state is propagated by the follwing :
 * The number of ways of matching element i of the string is the sum of all possible ways of matching
 * element i+1 of the string
*/
vtype dpSolve(std::string str1, std::string str2, std::string str3){

	vtype num[62][3][62][62];
	memset(num , 0, 62*3*62*62*sizeof(vtype));
	int debug = 0;

	std::string words[] = {str1,str2};

	/* Set the match count to 1 for the bottom most element in the original string and all starting substrings*/
	int l = str3.size();
	for(int p = 0 ; p <= words[0].size() ; ++p)
		for(int q =0; q <= words[1].size() ; ++q)
			if(str1[p]==str3[l-1]){
				if(debug) std::cout<<"n("<<l-1<<","<<"0"<<","<<p<<","<<q<<")=1"<<endl;
				num[l-1][0][p][q] = 1;
			}


	for(int q = 0 ; q <= words[1].size() ; ++q)
			for(int p =0; p <= words[0].size() ; ++p)
				if(str2[q]==str3[l-1]){
					if(debug) std::cout<<"n("<<l-1<<","<<"1"<<","<<p<<","<<q<<")=1"<<endl;
					num[l-1][1][p][q] = 1;
				}


	if(debug) std::cout<<endl<<"-------------------------------"<<endl;

	/* Now build the DP table */

	for(int i=l-2; i>=0 ; --i){
		for(int p=words[0].size(); p >= 0 ; --p){
			for(int q=words[1].size(); q >=0 ; --q){
				if(str3[i]==words[0][p]){
					vtype sum0=0;
					for(int k=p+1;k<words[0].size();++k)
						sum0 += num[i+1][0][k][q];
					for(int k=q; k<words[1].size();++k)
						sum0 += num[i+1][1][p+1][k];
					num[i][0][p][q] = sum0;
				}
				else num[i][0][p][q] = 0;
				if(debug) std::cout<<"n("<<i<<","<<"0"<<","<<p<<","<<q<<")="<<num[i][0][p][q]<<endl;
				if(str3[i]==words[1][q]){
					vtype sum1=0;
					for(int k=q+1;k<words[1].size();++k)
						sum1 += num[i+1][1][p][k];
					for(int k=p; k<words[0].size();++k)
						sum1 += num[i+1][0][k][q+1];
					num[i][1][p][q] = sum1;
				}
				else num[i][1][p][q] = 0;
				if(debug) std::cout<<"n("<<i<<","<<"1"<<","<<p<<","<<q<<")="<<num[i][1][p][q]<<endl;
			}
		}
	}

	vtype ans = 0;
	for(int p=0; p< words[0].size(); ++p)
		ans += num[0][0][p][0];

	for(int q=0; q< words[1].size(); ++q)
		ans += num[0][1][0][q];


	return ans;

}
vtype recursiveSolve(std::string s[2], std::string s3, int i, std::pair<int ,int> pos, int j){
	int debug  = 0;
	if(debug){
		std::cout<<"\n";
		scount++;
		for(int z=0; z<scount ; ++z)
			std::cout<<" ";
		std::cout<<"num("<<i<<","<<j<<","<<pos.first<<","<<pos.second<<")";
	}

	int sum=0;
	if(j==0){
		if(s3[i]!=s[0][pos.first])
			sum= 0;
		else{
			if(i==s3.size()-1)
				sum = 1;
			else {
				for(int k=pos.first+1; k<s[0].size() ; ++k)
					sum += recursiveSolve(s,s3,i+1,std::make_pair(k,pos.second),0);
				//search the other string as well
				for(int k=pos.second;k<s[1].size();++k)
					sum += recursiveSolve(s,s3,i+1,std::make_pair(pos.first+1,k),1);
			}
		}
	}else{
		if(s3[i]!=s[1][pos.second])
			sum = 0;
		else{
			if(i==s3.size()-1)
				sum = 1;
			else {
				for(int k=pos.second+1; k<s[1].size(); ++k)
					sum += recursiveSolve(s,s3,i+1,std::make_pair(pos.first,k),1);
				//search the other string as well
				for(int k=pos.first; k<s[0].size(); ++k)
					sum += recursiveSolve(s,s3,i+1,std::make_pair(k,pos.second+1),0);
			}
		}
	}

	if(debug){
	std::cout<<"\n";
		for(int z=0; z<scount ; ++z)
			std::cout<<" ";
		std::cout<<"sum="<<sum;
		dnum[i][pos.first][pos.second][j]=sum;
		scount--;
	}
	return sum;
}

vtype recursiveSolution(std::string str1,std::string str2,std::string str3){
	std::string s[] = {str1,str2};
	vtype n1=0;
	for(int i=0; i<str1.size(); ++i)
		n1 += recursiveSolve(s,str3,0,std::make_pair(i,0),0);
	vtype n2=0;
	for(int i=0; i<str2.size(); ++i)
		n2 += recursiveSolve(s,str3,0,std::make_pair(0,i),1);
	return n1 + n2;
}


int main() {
	vtype ncases;
	std::string str1, str2, str3;

   	std::cin>>ncases;
	for(int i=0 ; i<ncases; ++i){
		cin>>str1>>str2>>str3;
		vtype numways;
		numways = dpSolve(str1,str2,str3);
		//recursiveSolution(str1,str2,str3);
		std::cout<<numways<<endl;
	}

	return 0;


}
