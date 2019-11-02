
struct hashNode
{
	LinkedList<hash_table_entry> list;

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
