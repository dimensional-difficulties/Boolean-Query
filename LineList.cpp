#include"LineList.h"
using namespace std;
LineList::LineList()
{
	head=NULL;
	tail=NULL;
}
void LineList::add(string line,string filenameRead,int lineNumberRead)
{
	Line* temp=new Line;
	temp->filename=filenameRead;
	temp->lineNumber=lineNumberRead;
	temp->lineText=line;
	if(tail==NULL)
		tail=head=temp;
	else
	{
		tail->link=temp;
		tail=temp;
	}
}
LineList::~LineList()
{
	Line* temp;
	while(head!=tail)
	{
		temp=head;
		head=head->link;
		delete temp;
	}
	delete head;
}
