#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "defn.h"

#define ROOT_FOLDER "./1950-1952/"

using namespace std;


/*
* LinkedList Class implementation
*/
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

struct hashNode
{
	LinkedList list;
	hashNode *next;

	void print_node()
	{

		list.print_list();
	}

	int size()
	{
		return list.get_size();
	}

	void add_to_node(hash_table_entry e)
	{
		list.add(e);
	}
};

/*
* Hashtable implementation
*/
class HashTable
{
private:
	int T_SIZE = 0;

	hashNode *hash_table_head;
	hashNode *ptr;

public:
	/*
	* constructor
	*/
	HashTable(int TABLE_SIZE)
	{
		T_SIZE = TABLE_SIZE;

		hash_table_head = (hashNode*) malloc(TABLE_SIZE * sizeof(hashNode));
		hashNode *ptr = hash_table_head;
		
		// blow it up.
		hashNode empty_node;
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
			*ptr = empty_node;
			 ptr++;
		}
	};

	int hash_it(hash_table_entry e)
	{
		return (e.event_id % T_SIZE);  
	}

	/*
	* Add the entry to the table
	*/
	void add_to_table(hash_table_entry e)
	{
		int key = hash_it(e);
		add_at_key(e, key);
	}

	/*
	* Add a value at the respective key.
	*/
	void add_at_key(hash_table_entry entry, int key)
	{
		hashNode *ptr = hash_table_head;
		for (int i = 0; i < key; ++i)
		{
			ptr++;
		}
		ptr->add_to_node(entry);
	}

	/*
	* print the damn thing
	*/
	void print_hash_table()
	{
		hashNode *ptr = hash_table_head;
		for (int i = 0; i < T_SIZE; ++i)
		{
			ptr->print_node();
			ptr++;
		}
	}

	// ~HashTable();
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
bool is_number(string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/*
* convert the file into a vector. 
*/
std::vector<string> 	file_to_vector()
{
	int line_n = 0;
	string FILE_PATH = string(ROOT_FOLDER) + "details-1950.csv";
	string line;
	ifstream file_stream;

	// open file and put the file into a 2d vector.
	char fp[FILE_PATH.size() + 1];
	strcpy(fp, FILE_PATH.c_str());

	file_stream.open(fp);
	// get rid of the first line
	getline(file_stream, line); 

	std::vector<string> lines;

	// make a vector 
	while(getline(file_stream, line).good())
	{
		lines.push_back(line);
	}
	return lines;
}


int 	main(int argc, char const *argv[])
{
	std::vector<string> lines = file_to_vector();

	HashTable table(lines.size());

	storm_event

	int index = 0;

	for (int i = 0; i < lines.size(); ++i)
	{
		std::vector<string> line = str_to_vector_tokens(lines[i], ",");
		hash_table_entry e;
			e.event_id = stoi(line[0]);
			e.event_index = index;
			e.year = stoi(line[2]);
		index++;
		table.add_to_table(e);
	}

	table.print_hash_table();

	// std::vector<string> query = parse_query(argv);

	// // find
	// if (query[0] == "find")
	// {
	// 	// find event
	// 	if (query[1] == "event")
	// 	{
	// 		/* code */
	// 	}
	// 	// find max
	// 	else if (query[1] == "max")
	// 	{
	// 		// find max fatality
	// 		if (query[2] == "fatality")
	// 		{
	// 			/* code */
	// 		}
	// 		// find max 
	// 		else if (is_number(query[2]))
	// 		{
	// 			/* code */
	// 		}
	// 		else cout << "INVALID QUERY";
	// 	}
	// 	else cout << "INVALID QUERY";
	// }
	// // range
	// else if(query[0] == "range")
	// {
	// 	// range all
	//   	if (query[1] == "all")
	//   	{
	//   		/* code */
	//   	}
	//   	// range <yyyy> 
	//   	else if (is_number(query[1]))
	//   	{
	//   		/* code */
	//   	}
	//   	else cout << "INVALID QUERY";
	// }
	// // storm 1 1950

	// else if(is_number(query[0]))
	// {
	// 	int n_years = stoi(query[0]);
	// 	std::vector<int> years;
	// 	// make a vector of years one wants to get data of.
	// 	for (int i = 1; i <= n_years; ++i)
	// 		{
	// 			years.push_back(stoi(query[i]));
	// 		}	
		
	// }
	// else cout << "INVALID QUERY";


	return 0;
}