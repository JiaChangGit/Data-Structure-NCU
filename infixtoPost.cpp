#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;
typedef class Infix_to_Postfix ITP;

class Infix_to_Postfix
{
private:
  char data;
  ITP *link;

public:
  Infix_to_Postfix();
  Infix_to_Postfix(char data, ITP *link);
  ~Infix_to_Postfix();

  //  ITP *create();
  ITP *push(ITP *top, char ch);
  ITP *pop(ITP *top);
  
};

ITP::Infix_to_Postfix()
{
  cout << "constructed, data: " << this->data << ", link: " << this->link << endl;
}
ITP::Infix_to_Postfix(char data, ITP *link)
{
  this->data = data;
  this->link = link;
  cout << "(p) Constructed, data: " << this->data << ", link: " << this->link << endl;
}
ITP::~Infix_to_Postfix()
{
  cout << "~destructed!!" << endl;
}

ITP *ITP::push(ITP *top, char ch)
{
  ITP *new1;
  new1->data = ch;
  if (top != NULL)
    new1->link = top;
  top = new1;
  return top;
}

ITP *ITP::pop(ITP *top)
{
  ITP *ptr;
  if (top != NULL)
  {
    cout << top->data;
    ptr = top;
    top = top->link;
    free(ptr);
  }
  return top;
}

int main(void)
{

  return 0;
}