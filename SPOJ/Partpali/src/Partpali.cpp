#include<iostream>
#include<math.h>
#include<cstring>
#define COEFF 0
#define LIMIT 1
using namespace std;
typedef unsigned long long vtype;

vtype  numSolutions(int eqn[][2] ,int n, vtype N){

    vtype p[n+1][N+1];
    memset(p,0,sizeof(vtype)*(n+1)*(N+1));
    
    //get to the first non-zero term in the equation
    int pos;
    for(pos = 1; pos<=n && !eqn[pos][COEFF];pos++);


    for(int k=0; k<=N ; k++){
        if((k%eqn[pos][COEFF]==0) && (k/eqn[pos][COEFF]<=eqn[pos][LIMIT]))
            p[pos][k] = 1;
        else p[pos][k] =0;
//        cout<<p[1][k]<<" ";
    }

//    cout<<"\n";
    
    for(int i=pos+1; i<= n; i++){
        for(int k=0; k <=N ; k++){
        	if(eqn[i][COEFF]==0)
        		eqn[i][LIMIT] = 0;
            for(int j=0; j<= eqn[i][LIMIT] ; j++){
                if(eqn[i][COEFF]*j <=k)
                p[i][k]  = p[i][k] + p[i-1][k-eqn[i][COEFF]*j];
                
            }
//            cout<<p[i][k]<<" ";
        }
//        cout<<"\n";
    }
//    cout<<"for "<<N<<": "<<p[n][N]<<"\n";
    vtype val = p[n][N];
    return p[n][N];
}
vtype pow10mod(vtype n,vtype num){
	if(n==0)
		return 1;
	vtype val = 1;
	for(int i=1; i <=n ; i++){
		val = ((val%num)*(10%num))%num;
	}
	return val;
}
vtype numPalindromes(int num, int len){

    //if its a multiple of 10 , return 0. No palindromes possible
    if(num%10==0)
        return 0;


    int nvar = len/2; 
    vtype maxval = 0;
    int eqn[nvar+2][2];
    int indep_digits = 0;
    for(int i=1;i<=len/2;i++){
        eqn[i][COEFF]= ((vtype)pow10mod(int(len-i),num) + (vtype)pow10mod(int(i-1),num))%num;

        if(eqn[i][COEFF]==0){
            //this digit can take any value, but in the diophantine equation , its coefficient becomes
            //zero so ,its values are not caounted and must be separately multiplied;If it is the first
            //digit , then it can take on 9 vals, otherwise 10 vals.
            indep_digits++;
            eqn[i][LIMIT]=0;
        }else{
        	  eqn[i][LIMIT]= 9;
        }

        maxval += eqn[i][COEFF]*9;
        
    }
    //odd length. one extra variable
    if(len%2==1){
        eqn[(len/2) + 1][COEFF] =  (vtype)pow10mod(int(len/2),num);
        if(eqn[(len/2) + 1][COEFF]==0)
            indep_digits++;
        eqn[(len/2) + 1][LIMIT] =  9;
        nvar+=1;
        maxval += eqn[(len/2) + 1][COEFF]*9;
    }


    int subtractand = eqn[1][COEFF];
    eqn[1][LIMIT] = 8;
    vtype count = 0;
    for(vtype i=num ; i<=maxval ; i+=num){
        count+= numSolutions(eqn,nvar,i-subtractand);
    }    


    //each independent digit can take 10 vals except for the first digit;
    if(indep_digits>0){

        if(count) 	count = count*pow(10,indep_digits);
        else 		count = pow(10,indep_digits);
        //if the first digit is also an independent digit , it can only take values from 1-9.
        if(eqn[1][COEFF]==0){
        	if(count)	count = 9*(count/10);
            else 		count = 9;
        }

    }






    return count;
}


int main(){

    //int eqn[][2] = {{0,0},{1,48},{1,48},{2,48},{3,48}};
    //int eqn[][2] = {{0,0},{1,48},{2,48},{3,48},{1,48}};
   
    //int eqn2[][2] = {{0,0},{2,9},{5,8}};
    int eqn3[][2] = {{0,0},{5,8},{2,9}};
    int d = 1;
    while(1){
    	int eqn[][2] = {{0,0},{5,8},{2,9}};
    	for(int i=1;i<=2;i++)
    	eqn[i][LIMIT] = eqn3[i][LIMIT]/d;
    	int count=numSolutions(eqn,2,12);
    	if(count==0)
    		break;
    	else d++;
    }

//	cout<<"\n"<<numSolutions(eqn3,2,40);
//    for(int i=1 ; i <=5 ; i++)
//    cout<<numPalindromes(30,3);
    int numcases;
    int num,len;
//    cout<<numPalindromes(359,18);
    cin>>numcases;
    for(int i=0; i< numcases; i++){
        cin>>num>>len;
        cout<<numPalindromes(num,len)<<"\n";
    }

}
