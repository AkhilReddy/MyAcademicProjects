/* Adjacency matrix representation of a directed graph */

#include<iostream>
using namespace std;
#include<stdlib.h>

int main()
{
	static int a[5][5];
	int i,j,m,n;
	
	//Consider there is a four vertex numbered 1 to 4 or we can create dynamically by just changing for loop count by (n*n-1)
	
	cout<<"Enter the edges between vertices as : 1 4 (if there is an Edge between vertex 1 and 4)\n";
	cout<<"\t\tNote : Enter 0 and 0 once all over\n\n";
	
	for(i=1;i<=12;i++)
	{
		cin>>m>>n;
		if(m==0 && n==0)
		break;
		a[m][n]=1;
	}
	
	cout<<"The adjacent matrix for the graph is :\n";
	cout<<"\t1\t2\t3\t4\n";
	cout<<"------------------------------------\n";
	for(i=1;i<=4;i++)
	{
		cout<<i<<" |\t";
		
		for(j=1;j<=4;j++)
		{
			cout<<a[i][j]<<"\t";
		}
		cout<<"\n";
	}
	
	return 0;
}
