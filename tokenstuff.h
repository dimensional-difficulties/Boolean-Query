//(c)Copyright 2003 Thomas Fernandez
//Edited in 2014 by Michael Kossin
//All rights reserved.
#pragma once
#include <fstream> 
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
inline string toLower(const string & s)
{
	string result=s;
	for(int i=0;i<result.length();i++)result[i]=tolower(result[i]);
	return result;
}
inline bool getString(ifstream& infile,string& s)
{
	char temp[2048];
	strcpy(temp,"");
	bool endoffile=infile.eof();
	while((!endoffile)&&(strlen(temp)==0))
	{
		infile.getline(temp,2047);
		endoffile=infile.eof();
		s=temp;
	}
	return endoffile; 
}
inline bool isAlpha(char c)
{
	return((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z'));
}
inline void getStart(string s,int& p)
{
	while(p<s.length()&&!isAlpha(s[p]))
	{
		p++;
	}
}
inline void getEnd(string s,int& p)
{
	while (p<s.length()&&isAlpha(s[p]))
	{
		p++;
	}
}
inline vector<string> tokenize(string x)
{
	vector<string> result;
	int itoke=0;
	int start,end;
	start=0;
	while (start<x.length())
	{
		getStart(x,start);
		if(start<x.length())
		{
			end=start+1;
			getEnd(x,end);
			result.push_back(x.substr(start,end-start));
			itoke++;
			start=end+1;
		}
	}
	return result;
}
inline bool getStringAndTokens(ifstream& infile,string& line,vector<string>& tokens)
{
	bool endoffile=getString(infile,line);
	tokens=tokenize(line);
	for(int i=0;i<tokens.size();i++)
		tokens[i]=toLower(tokens[i]);
	return endoffile;
}
