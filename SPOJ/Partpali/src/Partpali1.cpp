#include<iostream>
#include<cassert>
#include<cstring>
using namespace std;
typedef unsigned long long vtype;

inline vtype pow10mod(int i, int n){

    if(i==0)
        return 1;

    vtype val = 1;
    for(int k=1; k <= i ;k++)
        val = ((val%n)*(10%n))%n;
    return val;
}

inline vtype numPalindromes(int n, int l){



	vtype z[l+1][n+1];
	memset(z,0,sizeof(vtype)*(l+1)*(n+1));

    //No of palindromes of length zero that are perfectly divisible
    //by the number = 1
    z[0][0]=1;

    for(int i=0; i<=9 ; i++){
        //set the count for palindromes of length 1 and 2.
        z[1][i%n] += 1; 
        if(l>=2)
        z[2][(10*i+i)%n] += 1;
    }

    //for palindromes of length 2 and above , break it into
    //palindromes of length l-2 and check each of those to satisf38y the
    //calculation for the current remainder

    for(int k =3 ; k <=l; k++){
    	int idx = pow10mod(k-1,n);
    	vtype sumk=0;
        for(int r = 0  ; r < n ; r++){
            for(int i=(k==l)?1:0 ; i<=9 ; i++){
                int j = ((i%n)*(idx%n) + (i%n))%n;

                z[k][(10*r+j)%n]  += z[k-2][r];
            }
        }

    }
    
    if(l<=2)
    	return z[l][0]-1 ;
    else return z[l][0];
}
    

int main(){


	int numcases;
	int num,len;
	cin>>numcases;
	for(int i=0; i< numcases; i++){
		cin>>num>>len;
		cout<<numPalindromes(num,len)<<"\n";
	}

    return 0;
}
