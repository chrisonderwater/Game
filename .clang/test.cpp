//
//
//  Balancing a Strict Binary Search Tree
//		using DSW Balancing Algorithm
//

#include <stdio.h>
#include <stdlib.h>


//////////////////////////////////////////////
struct Node { int Data; struct Node *Left,*Right; };


/////////////////////////////////////
// Rotates around the current node 
int LeftRotate(struct Node *node)  // =1 if rotate works,=0 otherwise 
	{  struct Node *nd;  int data;
	if(node==0 || node->Right==0) { return 0; }	// No Right Node!!

	nd=node->Right; node->Right=nd->Right;  // Move Node
	nd->Right=nd->Left; nd->Left=node->Left;
	node->Left=nd;

	data=node->Data;  node->Data=nd->Data; nd->Data=data;
	return 1;
	}


/////////////////////////////////////
// Rotate around current node
int RightRotate(struct Node *node) // =1 if rotate works, =0 otherwise
	{  struct Node *nd;  int data;
	if(node==0 || node->Left==0) { return 0; }	

	nd=node->Left; node->Left=nd->Left;
	nd->Left=nd->Right; nd->Right=node->Right;
	node->Right=nd;

	data=node->Data; node->Data=nd->Data;  nd->Data=data;
	return 1;
	}



//////////////////////////////////////
void DSWBalancingAlgorithm(struct Node *root)
	{  struct Node *p;  int nodecount; int i;
	///////////// Create Linear Back Bone ///////////////////
	
	for(p=root,nodecount=0;p!=0;p=p->Right,++nodecount)
		{
		while(RightRotate(p)==1) { }
		}

	////////////  Perform Balancing ///////////////////////
	for(i=nodecount/2; i>0; i/=2 )
		{  int k;
		for(p=root,k=0;k<i;++k,p=p->Right)
			{ LeftRotate(p);  }
		}
	}


////////////////////////////////////////////////////////////
// The Following Code is used to Check how balanced is a tree
int Height(struct Node *root)    
	{
	if(root==0) { return 0; }
	return 1 + __max(Height(root->Left),Height(root->Right));
	}


///////////////////////////////////////////////////////
// Following Function will Find the Sum of the Absolute diff in
// hight of every node.  The recursion below is terrible in running time!!!
int SumAbsDiff(struct Node *root) // =0 Means a perfect balanced tree
	{
	if(root==0) { return 0; }
	return abs(Height(root->Left)-Height(root->Right))
				+SumAbsDiff(root->Right)+SumAbsDiff(root->Left);
	}


/////////////////////////////////////
int InsertValue(struct Node **root,int value)// =1 on success, =0 on fail
	{  struct Node *p,*nw;
	if((nw=(struct Node *)malloc(sizeof(struct Node)))==0) { return 0; }

	nw->Data=value; nw->Left=nw->Right=0;	

	if(*root==0) { (*root)=nw;  return 1; }

	for(p=*root; ; )
		{
		if(value<p->Data)
			{
			if(p->Left==0) { p->Left=nw; return 1; }
			p=p->Left;
			}
		else if(value>p->Data)
			{
			if(p->Right==0) { p->Right=nw; return 1; }
			p=p->Right;
			}
		else // We are trying to insert a value that exists in Strict BST
			{
			printf("Inserting Identical value into tree\n"); 
			free(nw); return 0; 
			}
		}
	}


////////////////////////////////////////
void PrintTree(struct Node *root)
	{  // Perform Inorder Traversal of tree
	if(root==0) { return; }
	PrintTree(root->Left);
	printf(" %d ",root->Data);
	PrintTree(root->Right);
	}


////////////////////////////////////////
void DeleteTree(struct Node *root)
	{
	if(root==0) { return; }
	DeleteTree(root->Left);  DeleteTree(root->Right);
	free(root);	
	}



//////////////////////////////////////
int main(void)
	{  struct Node *root=0;  int i;

	for(i=0;i>-15;--i)  // Insert some Nodes
		{  InsertValue(&root,i); }

	printf("Before Balancing : %d\n",SumAbsDiff(root));
	DSWBalancingAlgorithm(root);
	printf("After Balancing  : %d\n",SumAbsDiff(root));
	
	DeleteTree(root); root=0; return 0;
	}