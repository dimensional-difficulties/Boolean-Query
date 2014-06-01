#pragma once
#include<string>
using namespace std;
struct Line
{
	Line();
	Line(string text,string file,int number){lineText=text;file=filename;number=lineNumber;}
	Line* link;
	string lineText;
	string filename;//The file where the line was found. 
	int lineNumber;
};