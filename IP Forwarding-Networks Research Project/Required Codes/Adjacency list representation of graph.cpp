/* Adjacency list representation of graph */

#include<iostream>
using namespace std;
#include<stdlib.h>

struct node
{
	char name;
	node *vlink;//link for other nodes one by one.
	node *edge;//For Edge link.
};

int main()
{
int n,i,x=0,j,noe;

char a,b;

node *first,*newnode,*plinker,*elinker;

cout<<"How many vertices are there? : ";
cin>>n;
cout<<"Enter all the vertices names:\n";

for(i=1;i<=n;i++)
{
	if(x==0)//Creating first node or root for total graph
	{
		newnode = new node;
		cin>>newnode->name;
		first=newnode;//always used to reffered to root
		plinker=newnode;//used to create links for one after other nodes by links
		newnode->vlink=NULL;
		newnode->edge=NULL;
		x++;//Next nodes	
	}
	else
	{
		//-------------------------//
		newnode = new node;
		cin>>newnode->name;
		newnode->vlink=NULL;
		newnode->edge=NULL;
		//------------------------//
		plinker->vlink=newnode;
		plinker = newnode;
	}
}

cout<<"\nEnter the edges between vertices. Enter a b, if there is an edge\n";
cout<<"between a and b.Enter 0 0 if over\n";

noe=n*(n-1);//max possible noe

for(j=1;j<=noe;j++)
{
	cin>>a>>b;
	if(a == '0' && b == '0')
	{
	  break;
    }
	plinker = first;
/*%*/while(plinker != NULL && plinker->name != a)//This while loop will take Plinker to perticular required node
	{
		plinker=plinker->vlink;
	}
	if(plinker == NULL)
	{
		cout<<"Sorry! No such vertix with name \n";
		break;
	}
//-------------------------------------------------------------------------//
	elinker = plinker;
	while(elinker->edge != NULL)//This will take edge link to last
	{
	   elinker = elinker->edge;
    }
	newnode = new node;
	newnode->name=b;
	elinker->edge = newnode;
	newnode->vlink=NULL;
	newnode->edge=NULL;
}
	cout<<"\nAdjacent List representation of Graph is : \n\n";
	plinker = first;
	while(plinker != NULL)
	{
		cout<<plinker->name<<"  -->"<<"\t";
		elinker = plinker->edge;
		while(elinker != NULL)
		{
			cout<<elinker->name<<"  -->"<<"\t";
			elinker = elinker->edge;
		}
		cout<<"\n";
		plinker = plinker->vlink;
	}
	return 0;
}
