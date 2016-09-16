/* Adjacency Matrix Representation for Undirected graph */

#include<iostream>
using namespace std;
#include<stdlib.h>

int main()
{
	static int a[5][5];
	int i,j,m,n;
	
	cout<<"Consider there are four vertices numbered 1 to 4 \n";
	cout<<"Enter the edge between vertices as : 1 4(if there is edge b/w vertex 1 & 4\n";
	cout<<"\n\tNote:Enter 0 0 when over\n";
	
	for(i=1;i<=12;i++)
	{
		cin>>m>>n;
		if(m==0 && n==0)
		{
				break;
		}
        a[m][n]=1;
		a[n][m]=1;
	}
	
	cout<<"The adjacency matrix for the graph is : \n";
	cout<<"\t1\t2\t3\t4\n";
	cout<<"----------------------------------------\n";
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
