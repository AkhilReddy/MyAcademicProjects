//Be carefull and concentrate at /****/

#include<iostream>
using namespace std;
#include<stdlib.h>
#define max 20

/****/enum marker{V,NV};//Here marked is a user created data type which contains only values as Y and N .

struct node
{
	char name;
	node *v;//Pointer to node for vertical movement of nodes in graph
	node *e;//Pointer to node for horizontal movement of nodes in graph
	enum marker m;
};

/* Stack Creation */
void DFS();
struct node *stack[max];
int top=-1;
void push(struct node *h);
struct node *pop();

struct node *newnode,*first/*Stores Index of graph*/,*tempry,*store,*dummy/*Stores Index of graph and used in crating V link with other nodes */;

main()
{
	int n,x=0/* Just to have proper initalisation of index node */,i,j,no_ofedges;
	char a,b;
	
//	struct node *newnode,*first/*Stores Index of graph*/,*tempry,*store,*dummy/*Stores Index of graph and used in crating V link with other nodes */;
	
	cout<<"How many vertices are there ? :- ";
	cin>>n;
	cout<<"\n\tEnter all vertices names:\n";
	for(i=1;i<=n;i++)
	{
		if(x==0)
		{
			newnode = new (struct node);
			cin>>newnode->name;
			first = newnode;
			dummy = newnode;
			newnode->v = NULL;
			newnode->e = NULL;
			newnode->m = NV;//Not visited
			x++;//makes that we never come to this conditional
		}
		else
		{
			newnode = new (struct node);
			cin>>newnode->name;
			newnode->v = NULL;
			newnode->e = NULL;
			newnode->m = NV;
			dummy->v = newnode;
			dummy = newnode;
		}
		
	}
	
	cout<<"\nEnter the edges between vertices as :----> a b if there is edge between a and b\n";
	cout<<"Note:Enter 0 0 if over\n\n";
	
	no_ofedges = n*(n-1);
	
	for(j=1;j<no_ofedges;j++)
	{
		cin>>a>>b; /*****/ //An important feature of c++
		if(a =='0' && b =='0')
		{
			break;
		}
		dummy = first;
		while(dummy != NULL && dummy->name != a)//To make v pointer to move to exact 'a' in Graph
		{
			dummy=dummy->v;
		}
		
		if( dummy == NULL)
		{
			cout<<"Sorry no vertex exist by this name\n";
			break;
		}
		
		tempry = dummy;
		
		while(tempry->e != NULL)
		{
			tempry = tempry ->e;
		}
		
		newnode = new (struct node);
		newnode->name = b;
		newnode->e=NULL;
		newnode->v=NULL;
		tempry->e=newnode;
		
	}
	
	system("cls");
	DFS();	
}

void DFS()
{
	cout<<"\nAdjacentry List representation of Graph is \n\n";
	dummy = first;
	
	while(dummy != NULL)
	{
		cout<<dummy->name<<"--->";
		tempry = dummy->e;
		
		while( tempry != NULL)
		{
			cout<<tempry->name<<"---->";
			tempry = tempry->e;
		}
		cout<<"||||\n";
		dummy = dummy->v;
			
	}
 system("pause");
 system("cls");
 cout<<"Depth First traversal of the graph is :  \n\n";
 dummy = first;

 if(dummy == NULL)
 {
	cout<<"Sorry no Vertices in the graph \n";
 }
 else
 {
 //	cout<<"1OK\n";
	push(dummy); // Pushing first vertex i.e Index of graph into Stack
 }

 while(top >= 0) // Till stack is not empty 
 {
 	//cout<<"2OK\n";
	store=pop(); // first element of stack is popped out and stored in store
	dummy=first; // Vertical traversal for getting exact vertex == store
/***/while(dummy->name != store->name ) // traversal
	{
	//	cout<<"3OK\n";
		dummy=dummy->v;
	}
//	cout<<"4OK\n";
/***/store = dummy; // Requirved vertex is selected and stored in store (to get link into graph
	if(store->m == NV)//checked for V or NV
	{
		//cout<<"5OK\n";
		cout<<"----->"<<store->name<<"\t";
		store->m = V; // Marked
		tempry = store->e;/*Now we need to push adj vertices of Popped out Vertex*/
		while(tempry != NULL)
		{
			//cout<<"6OK\n";
			push(tempry);//all edges of pushed into stack
			tempry = tempry->e;
		}
	}
  }
  cout<<"\n\n";
  system("pause");
}

void push(struct node *h)
{
	top++;
	stack[top]=h;
}

struct node *pop()
{
	//top--;
	return (stack[top--]);
}
