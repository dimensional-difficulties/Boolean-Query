#pragma once
#include"line.h"
#include<string>
using namespace std;
struct LineList
{
	LineList();
	~LineList();
	void add(string line,string filenameRead,int lineNumberRead);
	Line* head;
	Line* tail;
};