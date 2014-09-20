#pragma once
#include<string>
#include"Line.h"
using namespace std;
struct Word
{
	Word();
	Word(string text,string found);
	string wordText;
	Line* lineWhereFound;
};
