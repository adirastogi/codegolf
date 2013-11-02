//============================================================================
// Name        : Acmaker.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to SPOJ ACMAKER:
// Description : Using Dynamic Programming
//============================================================================

#include <iostream>
#include <cstdio>
#include <set>
#include <cstring>
using namespace std;
int getNumWays(std::string words[150] , int n){

	std::string abbrev = words[0];
	int l = abbrev.size();
	/*the DP sate variable is defined as follows:
	num[i][j][k] = number of ways character i in the abbrev can be matched with character k in the jth word
	such that each following word j=j+1....n has at least one matching character
	*/
	int num[l][150][150];
	memset(num,0,l*150*150*sizeof(int));

	//fill the last row of the state table so that only matching chars in the last word are counted.
	bool setLast = false;
	for(int j=n-1; j>0 ;  --j)
		for (int k=words[j].size()-1 ; k>=0 ; --k)
			if(j==n-1 && tolower(abbrev[l-1])==words[j][k]){
				num[l-1][j][k]=1;
				setLast = true;
			}
			else num[l-1][j][k]=0;

	if(!setLast)
		return 0;

	//now start looking for matches
	for (int i=l-2; i >=0 ; --i){
		int j,k;
		for(j=i+1; j >0; --j){
			for (k=words[j].size()-1; k >=0 ; --k){
				if(tolower(abbrev[i])!=words[j][k])
					num[i][j][k]=0;
				else{
					//this word's sum
					int thisSum = 0;
					for(int p=k+1;p<words[j].size();p++)
						thisSum += num[i+1][j][p];
					//check if there is atleast one match in the next word
					int otherSum = 0;
					if(j+1<n){
						for(int q=0 ; q < words[j+1].size(); q++)
							otherSum += num[i+1][j+1][q];
					}

					num[i][j][k] = otherSum + thisSum;
				}
			}
		}
	}
	int debug = 1;
	if(debug){
		cout<<"\n-------------------------------------------------------\n";
		//debug print the entire matrix
		cout<<"  ";
		for(int j=1; j < n ; j++){
			for(int k=0 ; k < words[j].size() ; ++k)
				cout<<words[j][k]<<" ";
			cout<<" | ";
		}
		cout<<"\n";
		for( int i=0 ; i < abbrev.size() ;++i){
			cout<<abbrev[i]<<" ";
			for (int j=1; j <= i+1 && j< n; ++j){
				for(int k=0 ; k<words[j].size() ; ++k){
					cout<<num[i][j][k]<<" ";
				}
				cout<<" | ";
			}
			cout<<"\n";
		}
		cout<<"\n-------------------------------------------------------\n";
	}

	int ans = 0;
	//return the sum of the top row upto the correct value of j(1) & k
	for(int k=0; k < words[1].size() ; ++k)
				ans += num[0][1][k];

	return ans;

}

int main() {
	int nins=0;
	std::string words[150];
	char line[160];

	while(1){
		cin>>nins;
		cin.get();
		if(nins==0) break;
		std::set<std::string> insigWords;
		for(int i=0; i< nins; ++i){
			cin.getline(line,100);
			insigWords.insert(std::string(line));
		}
		//start reading the input
		while(1){

			cin.getline(line,160);
			if(!strcmp(line,"LAST CASE"))
				break;
			char* p = strtok(line," \n");
			int i = 0;
			while (p!=NULL){
				//the read token is a significant word
				if(insigWords.find(p)==insigWords.end()){
					words[i++] = std::string(p);
				}
				p = strtok(NULL," \n");
			}
			int n = getNumWays(words,i);
			if(n>0)
				std::cout<<words[0]<<" can be formed in "<<n<<" ways\n";
			else std::cout<<words[0]<<" is not a valid abbreviation\n";
		}

	}

	//std:: string words2[] = {"ACM","academy","domputer"};
	//std:: string words2[] = {"RADAR","radio","detection","ranging"};
	//std::string words3[] = {"APSC","ap","psec","psc","psc"};
	//getNumWays(words3,5);

}
