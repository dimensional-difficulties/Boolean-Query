#include"BST_of_Words.h"
#include<algorithm>
#include <iterator>
using namespace std;
BST_of_Words::BST_of_Words()
{
	pRoot=NULL;
}
void BST_of_Words::addFile(string fileName)
{
	ifstream infile;
	infile.open(fileName.c_str());
	string line;
	vector<string> tokens;
	bool endOfFile=infile.eof();
	int count=0;
	Word* wording=new Word;
	while(!endOfFile)
	{
		endOfFile=getStringAndTokens(infile,line,tokens);
		// If I'm already read past the end of the file then the last read is invalid.  


		count++;

		lines.add(line,fileName,count);

		for(int i=0;i<tokens.size();i++)
		{
			wording=new Word;
			wording->wordText=tokens[i];
			wording->lineWhereFound=lines.tail;
			addWord(*wording);
		}

	}
	endOfFile=getStringAndTokens(infile,line,tokens);
	// If I've already read past the end of the file then the last read is invalid.  
	if(!endOfFile)
	{

		count++;

		lines.add(line,fileName,count);

		for(int i=0;i<tokens.size();i++)
		{
			wording=new Word;
			wording->wordText=tokens[i];
			wording->lineWhereFound=lines.tail;
			addWord(*wording);
		}
	}
	infile.close();
}
TreeNode** BST_of_Words::findInsertionPoint(TreeNode** ppRoot, string wordToAdd)
{
	if ((*ppRoot)==NULL)
		return ppRoot;
	if(wordToAdd<=((*((**ppRoot).pData)).wordText))
		return findInsertionPoint(&((**ppRoot).pLeft),wordToAdd);
	else
		return findInsertionPoint(&((**ppRoot).pRight),wordToAdd);
}
void BST_of_Words::addWord(Word& wordToAdd)
{
	string wordLetters=wordToAdd.wordText;
	Line* lineNumber=wordToAdd.lineWhereFound;
	TreeNode** ppInsertPoint=findInsertionPoint(&pRoot,wordLetters);
	TreeNode* pNewTreeNode=new TreeNode;
	pNewTreeNode->pLeft=NULL;
	pNewTreeNode->pRight=NULL;
	(*pNewTreeNode).pData=&wordToAdd;
	(*ppInsertPoint)=pNewTreeNode;
}
string BST_of_Words::print()
{
	string result="";
	result=print(pRoot, result);
	return result;
}
string BST_of_Words::print(TreeNode* pRootOfCurrentTree, string& result)
{
	if(pRootOfCurrentTree==NULL)
		return"";
	print((*pRootOfCurrentTree).pLeft, result);
	result+=(*((*pRootOfCurrentTree).pData)).wordText; //the data contained in what is pointed to by the data member of what is pointed to by pRootOfCurrentTree
	result+="\n";
	print((*pRootOfCurrentTree).pRight, result);
	return result;
}
set<Word*> BST_of_Words::myFind(string thingToFind)
{
	set<Word*> wordSet;
	TreeNode** ppFound=myFind(&pRoot,thingToFind,&wordSet);
	return wordSet;
}
TreeNode** BST_of_Words::myFind(TreeNode** ppRoot,string wordToFind,set<Word*>* wordSet)
{
	if((*ppRoot)==NULL)
		return ppRoot;
	if((*((**ppRoot).pData)).wordText==wordToFind)
		wordSet->insert((**ppRoot).pData);
	if(wordToFind<=(*((**ppRoot).pData)).wordText)
		return myFind(&((**ppRoot).pLeft),wordToFind,wordSet);
	else
		return myFind(&((**ppRoot).pRight),wordToFind,wordSet);
}
set<Line*> BST_of_Words::lineFind(string thingToFind)
{
	set<Line*> lineSet;
	TreeNode** ppFound=lineFind(&pRoot,thingToFind,&lineSet);
	return lineSet;
}
TreeNode** BST_of_Words::lineFind(TreeNode** ppRoot,string wordToFind,set<Line*>* lineSet)
{
	if((*ppRoot)==NULL)
		return ppRoot;
	if((*((**ppRoot).pData)).wordText==wordToFind)
		lineSet->insert((**ppRoot).pData->lineWhereFound);
	if(wordToFind<=(*((**ppRoot).pData)).wordText)
		return lineFind(&((**ppRoot).pLeft),wordToFind,lineSet);
	else
		return lineFind(&((**ppRoot).pRight),wordToFind,lineSet);
}

void BST_of_Words::clear(TreeNode* pRootOfCurrentTree)
{
	if(pRootOfCurrentTree==NULL)
		return;
	clear((*pRootOfCurrentTree).pLeft);
	delete(*pRootOfCurrentTree).pData;
	clear((*pRootOfCurrentTree).pRight);
}
BST_of_Words::~BST_of_Words()
{
	clear(pRoot);
}
set<Line*> BST_of_Words::query(string queryLine)
{
	sTree.pSRoot=new sTreeNode;
	sTree.addContent(queryLine,sTree.pSRoot);
	set<Line*> finalSet=evaluate(sTree.pSRoot);
	return finalSet;
}
set<Line*> BST_of_Words::evaluate(sTreeNode* expression)
{
	set<Line*> leftSet;
	set<Line*> rightSet;
	set<Line*> resultSet;
	if(expression->content=="&")//then return a set that is the intersection of the two children.  
	{
		leftSet=evaluate(expression->pLeftS);
		rightSet=evaluate(expression->pRightS);
		set_intersection(leftSet.begin(),leftSet.end(),rightSet.begin(),rightSet.end(),inserter(resultSet,resultSet.begin()));
		return resultSet;
	}
	else if(expression->content=="|")
	{
		leftSet=evaluate(expression->pLeftS);
		rightSet=evaluate(expression->pRightS);
		set_union(leftSet.begin(),leftSet.end(),rightSet.begin(),rightSet.end(),inserter(resultSet,resultSet.begin()));
		return resultSet;
	}
	else
		return lineFind(expression->content);
}