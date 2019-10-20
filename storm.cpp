#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
// #include <vector>
#include "defn.h"

/*
* No vectors? I made an Arraylist class.
*/
template <class T>
class  ArrayList {
public:

    typedef T* Iterator;

    ArrayList();
    ArrayList(unsigned int size);
    ArrayList(unsigned int size, const T & initial);
    ArrayList(const ArrayList<T>& v);
    ~ArrayList();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T & operator[](unsigned int index);
    ArrayList<T> & operator = (const ArrayList<T> &);
    void clear();
private:
    unsigned int _size;
    unsigned int _capacity;
    unsigned int Log;
    T* buffer;
};

template<class T>
ArrayList<T>::ArrayList() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
    Log = 0;
}


template<class T>
ArrayList<T>& ArrayList<T>::operator = (const ArrayList<T> & v) {
    delete[] buffer;
    _size = v._size;
    Log = v.Log;
    _capacity = v._capacity;
    buffer = new T [_capacity];
    for (unsigned int i = 0; i < _size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
void ArrayList<T>::push_back(const T & v) {
    /*
        Incidentally, one common way of regrowing an array is to double the size as needed.
        This is so that if you are inserting n items at most only O(log n) regrowths are performed
        and at most O(n) space is wasted.
    */
    if (_size >= _capacity) {
        reserve(1 << Log);
        Log++;
    }
    buffer [_size++] = v;
}

template<class T>
void ArrayList<T>::pop_back() {
    _size--;
}

template<class T>
void ArrayList<T>::reserve(unsigned int capacity) {
    T * newBuffer = new T[capacity];

    for (unsigned int i = 0; i < _size; i++)
        newBuffer[i] = buffer[i];

    _capacity = capacity;
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
unsigned int ArrayList<T>::size() const {
    return _size;
}

template<class T>
T& ArrayList<T>::operator[](unsigned int index) {
    return buffer[index];
}

template<class T>
ArrayList<T>::~ArrayList() {
    delete[] buffer;
}

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

struct hashNode
{
	LinkedList list;

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

	hash_table_entry at(int index)
	{
		return list.at(index);
	} 

	hash_table_entry find(int event_id)
	{
		return list.find(event_id);
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

	int hash_it(int event_id)
	{
		return (event_id % T_SIZE);  
	}

	hashNode at(int index)
	{
		hashNode *ptr = hash_table_head;
		for (int i = 0; i < index; ++i)
		{
			ptr++;
		}
		return *ptr;
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

	hash_table_entry find(int event_id)
	{
		int key = hash_it(event_id);

		hashNode n = at(key);
		return n.find(event_id);
	}

	// ~HashTable();
};

/*
* convert the string into vector tokens
*/
ArrayList<string>  	str_to_vector_tokens(std::string str, std::string delim)
{
    ArrayList<string> tokens;
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
ArrayList<string>	parse_query(char const *argv[])
{
	int i = 1;
	string query = "";
	while(argv[i])
	{
		query += (argv[i]);
		query += ",";
		i++; 
	}
	ArrayList<string> query_v;

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
ArrayList<string> 	file_to_vector()
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

	ArrayList<string> lines;

	// make a vector 
	while(getline(file_stream, line).good())
	{
		lines.push_back(line);
	}
	return lines;
}

int 	convert_to_digits(string str)
{
	char suffix = str[str.length() - 1];
	int multiplier = 1;

	// 200K
	if (suffix == 'K')
	{
		multiplier = 1000;
	}
	// 10.0M
	else if(suffix == 'M')
	{
		multiplier = 1000000;
	}
	
	string number = "";
	for (int i = 0; i < str.length() - 1; ++i)
	{
		number += str[i];
	}

	int value = stof(number) * multiplier;
	
	return value; 
}

/*
* Print the storm event
*/
void 	print_storm_event(storm_event se)
{
	cout << "EVENT ID : " << se.event_id << "\n";
	cout << "STATE : " << se.state << "\n";	
	cout << "YEAR : " << se.year << "\n";	
	cout << "MONTH : " << se.month_name << "\n";
	cout << "EVENT TYPE : " << se.event_type << "\n";
	cout << "CZ TYPE : " << se.cz_type << "\n";
	cout << "CZ NAME : " << se.cz_name << "\n";
	cout << "INJURIES DIRECT : " << se.injuries_direct << "\n";
	cout << "INJURIES INDIRECT : " << se.injuries_indirect << "\n";
	cout << "DEATHS DIRECT: " << se.deaths_direct << "\n";
	cout << "DEATHS INDIRECT : " << se.deaths_indirect << "\n";
	cout << "DAMAGE PROPERTY : " << se.damage_property << "\n";
	cout << "DAMAGE CROPS : " << se.damage_crops << "\n";
	cout << "TOR F Scale : " << se.tor_f_scale << "\n";	 
}

int 	main(int argc, char const *argv[])
{
	ArrayList<string> lines = file_to_vector();

	int index = 0;
	int TABLE_SIZE = lines.size();

	HashTable table(TABLE_SIZE);
	storm_event *event = (storm_event*) malloc(TABLE_SIZE * sizeof(storm_event));


	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		ArrayList<string> line = str_to_vector_tokens(lines[i], ",");
		hash_table_entry e;
			e.event_id = stoi(line[0]);
			e.event_index = index;
			e.year = stoi(line[2]);


		storm_event se;
			se.event_id = stoi(line[0]);
			strcpy(se.state, line[1].c_str());
			se.year = stoi(line[2]);
			strcpy(se.month_name, line[3].c_str());
			strcpy(se.event_type, line[4].c_str());
			se.cz_type =  line[5][0];
			strcpy(se.cz_name, line[6].c_str());
			se.injuries_direct = stoi(line[7]);
			se.injuries_indirect = stoi(line[8]);
			se.deaths_direct = stoi(line[9]);
			se.deaths_indirect = stoi(line[10]);
			se.damage_property = convert_to_digits(line[11]);
			se.damage_crops = stoi(line[12]);
			strcpy(se.tor_f_scale, line[13].c_str());

			// add the storm event to the damn storm event array
			storm_event *ptr = event;
			for (int i = 0; i < index; ++i)
			{
				ptr++;
			}
			*ptr = se; 

		index++;
		table.add_to_table(e);
	}

	ArrayList<string> query = parse_query(argv);

	// find
	if (query[0] == "find")
	{
		// find event
		if (query[1] == "event")
		{

			int ei = table.find(stoi(query[2])).event_index;
			storm_event *ptr = event;
			for (int i = 0; i < ei; ++i)
			{
				ptr++;
			}
			print_storm_event(*ptr);
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
		ArrayList<int> years;
		// make a vector of years one wants to get data of.
		for (int i = 1; i <= n_years; ++i)
			{
				years.push_back(stoi(query[i]));
			}	
		
	}
	else cout << "INVALID QUERY";


	return 0;
}