
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

/****/struct node *que[max];// as que should hold nodes

int r=-1,f=-1;//r => rear ; f => front

void enqueue(node *h);
node* dequeue();

main()
{
	int n,x=0/* Just to have proper initalisation of index node */,i,j,no_ofedges;
	char a,b;
	
	struct node *newnode,*first/*Stores Index of graph*/,*tempry,*store,*dummy/*Stores Index of graph and used in crating V link with other nodes */;
	
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
	
	cout<<"\n\nBreadth First traversal of the Graph is \n\n";
	dummy = first;
	
	if(dummy == NULL)
	{
		cout<<"Sorry!No vertices in the graph\n";
	}
	else
	{
		enqueue(dummy);//First i.e Index of Graph is enqued into queue
	}
	while(r != -1)
	{
	   	store = dequeue();//first value of que is dequed
	   	dummy = first;
	   	
	   	while(dummy->name != store->name)
	   	{
	   		dummy = dummy->v;
	   	}
	   	
	   	store = dummy;
	   	
	   	if(store->m == NV)
	   	{
	   		cout<<"---->"<<store->name;
	   		store->m = V;
	   		tempry = store->e;//For queing neighbours of enqued node
	   		while(tempry != NULL)
	   		{
	   			enqueue(tempry);
	   			tempry = tempry->e;
	   		}
	   	}
	}
	
	system("pause");
}

void enqueue(struct node *h)
{
	r++;
	que[r]=h;
	if(f==-1)//For first insertion or enqueing into queue
	{
		f=0;
	}
}

struct node* dequeue()
{
	struct node *q;
	if(f==r)//For only one last element in que
	{
		q = que[f];
		f=-1;
		r=-1;
	}
	else
	{
		q=que[f];
		f++;
	}
	
	return(q);
}




