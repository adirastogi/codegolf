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
void numFactors(type n, type& p , type& q){

    /* Count the pairs (k,1) and (k,k) for k in [1,n] and exclude (1,1,) */
    p = n*2 -1; 


    /* Now we only need count factors upto \|n as on factor of each number in the range
       [1-n] will be less than \|n . So the number of factors will be double that number.
       But when we start counting factors by counting multiples upto \|n , we  will also 
       be counting numbers that have more than one factor ( such as 6) twice this 
       way. Now for each number , while counting its multiples we notice that all the multiples
       less than k^2 would already have been covered while counting the multiples arising of
       the numbers in the range [1,k-1]. So for each k belonging to [1,\|n] we begin our 
       counting at k^2. Also this pair must only be counted once as both its factors are same.
    */
    type nsq = sqrt(n);
    for (int i=2; i <=nsq ; ++i){
        type muls = (n < (i*i+1))?0:multiples(i*i+1,n,i);
        p = p + 2*muls + 1;
    }
    q = n*n;

    /* calculate the gcd of the two numbers to bring to lowest fraction*/
    type cf = gcd(q,p);
    p = p/cf;
    q = q/cf;

}
int main(){

    type t,p,q,n;
    scanf("%llu",&t);
    for (int i=0 ; i< t ; i++){
        scanf("%llu",&n);
        numFactors(n,p,q);
        printf("%llu/%llu\n",p,q);
    }

}
