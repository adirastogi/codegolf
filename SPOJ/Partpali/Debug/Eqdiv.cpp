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
using namespace std;
#define foreachAdj(i,j,n)  for(int k=(i)-1; k <=(i)+1 ; k+=2){                           \
                                     for(int l=(j)-1 ; l<=(j)+1 ; l+=2){                 \
                                        if( k >= 1 && k <= (n) && l >= 1 && l <= (n)){ 

#define endeachAdj                                                                }      \
                                      }                                                  \
                                 }
        



//return the count of contiguous elements with the same value as node (i,j)
int dfs(int g[][7], int n, int i, int j){

    int count = 1;

    //mark this node as currently being processed
    g[i][j] *= -1;
    foreachAdj(i,j,n)
    //if it is unvisited and is of the same denomination then visit it.
    if(g[k][l] > 0 && g[k][l]== (g[i][j]*-1)){
        count += dfs(g,n,k,l);
    }
    endeachAdj

    return count;
}

//do a dfs on the neighbours.
int isEquidiv(int g[][7] , int n){

    //do a dfs from vertex(i,j) that is still untraversed
    for(int i=1; i<= n; i++){
        for(int j=1; j <= n; j++){
            if(g[i][j] > 0 ){
                int count = dfs(g,n,i,j);
                if(count!=n) return 0;
            }
        }
    }

    return 1;

}



int main() {
    
    int n;
    int g[7][7];
    
    while(1){
        scanf("%d",&n);
        if(n==0) break;
        for(int i=0;i<=n+1;i++)
            for(int j=0 ; j<=n+1;j++)
                g[i][j] = 1;
        //memset(g,0,sizeof(int)*(n+1)*(n+1));
        for(int l=1 ; l<=n-1 ; l++){
            for(int k=1; k<=n ; k++){
                int i,j;
                cin>>i>>j;
                //scanf("%d",&j);
                g[i][j] = l+1;

            }

        }

        cout<<"\n";
        for(int i=0;i<=n+1;i++){
            for(int j=0 ; j<=n+1;j++)
                cout<<g[i][j]<<" ";
            cout<<"\n";
        }


        if(isEquidiv(g,n))
            cout<<"good\n";
        else cout<<"wrong\n";
    }


	return 0;
}
