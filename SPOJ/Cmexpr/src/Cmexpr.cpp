//============================================================================
// Name        : Cmexpr.cpp
// Author      : Aditya
// Version     :
// Copyright   : 
// Description : Solution to SPOJ CMEXPR.
//				 To get the minimum number of parantheses , first build the
//				 syntax tree and then walk the syntax tree deciding whether to parenthesize
//				 an expression or not based on the relative precedence of ops on two nodes.
//============================================================================

#include <iostream>
#include <cstring>
#include <ctype.h>
#define MAXEXPRLEN 300
#define TOKENTYPE(x) isalnum((x))?'o':((x)==')')?'R':((x)=='(')?'L':'O'
#define prec(x)  (((x)=='+')?1:\
				 ((x)=='-')?1:\
				 ((x)=='*')?3:\
				 ((x)=='/')?3:\
				 ((x)=='$')?-1:0)


#define tpos(x) (isalnum((x)))?4:((((x)-42>4)?2:(x)-42))
//relative precedence matrix
static int prec_table[4][5] = {
	/*	 	 * + / - x */
	/* * */	{0,3,0,3,0},
	/* + */	{0,0,0,0,0},
	/* / */	{2,3,2,3,0},
	/* - */	{0,2,0,2,0}
};

using namespace std;
struct node{
	node* lop;
	char op;
	node* rop;
};

node* build_tree(char*,int len);
void print_postfix(node* root){
	if(!root)
		return;
	print_postfix(root->lop);
	print_postfix(root->rop);
	cout<<root->op;
}
void print_infix(node* root){

	if(!root)
		return;

	char t = TOKENTYPE(root->op);
	int open=0;

	if(t=='O' && (prec_table[tpos(root->op)][tpos(root->lop->op)]&1)){
		cout<<"(";
		open=1;
	}

	print_infix(root->lop);
	if(open)cout<<")";


	cout<<root->op;
	open=0;
	if(t=='O' && (prec_table[tpos(root->op)][tpos(root->rop->op)]&2)){
		cout<<'(';
		open=1;
	}

	print_infix(root->rop);
	if(open)cout<<")";

}

int main() {

//	//node* tree = build_tree("a*((b-c-(d-e))/(f-g*h))!");
//	node* tree = build_tree("(a*b)+(a-(c-d))!",17);
//	print_postfix(tree);
//	cout<<endl;
//	print_infix(tree);
//	cout<<endl;

	int n;
	cin>>n;
	char expr[300];
	for(int i=0; i<n;i++){
		cin>>expr;
		//cout<<"**"<<expr<<endl;
		int len = strlen(expr);
		expr[len]='!';
		expr[len+1]='\0';
		node* tree = build_tree(expr,len);
		print_infix(tree);
		cout<<endl;
	}


}
node* build_tree(char* infix, int len){

	char * stack = new char[len+2];
	node**  tree_stack = new node*[len+2];
	stack[0]='$';
	int top = 0;
	int tree_top=-1;

	char * p = infix;
	while(*p){

		switch(TOKENTYPE(*p)){
		case 'o':{
			//get a new id node
			struct node* n = new node;
			n->lop = n->rop = NULL;
			n->op = *p;
			tree_stack[++tree_top]= n;
			break;
		}
		case 'O':{
			while(prec(*p) <= prec(stack[top])){
				//new op node
				struct node* n = new node;
				n->lop = tree_stack[tree_top-1];
				n->rop = tree_stack[tree_top];
				n->op = stack[top];
				tree_top -=2;
				tree_stack[++tree_top] =n;
				top--;
			}
			stack[++top] = *p;
			break;
		}
		case 'L':{
			stack[++top] = *p;
			break;
		}
		case 'R':{
			while(stack[top]!='('){
				struct node* n = new node;
				n->lop = tree_stack[tree_top-1];
				n->rop = tree_stack[tree_top];
				n->op = stack[top];
				tree_top -=2;
				tree_stack[++tree_top] =n;
				top--;
			}
			top--;
			break;
		}
		}

		p++;
	}
	return tree_stack[tree_top];
}
