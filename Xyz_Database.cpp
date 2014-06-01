#include"Xyz_Database.h"
#include"BST_of_Words.h"
#include<iostream>
#include<sstream>
#include<cstdio>
#include<stdlib.h>
#include<fstream>
//#include <algorithm>
//#include <iterator>
using namespace std;
Xyz_Database::Xyz_Database()
{
	ifstream fileList;
	string nameOfFile;
	fileList.open("file_list.txt");
	if((!fileList.fail())&&(!fileList.eof()))
	{
		while(!fileList.eof())
		{
			fileList>>nameOfFile;
			tree.addFile(nameOfFile);
		}
		fileList.close();
	}
}
string Xyz_Database::transducer(std::string &command)
{
	temp.clear();
	int i;
	string result="";
	string name;
	char buffer[4];
	int lineNumberInt;
	//BST_of_Words tree;
	//Word* temp;
	if(command.substr(0,8)=="ADD_FILE")
	{
		name=command.substr(9,9999);
		if(fileListString!="")
			fileListString+="\n";
		fileListString+=name;

		(*this).tree.addFile(name);
	}
	if(command.substr(0,9)=="FIND_WORD")
	{
		name=command.substr(10,9999);//everything after the instruction (the word to find for example)
		i=0;
		while(i<name.length())
		{
			name[i]=tolower(name[i]);
			i++;
		}
		string test;
		temp=tree.myFind(name);
		j=temp.begin();
		while(j!=temp.end())
		{
			result+=(*(*(*j)).lineWhereFound).lineText;
			result+="\n";
			result+=(*(*(*j)).lineWhereFound).filename;
			result+=" [";
			lineNumberInt=(*(*(*j)).lineWhereFound).lineNumber;
			itoa(lineNumberInt,buffer,10);
			result+=buffer;
			result+="]\n\n";
			j++;
		}
	}
	if(command=="PRINT")
	{
		result=tree.print();
	}
	if(command=="CLEAR")
	{
		tree.clear(tree.pRoot);
	}
	if(command.substr(0,5)=="QUERY")
	{
		name=command.substr(6,999);
		
		
		//First, put parentheses around every word.

		for(i=0;i<name.length();i++)
		{
			char letter = (name.c_str())[i];
			if(isalnum(letter))
			{
				name.insert(i,"(");
				i++;
				letter = (name.c_str())[i];
				while(isalnum(letter))
				{
					i++;
					letter = (name.c_str())[i];
				}
				name.insert(i,")");
			}
		}
		
		

		lineTemp=tree.query(name);
		k=lineTemp.begin();
		while(k!=lineTemp.end())
		{
			result+=(*k)->lineText;       
			result+="\n";
			result+=(*k)->filename;        
			result+=" [";
			lineNumberInt=(*k)->lineNumber;     
			itoa(lineNumberInt,buffer,10);
			result+=buffer;
			result+="]\n\n";
			k++;
		}
	}
	return result;
}
Xyz_Database::~Xyz_Database()
{
	
	ofstream fileList;
	fileList.open("file_list.txt");
	fileList<<fileListString;
	fileList.close();
}