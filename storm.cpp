#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

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

	// ~LinkedList();};
};

/*
* convert the string into vector tokens
*/
std::vector<string> 	str_to_vector_tokens(std::string str, std::string delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

/*
* Get the command line query as a string 
*/
std::vector<string>	parse_query(char const *argv[])
{

	int i = 1;
	string query = "";
	while(argv[i])
	{
		query += (argv[i]);
		query += ",";
		i++; 
	}
	std::vector<string> query_v;

	query_v = str_to_vector_tokens(query, ",");
	return query_v;
}

/*
* helper function to check if 
* a string is a number
*/
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int 	main(int argc, char const *argv[])
{
	std::vector<string> query = parse_query(argv);

	// find
	if (query[0] == "find")
	{
		// find event
		if (query[1] == "event")
		{
			/* code */
		}
		// find max
		else if (query[1] == "max")
		{
			// find max fatality
			if (query[2] == "fatality")
			{
				/* code */
			}
			// find max 
			else if (is_number(query[2]))
			{
				/* code */
			}
			else cout << "INVALID QUERY";
		}
		else cout << "INVALID QUERY";
	}
	// range
	else if(query[0] == "range")
	{
		// range all
	  	if (query[1] == "all")
	  	{
	  		/* code */
	  	}
	  	// range <yyyy> 
	  	else if (is_number(query[1]))
	  	{
	  		/* code */
	  	}
	  	else cout << "INVALID QUERY";
	}
	// storm 1 1950

	else if(is_number(query[0]))
	{
		int n_years = stoi(query[0]);
		std::vector<int> years;
		// make a vector of years one wants to get data of.
		for (int i = 1; i <= n_years; ++i)
			{
				years.push_back(stoi(query[i]));
			}	
		
	}
	else cout << "INVALID QUERY";


	return 0;
}