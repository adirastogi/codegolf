#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long double  vtype;


int main(){

	char str[10003];
	cin>>str;

	//strcpy(str,"*******************");
	vtype len = strlen(str);
	queue<vtype> q;
	q.push(1);
	vtype insertions = 1;
	for(int i=0; i < len ;i++){
		vtype count = 0;
		while(insertions > 0){
			vtype n = q.front();
			q.pop();
			insertions--;
			switch(str[i]){
			case 'L': q.push(2*n);count=1; break ;
			case 'R': q.push(2*n + 1); count=1;break;
			case 'P': q.push(n);count++; break;
			case '*': q.push(2*n); q.push(2*n + 1); q.push(n); count=3; break;
			}
		}
		insertions = count;
	}

	vtype qlen = q.size();
	vtype ans = 0;
	for(vtype i =0 ;i < qlen ; i++){
		ans += q.front();
		q.pop();
	}

	printf("%.0Lf",ans);
	return 0;
}
