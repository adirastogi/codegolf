//============================================================================
// Name        : Books1.cpp
// Author      : Aditya
// Version     :
// Copyright   : Solution to SPOJ Books1 : http://www.spoj.com/problems/BOOKS1/
// Description : Solution using both binary search and dynamic programming.
//============================================================================

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
typedef  long long vtype;
template<class comparator>
vtype binsearch(vtype low, vtype high, comparator& place_divisions){
	vtype mid = 0;
	vtype l  = low;
	vtype h = high;
	vtype last_good =-1;
	bool fits = false;
	while(l<=h){
		mid = (l+h)/2;

		vtype val = place_divisions(mid);
		//estimate is too low
		if(val==-1){
			l = mid+1;
			//update last_good with the lower estimate if no good estimate has been found yet.
			fits = false;
			last_good = (last_good==-1)?mid:last_good;
		}
		//estimate is too high
		else if(val==1)
			h = mid-1;
		else{
			//estimate is just right, mark it as the last good estimate
			fits = true;
			last_good = mid;
			h=mid-1;
		}
	}
	if(fits)
		return last_good;
	else return -last_good;
}


struct Divide{
	vtype* books ;
	vtype size;
	vtype num_scribes;
	vtype maxval;
	Divide(vtype* arr, vtype s, vtype n):books(arr),size(s),num_scribes(n){}
	inline vtype operator()(vtype distance) const {
		vtype max_sum = 0;
		vtype div_sum = 0;
		vtype numdivs = 0;
		for(vtype i=0 ; i< size && numdivs<num_scribes; i++){
			//the distance is so low that it is less than even the book size
			if(books[i]>distance)
				return -1;
			if(div_sum+books[i]<=distance)
				div_sum+=books[i];
			else{
				//divide here
				numdivs++;
				//div_sum=books[i];
				div_sum=0;
				i--;
			}
			max_sum = std::max(max_sum,div_sum);
		}

		if(numdivs>=num_scribes){
			//too low estimate
			return -1;
		}
		else if(numdivs==num_scribes-1){
			//just right
			return 0;
		}
		//too high estimate
		else return 1;
	}
};
void printResults(vtype books[], vtype size , vtype num_scribes,vtype last_good){
	bool desc = true;
	vtype max_dist = 0;

	//if the value obtained by binary search is just right (i.e. optimum, in which case the
	// value of last_good is positive, then we should start dividing vtypeo partitions from the
	//back end as this value represents the upper bound for the max sum of a partition and to keep
	//the partitions in the front smaller, the partitions should be made as big as possible
	//starting from the back.
	//On the other hand, if the value obtained by binary search is not the optimum but represents
	//the best lower bound, then in that case the division of partitions should start from the front
	//end in order to keep the front partitions as small as possible.

	if(last_good<0){
		desc = false;
		max_dist = -last_good;
	}else{
		desc = true;
		max_dist = last_good;
	}
	vtype div_sum = 0;
	vtype back = -1;
	vtype divpos[num_scribes];

	//do a two way loop
	vtype limit = (desc)?-1:size;
	vtype start = (desc)?(size-1):0;
	vtype incr = (desc)?-1:1;
	for(vtype i=start; i!=limit && (back < (num_scribes-2)); i+=incr){
		if(div_sum+books[i]>max_dist){
			divpos[++back]=i+((desc)?1:0);
			div_sum = books[i];
		}
		else div_sum+=books[i];
	}

	//entries in divpos are depending upon the asc or desc traversal order so
	//take care of that.
	divpos[back+1] = -1;
	if(!desc)
		back = 0;

	for(vtype i=0;i<size;i++){
		if(divpos[back]==i){
			printf("/ ");
			back += (desc)?-1:1;
		}
		printf("%lld ",books[i]);
	}
}
void testCode(){

	setvbuf(stdout,NULL,_IOLBF,0);
	//vtype a[] = {1,2,4,3,5,1,2,7,4,2};
	//vtype a[] = {1,1,1,1,1};
	//vtype a[] = {1,2,3,4,5,6,7,8,9};
	vtype a[] = {10, 10, 20, 1200, 10, 10, 20, 1200};
	Divide d(a,8,6);
	vtype max_val = binsearch(10,2480,d);
	printResults(a,8,6,max_val);


}
int main() {
	testCode();
	return 0;
	vtype ncases = 0;
	vtype m,n;
	scanf("%lld",&ncases);
	for(vtype i =0 ; i < ncases ;i++){
		scanf("%lld",&m);
		scanf("%lld",&n);
		vtype p[m];
		vtype p_sum = 0;
		for(vtype j=0; j< m ; j++){
			scanf("%lld",&p[j]);
			p_sum += p[j];
		}
		Divide d(p,m,n);
		printResults(p,m,n,binsearch(p[0],p_sum,d));
		printf("\n");
	}
	return 0;
}
