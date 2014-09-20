#include"Xyz_Database.h"
#include"BST_of_Words.h"
#include<iostream>
#include<sstream>
#include<cstdio>
#include<stdlib.h>
#include<fstream>
using namespace std;
/* A C++ program to implement itoa() */
#include <iostream>
using namespace std;
 
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}


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


