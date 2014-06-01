#include<iostream>
#include"Xyz_Database.h"
#include"BST_of_Words.h"
#include"S_Expression_Tree.h"
void consoleInterface(Xyz_Database& m)
{
	string command;
	string result;
	while(command!="QUIT")
	{
		cout<<">";
		getline(cin,command);
		result=m.transducer(command);
		cout<<result;
	}
}
int main()
{
	Xyz_Database database;
	consoleInterface(database);
	return 0;
}