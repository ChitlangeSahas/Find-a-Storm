#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

/*
* LinkedList Class implementation
*/
class LinkedList
{
private:
	struct node
	{
		string data;
		node *next;
	};
public:
	node *head , *tail;
	int size;
	LinkedList()
	{
		size = 0;
		head = NULL;
		tail = NULL;
	};

	node* get_head()
	{
		return head;
	}

  void push(string d)
    {
      node *temp=new node;
      temp->data=d;
      temp->next=NULL;

      if(head==NULL)
      {
        head=temp;
        tail=temp;
        temp=NULL;
      }
      
      else
      {	
        tail->next=temp;
        tail=temp;
      }
    size++;
    }

	void print_list()
	{
		node *ptr = head;
		while(ptr != nullptr)
		{
			cout << ptr->data << "->";
			ptr = ptr->next;
		}
		if (size == 0)
		{
			cout << "list is empty\n";
		}
	}
	// ~LinkedList();
};

/*
* Get the command line query as a string 
*/
string	get_query(char const *argv[])
{
	int i = 1;
	string query = "";
	while(argv[i])
	{
		query += (argv[i]);
		query += ",";
		i++; 
	}
	return query;}


int 	main(int argc, char const *argv[])
{
	string query = get_query(argv);
	
	cout << query;
	return 0;
}			