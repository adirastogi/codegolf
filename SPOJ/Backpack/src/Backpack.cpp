#include <iostream>
#include <cstring>
#define VOL  0
#define COST 1
#define MAIN 2
#define ATTACH 3
#define A0(items,i)  i
#define A1(items,i)  items[A0(items,i)][MAIN]
#define A2(items,i)  items[A1(items,i)][MAIN]	
#define A3(items,i)  items[A2(items,i)][MAIN]
#define volume(items,i,j)  items[A##j(items,i)][VOL]
#define cost(items,i,j) (items[A##j(items,i)][COST])*(items[A##j(items,i)][VOL])
using namespace std;

typedef int vtype;


vtype calculateCost(vtype items[][4],  vtype n , vtype vmax){

	//the DP cost matricx
	vtype cmat[61][3201];

	for(int i=0 ; i <= n ; i++)
		cmat[i][0] = 0 ;
	
	for(int v= 0 ; v<= vmax; v++)
		cmat[0][v] = 0;

	for(int i = 1 ; i <=n ; i++){
		for(int v = 0 ; v <=vmax ; v++){
			if(items[i][ATTACH]!=1 && items[i][VOL] <= v){
				//this is not an atachment and can be included;
				//iterate over all combinations of attachments
				vtype max_cost = cost(items,i,0);
				vtype max_vol = volume(items,i,0);
				for(int j=1; j<7 ; j++)
				switch(j){
				//take one attachment
				case 1: max_cost = (volume(items,i,0) + volume(items,i,1) <= v)? max(max_cost,cost(items,i,0)+cost(items,i,1)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,1) <= v)? volume(items,i,0)+volume(items,i,1):max_vol;break;
				case 2: max_cost = (volume(items,i,0) + volume(items,i,2) <= v)? max(max_cost,cost(items,i,0)+cost(items,i,2)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,2) <= v)? volume(items,i,0)+volume(items,i,2):max_vol;break;
				case 3: max_cost = (volume(items,i,0) + volume(items,i,3) <= v)? max(max_cost,cost(items,i,0)+cost(items,i,3)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,3) <= v)? volume(items,i,0)+volume(items,i,3):max_vol;break;
				
				//take two attachments	
				case 4: max_cost = (volume(items,i,0) + volume(items,i,1) + volume(items,i,2) <= v)?
					max(max_cost,cost(items,i,0) + cost(items,i,1) + cost(items,i,2)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,1) + volume(items,i,2) <= v)?
					volume(items,i,0) + volume(items,i,1) + volume(items,i,2):max_vol;break;
				
				case 5: max_cost = (volume(items,i,0) + volume(items,i,2) + volume(items,i,3) <= v)?
					max(max_cost,cost(items,i,0) + cost(items,i,2) + cost(items,i,3)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,2) + volume(items,i,3) <= v)?
					volume(items,i,0) + volume(items,i,2) + volume(items,i,3):max_vol;break;
				
				case 6: max_cost = (volume(items,i,0) + volume(items,i,1) + volume(items,i,3) <= v)?
					max(max_cost,cost(items,i,0) + cost(items,i,1) + cost(items,i,3)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,1) + volume(items,i,3) <= v)?
					volume(items,i,0) + volume(items,i,1) + volume(items,i,3):max_vol;break;
					
				//take all three attachments
				case 7: max_cost = (volume(items,i,0) + volume(items,i,1) + volume(items,i,2) + volume(items,i,3) <= v)?
					max(max_cost,cost(items,i,0) + cost(items,i,1) + cost(items,i,2) + cost(items,i,3)):max_cost;
					max_vol = (volume(items,i,0) + volume(items,i,1) + volume(items,i,2) + volume(items,i,3) <= v)?
					volume(items,i,0) + volume(items,i,1) + volume(items,i,2) + volume(items,i,3): max_vol;break;
				};
				
				cmat[i][v] = max(cmat[i-1][v], max_cost + cmat[i-1][v-max_vol]);
									
			}
			else cmat[i][v] = cmat[i-1][v]; 
		}
	}
			 
	return 10*cmat[n][vmax];
}


int main(){
	
	vtype items[61][4];
	memset(items,0,sizeof(int)*61*4);
	vtype numcases;
	cin>>numcases;
	for(int i=0; i<numcases ; i++){
		vtype n,vmax;
		cin>>vmax>>n;
		for(int j = 1; j <= n; j++){
			cin>>items[j][VOL]>>items[j][COST]>>items[j][MAIN];
			items[j][VOL]/=10;
			if(items[j][MAIN])items[j][ATTACH]=1;
			//negative volume to mark attachment items
			//reverse the order of links so that each item is added to
			//the linked list of attachments starting at its's main item
			vtype idx = j;
			while(items[idx][MAIN])idx = items[idx][MAIN];
			if(idx)
			items[idx][MAIN] = j;
			items[j][MAIN] = 0;
		}
		cout<<calculateCost(items,n,vmax/10)<<"\n";
		
	}
	


}
