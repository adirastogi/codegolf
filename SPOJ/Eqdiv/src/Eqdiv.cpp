//============================================================================
// Name        : Eqdiv.cpp
// Author      : Aditya
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;
typedef pair<int,int > node;
#define foreachAdj(p,n)  {												\
	int i = (p).first; int j = (p).second;								\
	int K[4],L[4];														\
	K[0]=i;K[1]=i-1;K[2]=i,K[3]=i+1;									\
	L[0]=j-1;L[1]=j;L[2]=j+1;L[3]=j;									\
	for(int x=0; x <4 ; x++){                           				\
		 if( K[x] >= 1 && K[x] <= (n) && L[x] >= 1 && L[x] <= (n)){		\
					int k=K[x],l=L[x];

#define endeachAdj                                                }     \
    }																	\
}
        



//return the count of contiguous elements with the same value as node (i,j)
int dfs(int g[][101], int n, int i, int j){

    int count = 1;

    //mark this node as currently being processed
    g[i][j] *= -1;
    foreachAdj(node(i,j),n)
    	//if it is unvisited and is of the same denomination then visit it.
    	if(g[k][l] > 0 && g[k][l]== (g[i][j]*-1)){
        count += dfs(g,n,k,l);
    	}
    endeachAdj

    return count;
}


//would have to use an iterative dfs here , to get through the time limit.
int dfsIterative(int g[][101], int n, int i , int j){

	vector<node> stack;
	g[i][j] *= -1;
	stack.push_back(node(i,j));
	int count=0;
	while(!stack.empty()){
		node p = stack.back();
		stack.pop_back();
		count++;
		foreachAdj(p,n)
			//if it is unvisited and is of the same denomination then visit it.
		    if(g[k][l] > 0 && g[k][l]== (g[i][j]*-1)){
		    	g[k][l] *= -1;
		        stack.push_back(node(k,l));
		    }
		endeachAdj

	}
	return count;
}

//do a dfs on the neighbours.
int isEquidiv(vector<node> start, int g[][101] , int n){

    //do a dfs from vertex(i,j) that is still untraversed
//	int numbers =0;
//	for(int i=1; i<= n; i++){
//        for(int j=1; j <= n; j++){
//            if(g[i][j] > 0 ){
//                int count = dfsIterative(g,n,i,j);
//                if(count!=n) return 0;
//                else numbers++;
//                if(numbers==n-1)return 1;
//            }
//        }
//    }

	int numbers = 0;
	while(!start.empty()){
		node p = start.back();
		start.pop_back();
		int count = dfsIterative(g,n,p.first,p.second);
		if(count!=n) return 0;
		else numbers++;
		if(numbers==n-1)return 1;
	}

    return 1;

}



int main() {
    
    int n;
    int g[101][101];
    char line[256];
    while(1){

    	cin.getline(line,256);
    	sscanf(line,"%d",&n);
//        scanf("%d",&n);
        if(n==0) break;

        for(int i=1;i<=n;i++)
            for(int j=1 ; j<=n;j++)
                g[i][j] = n;


        vector<node> start;
        for(int l=1 ; l<=n-1 ; l++){
        	cin.getline(line,256);
        	stringstream str(line,ios::in);
        	int i,j;
        	for(int k=1; k<=n ; k++){
                str>>i;
                str>>j;
                g[i][j] = l;
            }
        	start.push_back(node(i,j));
        }

//        cout<<"\n";
//        for(int i=0;i<=n+1;i++){
//            for(int j=0 ; j<=n+1;j++)
//                cout<<g[i][j]<<" ";
//            cout<<"\n";
//        }

        if(isEquidiv(start,g,n))
            cout<<"good\n";
        else cout<<"wrong\n";
    }


	return 0;
}
