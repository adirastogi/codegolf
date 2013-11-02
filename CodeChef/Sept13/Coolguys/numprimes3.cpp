//Solution to CODECHEF problem
#include <iostream>
#include <math.h>
#include <cstdio>
#define multiples(s,e,k) ((((s)%(k)==0) || ((e)%(k)==0))?(((e)-(s))/(k) + 1):(((e)-(s))/(k)))
    
using namespace std;
typedef unsigned long long int type;
type gcd(type a , type b){

    while (a!=0 && b!=0 ){
        if(a>b)
            a = a%b;
        else 
            b = b%a;
    }
   return (a==0)?b:a;
}
int main(){

    type t,p,q,n;
    scanf("%llu",&t);
    for (int i=0 ; i< t ; i++){
        scanf("%llu",&n);
        {
            p = n*2 -1;
            type nsq = sqrt(n);
            for (int i=2; i <=nsq ; ++i){
                type muls = (n < (i*i+1))?0:multiples(i*i+1,n,i);
                p = p + 2*muls + 1;
            }
            q = n*n;
            type cf = gcd(q,p);
            p = p/cf;
            q = q/cf;
        }
        printf("%llu/%llu\n",p,q);
    }

}
