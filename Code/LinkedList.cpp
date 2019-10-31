/*
* LinkedList Class implementation
*/
using namespace std;
class LinkedList
{
private:
	struct node
	{
		hash_table_entry entry;
		node *next;
	};
public:
	int size;
	node *head , *tail;
	LinkedList()
	{
		size = 0;
		head = NULL;
		tail = NULL;
	};

	int get_size()
	{
		return size;
	}

  void add(hash_table_entry e)
    {
      node *temp=new node;
      temp->entry=e;
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

    hash_table_entry at(int index)
    {
    	node *n = head;
    	for (int i = 0; i < index; ++i)
    	{
    		n = n->next;
    	}
    	return n->entry;
    }

	hash_table_entry find(int event_id)
	{
		hash_table_entry e;
			e.event_id = -1;
		for (int i = 0; i < size; ++i)
		{
			if (at(i).event_id == event_id)
			{
				e = at(i);
			}
		}
		return e;
	}

	void print_list()
	{
		node *ptr = head;
		if (size == 0)
		{
			cout << "NULL\n";
		}
		else
		{
			while(ptr != NULL)
			{
				cout << ptr->entry.event_id << "->";
				ptr = ptr->next;
			}
			cout << "\n";
		}
		
	}
};