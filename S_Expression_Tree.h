#pragma once
#include<string>
using namespace std;
class sTreeNode
{
public:
	sTreeNode* pLeftS;
	sTreeNode* pRightS;
	string content;
	friend class S_Expression_Tree;
	friend struct BST_of_Words;
};
class S_Expression_Tree
{
	S_Expression_Tree();
	void addContent(string contentToAdd,sTreeNode* pRootOfCurrentTree);
public:
	sTreeNode* pSRoot;
	friend struct BST_of_Words;
};