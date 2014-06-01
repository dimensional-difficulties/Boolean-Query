#include"S_Expression_Tree.h"
#include<algorithm>
S_Expression_Tree::S_Expression_Tree()
{
	pSRoot=NULL;
}
void S_Expression_Tree::addContent(string contentToAdd, sTreeNode *pRootOfCurrentTree)//this is called in query.
{
	int numPar=0,index=0;
	do
	{
		
		if(contentToAdd[index]=='(')
			numPar++;
		else if(contentToAdd[index]==')')
			numPar--;
		else if(index==0)
			break;
		index++;
		if(index>=contentToAdd.length())//superfluous parentheses around outside of statement exist.  Remove.
		{	
			contentToAdd.erase(contentToAdd.length()-1,1);
			contentToAdd.erase(0,1);
			numPar=index=0;
		}
	}
	while(numPar!=0||index==0);
	
	
	if((contentToAdd[index]!='&')&&(contentToAdd[index]!='|')&&(contentToAdd[index]!=' '))
	{
		
		int start = 0;
		while(contentToAdd[start]=='(')
			start++;
		index=0;
		while((index<contentToAdd.length()))
		{
			if(index<contentToAdd.length()-1)
			{
				if(contentToAdd[index+1]==')')
					break;
			}
			index++;
		}
		pRootOfCurrentTree->content=contentToAdd.substr(start,index-start+1);
		pRootOfCurrentTree->pLeftS=NULL;//this is a leaf.  If it contains a word then it doesn't point to anything.
		pRootOfCurrentTree->pRightS=NULL;
	}
	else
	{
		if(index < contentToAdd.length())
		{
			pRootOfCurrentTree->content=contentToAdd[index];
			pRootOfCurrentTree->pRightS=new sTreeNode;
			addContent(contentToAdd.substr((index+2),9999),pRootOfCurrentTree->pRightS);
		}
		pRootOfCurrentTree->pLeftS=new sTreeNode;
		addContent(contentToAdd.substr(1,index-1),pRootOfCurrentTree->pLeftS);
	}
	/*Root.data is the operator, left is everything to the left of it, right is everything to the right of it.*/
}