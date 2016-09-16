#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int PathLen=0,Path[10];

struct Tree
{
	int Data;
	Tree *Left;
	Tree *Right;
};

typedef struct Tree TreeNode;
TreeNode *Root=NULL,*Root1=NULL;//Root is an address which points to TreeNode Variable(ADT) 'or' Simply Root is pointer to Tree.

/*
void CreateNode(TreeNode **Temp)
{
	*Temp = (TreeNode *)malloc(sizeof(TreeNode));
}
*/

void InsertNode(TreeNode **Root,int val)
{
  if(*Root == NULL)
 {
 //CreateNode(&Root);
 (*Root) = (TreeNode *)malloc(sizeof(TreeNode));
 (*Root)->Data = val;
 (*Root)->Left = NULL;
 (*Root)->Right = NULL;	
 printf("Node inserted into the Tree !!! It's Value is %d", (*Root)->Data);
 }
  
     else if(((*Root)->Data) > val)
    {
     InsertNode(&((*Root)->Left),val);	
    }	
    else if(((*Root)->Data) < val)
    {
     InsertNode(&((*Root)->Right),val);	
    }
 	
}


/*
int InsertNode(TreeNode *Root,int val)
{
  if(Root == NULL)
 {
 (Root) = (TreeNode *)malloc(sizeof(TreeNode));
                                            (Root)->Data = val;
 (Root)->Left = NULL;
 (Root)->Right = NULL;	
 printf("Node inserted into the Tree !!! It's Value is %d", (Root)->Data);
 }
     else if(((Root)->Data) > val)
    {
     InsertNode(((Root)->Left),val);	
    }	
    else if(((Root)->Data) < val)
    {
     InsertNode(((Root)->Right),val);	
    }
 	
}*/


int TreeSize(TreeNode *Root)//In place of Root we can generalise as Node.
{
	if(Root != NULL)
	{
		return(1 + TreeSize(Root->Left)+TreeSize(Root->Right) ) ;
	}
	else
	{
		return 0;
	}
} 

void Display_InOrder_Tree(TreeNode *Root)
{
	
	if(Root != NULL)//or Simply if(Root)
	{
		Display_InOrder_Tree(Root->Left);
	//	printf(" %d  ",(Root->Data)); 
	    printf(" %d  ",(*Root).Data);
		Display_InOrder_Tree(Root->Right);
	}
}


void Display_PreOrder_Tree(TreeNode *Root)
{
	if(Root !=NULL)
	{
	printf(" %d  ",(*Root).Data);
	Display_PreOrder_Tree(Root->Left);
	Display_PreOrder_Tree(Root->Right);	
	}
}

void Display_PostOrder_Tree(TreeNode *Root)
{
	if(Root !=NULL)
	{
	Display_PostOrder_Tree(Root->Left);
	Display_PostOrder_Tree(Root->Right);	
	printf(" %d  ",(*Root).Data);
    }
}

void IterLeastElement(TreeNode *Root)
{

TreeNode* Current=Root;        // IT IS REQUIRED AS WE WILL NEED TO SEE ROOT->NEXT and PROCEED to data.

if(Root != NULL)
{
	while(Current->Left != NULL)
	{
		Current = Current->Left;
	}
}

printf("\n\nThe Least Element of The Tree by Iteration is: %d",Current->Data);
getch();	

}

void RecurLeastElement(TreeNode *Root)
{	
if(Root!=NULL)
{
if(Root->Left !=NULL)
{
	RecurLeastElement(Root->Left);
}
else
{
	printf("\n\nThe Least Element of The Tree by Recursion is: %d",(Root)->Data);	
	getch();
}	
}
}

void LeastElement(TreeNode **Root)
{
	if(*Root !=NULL)
	{
	if((*Root)->Left != NULL)
	{
	LeastElement(&((*Root)->Left));
	}
	else
	{
	printf("\n\nThe Least Element of The Tree by Address Recursion is: %d",(*Root)->Data);
	getch();
	}
	}
}
void IterGreatestElement(TreeNode *Root)
{

TreeNode* Current=Root;

if(Root != NULL)
{
	while(Current->Right != NULL)
	{
		Current = Current->Right;
	}
}

printf("\n\nThe Greatest Element of The Tree by Iteration is: %d",Current->Data);
getch();	

}

void RecurGreatestElement(TreeNode *Root)
{	
if(Root!=NULL)
{
if(Root->Right !=NULL)
{
	RecurGreatestElement(Root->Right);
}
else
{
	printf("\n\nThe Greatest Element of The Tree by Recursion is: %d",(Root)->Data);	
	getch();
}	
}
}

void GreatestElement(TreeNode **Root)
{
	if(*Root !=NULL)
	{
	if((*Root)->Right != NULL)
	{
	GreatestElement(&((*Root)->Right));
	}
	else
	{
	printf("\n\nThe Greatest Element of The Tree by Address Recursion is: %d",(*Root)->Data);
	getch();
	}
	}
}

void SearchElement(TreeNode *Root,int Key)
{
	if(Root !=NULL)
	{
	   if((Root->Data == Key))
	   {
		printf("\n\tThe Value %d is Present in the Tree..!!!",Key);
	   }
	   else if((Root->Data > Key))
	  {
	    SearchElement(Root->Left,Key);	
	   }
	  else
	   {
		SearchElement(Root->Right,Key);
	   }
	
    }
    else
    {
    printf("\n\tThe Value %d is not Present in the Tree..!!!",Key);	
    }
}

void DeleteBST(TreeNode **Node)
{
	if((*Node) == NULL)
	{
		return;
	}
	DeleteBST(&((*Node)->Left));
	DeleteBST(&((*Node)->Right));
	if(  ((*Node)->Left) == NULL  && ((*Node)->Right) == NULL   )
	//if( !((*Node)->Left)  && !((*Node)->Right) )
	{
		printf("\nValue Freed from Memory of BST is %d ",(*Node)->Data);
		getch();
		free((*Node));
		(*Node) = NULL;
	}
}

TreeNode* DSearchElement(TreeNode *Root,int Key)
{
	if(Root !=NULL)
	{
	if((Root->Data == Key))
	{
		return (Root);
	}
	else if((Root->Data > Key))
	{
	    DSearchElement(Root->Left,Key);	
	}
	else
	{
		DSearchElement(Root->Right,Key);
	}
    }
    else
    {
    printf("\n\tThe Value %d is not Present in the Tree..!!!",Key);
	return (NULL);	
    }
}

int DRecurGreatestElement(TreeNode *Root)
{
int x;
	
if(Root!=NULL)
{
if(Root->Right !=NULL)
{
	DRecurGreatestElement(Root->Right);
}
else
{
	printf("\n\nThe Greatest Element of The Tree by Recursion is: %d",(Root)->Data);	
	getch();
	x=(Root)->Data;
	free (Root);
	Root = NULL;
	return (x);
}
}
}

void DeleteNode(TreeNode *Node,int key)
{
	//TreeNode *Temp;
	
    if(Node != NULL)
    {
 	(DSearchElement(Node,key))->Data = DRecurGreatestElement((DSearchElement(Node,key)));
 	printf("\n\nBST is Recreated after Deletion of Selected Tree\n\n");
 	getch();
    }
    else
    {
    printf("\n\n Tree is Already Empty \n");	
    }	
}

int MaxDepth(TreeNode *Node)
{
	int LLength;
	int RLength;
	if(Node != NULL)
	{
	LLength = MaxDepth(Node->Left);
	RLength	= MaxDepth(Node->Right);
	if(LLength > RLength)
	{
		return (LLength +1);
	}
	else if(LLength < RLength)
	{
		return (RLength +1);
	}
	}
	else
	{
		return 0;
	}	
}


void PrintPath(int Path[],int PathLen)
{
	
	for(int i=0;i<=PathLen;i++)
	{
		printf("-> %d ",Path[i]);
	}
	printf("\n");
}

/*
void PrintPathTree(TreeNode **Node,int Path[],int PathLen)
{
	if( (*Node) = NULL )
	{
	return ;	
	}
		
		//Append This Node to Path Array
		
	    Path[PathLen] = (*Node)->Data;
	    PathLen++;
	    
		//It's a Leaf.So Print the Path That Lead to here
		if((*Node)->Left == NULL && (*Node)->Right == NULL)
		{
		 PrintPath(Path,PathLen);
		 getch();	
		}
		else
		{
		//Otherwise Traverse BothTrees
		PrintPathTree(&((*Node)->Left),Path,PathLen);	
		PrintPathTree(&((*Node)->Right),Path,PathLen);
		}	
}
*/


void PrintPathTree(TreeNode *Node,int Path[],int PathLen)
{
	if( Node == NULL )
	{
	return ;	
	}
		
		//Append This Node to Path Array.
		
	    Path[PathLen] = (Node->Data);
	    PathLen++;
	    
		//It's a Leaf.So Print the Path That Lead to here.
		if( Node->Left == NULL && Node->Right == NULL)
		{
		 PrintPath(Path,PathLen);
		 getch();	
		}
		else
		{
		//Otherwise Traverse BothTrees.
		PrintPathTree((Node->Left),Path,PathLen);	
		PrintPathTree((Node->Right),Path,PathLen);
		}	
}

int CheckBST(TreeNode *Node)
{
	if(Node != NULL)
	{
		//General case with full complete Binary Node
		if(Node->Left != NULL && Node->Right != NULL)
		{
			if( Node->Data > ((Node->Left)->Data) && Node->Data < ((Node->Right)->Data) )
			{
				printf("\nNode with Value %d is Fine",Node->Data);
				return (CheckBST(Node->Left) & CheckBST(Node->Right));
			}
			else
			{
				printf("\nNode with Value %d is Not Fine",Node->Data);
				return 0;	
			}
		}
		
		//General case with Right Null Node
		else if(Node->Left != NULL && Node->Right == NULL)
		{
			if( Node->Data > ((Node->Left)->Data) )
			{
				printf("\nNode with Value %d is Fine",Node->Data);
				return (CheckBST(Node->Left));
			}
			else
			{
				printf("\nNode with Value %d is Not Fine",Node->Data);
				return 0;	
			}
		}
		//General case with Left Null Node
		else if(Node->Right != NULL && Node->Left == NULL)
		{
			if( Node->Data < ((Node->Right)->Data) )
			{
				printf("\nNode with Value %d is Fine",Node->Data);
				return (CheckBST(Node->Right));
			}
			else
			{
				printf("\nNode with Value %d is Not Fine",Node->Data);
				return 0;	
			}
		}
		else
		{
		   printf("\nNode with Value %d is Fine",Node->Data);
		   return 1;	
		}
	}
	else
	{
    printf("\nNode with Value %d is Not Fine",Node->Data);
    return 0;	
    }
}

int CheckEqualTree(TreeNode* Root,TreeNode* Root1)
{
	if(Root != NULL && Root1 != NULL)
	{
		if (Root->Data == Root1->Data)
		{
			return(CheckEqualTree(Root->Left,Root1->Left) & CheckEqualTree(Root->Right,Root1->Right));
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

int main()
{
 int ch,val,srch,key;
 printf("\nProgram Name:AKHIL REDDY TREE\n\n");
 while(1)
 {
	system("cls");
	
	printf("PRESS!!!\n");
	printf(" 1.TO INSERT NODE\n\n 2.TO COUNT TOTAL NO.OF NODES\n\n 3.TO GET IN-ORDER DISPLAY\n\n 4.TO GET PRE-ORDER DISPLAY\n\n 5.TO GET POST-ORDER DISPLAY\n\n 6.TO GET LEAST ELEMENT IN BST\n\n 7.TO GET HEIGHST ELEMENT IN BST\n\n 8.SEARCH ELEMENT\n\n 9.DELETE FULL TREE\n\n 10.Delete A Node in Tree\n\n 11.Maximum Depth of BST\n\n 12.Print Possible Path's\n\n 13.Check For Binary Tree\n\n 14.Create another Tree and Compare Both Trees\n\n 0.EXIT");
	printf("\n\nPlease enter Choice of Intrest: ");
	scanf("%d",&ch);
	
	switch(ch)
	{
		
	case 1:
	printf("Please give the Value you want to Insert into Node: ");
	scanf("%d",&val);
	InsertNode(&Root,val);
	//InsertNode(Root,val);
	getch();
	break;
	
	case 2:
	printf("Note:You will get Tree Size to the present point of Insertion\n");
	printf("\nTotal Number of Nodes in Tree is : %d ",TreeSize(Root));
	getch();
	break;
	
	case 3:
	printf("\n\n***Node Values of Tree in IN-ORDER (LNR) ***\n\n ");
	printf("Nodes Values in Increasing Order : ");
	Display_InOrder_Tree(Root);
	getch();
	break;
	
	case 4:
	printf("\n\n***Node Values of Tree in PRE-ORDER (NLR) ***\n\n ");
	printf("Nodes Values in PRE Order : ");
	Display_PreOrder_Tree(Root);
	getch();
	break;
	
	case 5:
	printf("\n\n***Node Values of Tree in POST-ORDER (LRN) ***\n\n ");
	printf("Nodes Values in POST Order : ");
	Display_PostOrder_Tree(Root);
	getch();
	break;
	
	case 6:
	IterLeastElement(Root);
	RecurLeastElement(Root);
	LeastElement(&Root);
	break;
	
	case 7:
	IterGreatestElement(Root);
	RecurGreatestElement(Root);
	GreatestElement(&Root);	
	break;
	
	case 8:
	printf("\nPls give the element You want to Search : ");
	scanf("%d",&srch);
	SearchElement(Root,srch);
	getch();
	break;
	
	case 9:
	DeleteBST(&Root);
	printf("\nTotal Binary Tree is Freed from Memory...");
	getch();
	break;
	
	case 10:
	printf("\nPls give the element You want to Delete : ");
	scanf("%d",&key);
	DeleteNode(Root,key);
	break;
	
	case 11:
	printf("\n\nThe Maximum depth of Given BST is : %d \n",MaxDepth(Root));
	getch();
	break;
	
	case 12:
	PrintPathTree(Root,Path,PathLen);
	break;
	
	case 13:
	int f;
	f=CheckBST(Root);
	getch();
	if(f == 1)
	{
		printf("\n  So Given Binary Tree is a BST  ");
	}
	else
	{
		printf("\n  So Given Binary Tree is a not a BST  ");
	}
	getch();
	break;
	
	case 14:
	int n;
	do{
	printf("Please give the Value you want to Insert into Node: ");
	scanf("%d",&val);
	InsertNode(&Root1,val);
	getch();
	printf("\nStill You want to continue Insertion into Tree2 : <Y/N>\n");
	scanf("%d",&n);
    }while(n);
    n=CheckEqualTree(Root,Root1);
    getch();
    if(n==1)
    {
    	printf("\t Both Trees are Equal Trees");
    }
    else
    {
    	printf("\t Both Trees are not Equal Trees");
    }
    getch();
    break;
    
	case 0:
	exit(0);	
	}
 }
 
return 0;	
}

