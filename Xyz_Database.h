#pragma once
#include"BST_of_Words.h"
#include<string>
#include<set>
#include<vector>
using namespace std;
struct Xyz_Database
{
	Xyz_Database();
	~Xyz_Database();
	string transducer(string& command);
	BST_of_Words tree;
	set<Word*,less<Word*> > temp;
	set<Word*,less<Word*> >::iterator j;
	set<Line*,less<Line*> > lineTemp;
	set<Line*,less<Line*> >::iterator k;
private:
	string fileListString;
};