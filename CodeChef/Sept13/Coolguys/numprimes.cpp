#include <iostream>
using namespace std;
typedef unsigned long long int type;
inline type multiples(type s , type e, type k){
    if(e < s) return 0;
    if(s%k==0 || e%k==0)
        return (e-s)/k +1;
    else
        return (e-s)/k;
}
int main(){
    type t,n,i,numbers;
    cin>>t;
    for(int k=0;k<t;k++){
        cin>>n;
        numbers = 0;
        for(i=1; i<=n/2; ++i)
            numbers += multiples(1,n,i)-1;
        numbers += n;
        cout<<numbers<<"/"<<n*n<<"\n";   
    }
   return 0; 
}
