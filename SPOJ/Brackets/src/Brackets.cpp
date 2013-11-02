//============================================================================
// Name        : Brackets.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;
typedef  long long vtype;
#define LEFT_NODE(i) (2*(i))
#define RIGHT_NODE(i) (2*(i)+1)
typedef pair<int,int> Pair;
#define INVALID pair<int,int>(0,0)
#define toggle(x) {(x) = ((x)==')')?'(':')';}
#define abs(x)  ((x)>0)?(x):-(x);

template<class T, class F>
class SegmentTree{



	T* tree;			//array of type T used for storing the tree. T is the return type of the function that
						//we want to store on the range
	int numelems;		//number of nodes in the tree;
	F functor;			//The function object used to process the ranges in the tree; The functor is called
						//with indices for a range i,j and returns a value of type T representing the operation
						//performed on that range. The segment tree gices O(nlgn) performance for such range
						//operations

	public :
	SegmentTree(){

	}
	~SegmentTree(){
		delete[] tree;
	}

	//function used to query the tree
	T query(int node,int b, int e, int i, int j){
		 if (i > e || j < b)
		    return INVALID;
		if(b>=i && e<=j)
			return tree[node];
		else{
			T l = query(LEFT_NODE(node),b,(b+e)/2,i,j);
			T r = query(RIGHT_NODE(node),(b+e)/2 + 1, e, i,j);
			if(l==INVALID)			//denotes non-existent value
				return r;
			else if (r==INVALID)
				return l;
			else return functor(l,r);
		}
	}

	//function used to build the tree
	T build(int k, int i, int j){
		if(i==j)
			tree[k] = functor(i);
		else{
			T l =build(LEFT_NODE(k),i,(i+j)/2);
			T r = build(RIGHT_NODE(k),(i+j)/2 + 1,j);
			tree[k] = functor(l,r);
		}
		return tree[k];
	}

	//function used to update the tree after an element at pos in the underlying array is changed
	T update(int node,int b, int e, int pos){

		if(pos < b || pos > e)
			return tree[node];

		//check to see where does pos lie ?
		if(b==e)
			//pos is equal to required position , so  we must have reached a leaf
			tree[node] = functor(pos);
		else{
		    T l= update(LEFT_NODE(node),b,(b+e)/2,pos);
		    T r= update(RIGHT_NODE(node),(b+e)/2 +1,e,pos);
		    tree[node] = functor(l,r);
		}
		return tree[node];
	}

	SegmentTree(int len,F f):tree(0),numelems(0),functor(f){
		int lgn = 0;
		while(len>>=1)
			lgn++;
		//max number of elements in the heap would be 2*2^(lgn +1)
		numelems = 2<<(lgn + 1);
		tree = new T[numelems];

	}


};

//functor to calculate the number of opening and closing unbalanced brackets in a range
template <class T>
class BalancedBrackets{
	char* array;
	public:
	BalancedBrackets(){}
	BalancedBrackets(char* a):array(a){}
	//check if any closing brackets in the right range cancel out with the opening brackets in the left range.
	//otherwise just add them
	inline T operator()(T l, T r){
		int balance = l.first - r.second;
		int o ,c;
		if(balance >= 0){
			o = balance + r.first ;
			c = l.second;
		}else{
			o = r.first;
			c = l.second - balance ;
		}

		return T(o,c);

	}
	//the identity functor
	inline T operator()(int index){
		if(array[index]==')')
			return T(0,1);
		else return T(1,0);
	}
};


int main(){

	int n,m,k;
//	char b[] = "())(()";//"(()()";//"())(()";//")()(";//"(()(";
//	n = strlen(b);
//	BalancedBrackets<Pair> bb(b);
//	SegmentTree<Pair,BalancedBrackets<Pair> > st(4,bb);
//	st.build(1,0,n-1);
//	Pair p = st.query(1,0,n-1,0,n-1);
//	b[3] = ')';
//	st.update(1,0,n-1,3);
//	p =  st.query(1,0,n-1,0,n-1);

	for(int i=0 ; i< 10 ; i++){
		scanf("%d",&n);
		char buffer[n+2];
		scanf("%s",buffer);
		BalancedBrackets<Pair> bb(buffer);
		SegmentTree<Pair,BalancedBrackets<Pair> > st(n-1,bb);
		st.build(1,0,n-1);
		scanf("%d",&m);
		printf("Test %d:\n",i+1);
		for(int j = 0 ; j< m ; j++){
			scanf("%d",&k);
			if(k>0){
				toggle(buffer[k-1]);
				st.update(1,0,n-1,k-1);
			}
			else{
				Pair p = st.query(1,0,n-1,0,n-1);
				if(p.first==0 && p.second==0)
					printf("YES\n");
				else printf("NO\n");
			}
		}
	}
	return 0;
}
