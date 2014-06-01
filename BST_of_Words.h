#pragma once
#include<string>
#include"LineList.h"
#include"Word.h"
#include<fstream>
#include"tokenstuff.h"
#include<stdlib.h>
#include<vector>
#include<set>
#include"Line.h"
#include"S_Expression_Tree.h"
#include<vector>
using namespace std;
class TreeNode
{
	TreeNode* pLeft;
	TreeNode* pRight;
	Word* pData;
	friend struct BST_of_Words;
};
struct BST_of_Words
{
	BST_of_Words();
	~BST_of_Words();
	TreeNode** findInsertionPoint(TreeNode** ppRoot, string wordToAdd);
	void addWord(Word& WordToAdd);
	void addFile(string fileName);
	void clear(TreeNode* pRootOfCurrentTree);
	LineList lines;
	string print();
	string print(TreeNode* pRootOfCurrentTree, string& result);
	set<Word*> myFind(string thingToFind);
	set<Line*> lineFind(string thingToFind);
	TreeNode* pRoot;
	set<Line*> query(string queryLine);
	set<Line*> evaluate(sTreeNode* expression);
private:
	TreeNode** myFind(TreeNode** ppRoot,string wordToFind,set<Word*>* wordSet);	
	TreeNode** lineFind(TreeNode** ppRoot,string wordToFind,set<Line*>* lineSet);
	S_Expression_Tree sTree;
};