#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <math.h>
#include "ArrayList.h"
#include "LinkedList.h"
#include "defn.h"
#include "HashTable.h"
#include "MaxHeap.cpp"
#include "bst.cpp"

#define ROOT_FOLDER "./"

ArrayList<int> years; // array to hold the years to analyze

using namespace std;


/******************************************HELPER FUNCTIONS START*************************************************/

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
        else tokens.push_back("");
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

ArrayList<string>	parse_query_cin(string query)
{
	ArrayList<string> query_v;

	query_v = str_to_vector_tokens(query, " ");
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
ArrayList<string> 	detail_file_to_array_list()
{
	ArrayList<string> lines;
	for (int i = 0; i < years.size(); ++i)
	{
		int line_n = 0;
		stringstream ss;
		ss << years[i];
		string year = ss.str();
		string FILE_PATH = string(ROOT_FOLDER) + "details-"+ year + ".csv";
		string line;
		ifstream file_stream;

		// open file and put the file into a 2d vector.
		char fp[FILE_PATH.size() + 1];
		strcpy(fp, FILE_PATH.c_str());

		file_stream.open(fp);
		// get rid of the first line
		getline(file_stream, line); 

		// make a vector 
		while(getline(file_stream, line).good()) lines.push_back(line);
	}
	return lines;
}

ArrayList<string> 	fatalities_file_to_array_list()
{
	ArrayList<string> lines;

	for (int i = 0; i < years.size(); ++i)
	{
		int line_n = 0;
		stringstream ss;
		ss << years[i];
		string year = ss.str();
		string FILE_PATH = string(ROOT_FOLDER) + "fatalities-"+ year +".csv";
		string line;
		ifstream file_stream;

		// open file and put the file into a 2d vector.
		char fp[FILE_PATH.size() + 1];
		strcpy(fp, FILE_PATH.c_str());

		file_stream.open(fp);
		// get rid of the first line
		getline(file_stream, line); 

		// make a vector 
		while(getline(file_stream, line).good()) lines.push_back(line);
	}
	return lines;
}


int 	convert_to_digits(string str)
{
	char suffix = str[str.length() - 1];
	int multiplier = 1;
	// 200K
	if (suffix == 'K') multiplier = 1000;
	// 10.0M
	else if(suffix == 'M') multiplier = 1000000;
	
	string number = "";
	for (int i = 0; i < str.length() - 1; ++i) number += str[i];

	int value = stof(number) * multiplier;
	
	return value; 
}

/*
* Print the storm storm_event_array
*/
void 	print_storm_event(storm_event se)
{
	cout << "*************" << endl;
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

	// print the fatalities
	if (se.deaths_direct != 0 || se.deaths_direct != 0 )
	{
		for (int i = 0; i < se.f->size; ++i)
		{
			cout << "=============" << endl;
			cout << "Fatality Information: " << endl;
			cout << "FATALITY ID : " << se.f->at(i).fatality_id << "\n";
			cout << "EVENT ID : " << se.f->at(i).event_id << "\n";
			cout << "FATALITY TYPE : " << se.f->at(i).fatality_type << "\n";
			cout << "FATALITY DATE : " << se.f->at(i).fatality_date << "\n";
			
			cout << "FATALITY AGE : " ; 
			if (se.f->at(i).fatality_age != -1) cout << se.f->at(i).fatality_age << endl;
			else cout << "Information N/A"<< "\n";

			cout << "FATALITY SEX : " ; 
			if (se.f->at(i).fatality_sex != ' ') cout << se.f->at(i).fatality_sex << endl;
			else cout << "Information N/A"<< "\n";

			cout << "FATALITY LOC : " ; 
			if (se.f->at(i).fatality_location[0] != ' ') cout << se.f->at(i).fatality_location << endl;
			else cout << "Information N/A"<< "\n";
			cout << "=============" << endl;
		}
	}
	else cout << "No Fatalities.\n";
	cout << "*************\n";
}

/*
* Is it a prime number?
*/
bool TestForPrime( int val )
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) ) factor++;
    return( factor > limit );
}

void print_heap_information(MaxHeap h)
{
	cout << "/**************** HEAP INFORMATION ****************/" << endl;
	cout << "Number of nodes in the heap : " << h.get_heap_size() << endl;
	cout << "Height of the Heap : " << h.height() << endl;
	cout << "Height of the left Subtree " << h.height_left_subtree() << endl;
	cout << "Height of the right Subtree " << h.height_right_subtree() << endl;
	cout << "/**************************************************/" << endl;
}

void print_HashTable_information(HashTable t)
{
	cout << "/************* HASH-TABLE INFORMATION **************/" << endl;
	cout << "Printing each chain length : " << endl;
	t.print_chain_lengths_frequency();
}
/******************************************HELPER FUNCTIONS END *************************************************/


int 	main(int argc, char const *argv[])
{
	ArrayList<string> q = parse_query(argv);

	int n_years = stoi(q[0]);

	for (int i = 0; i < n_years; ++i) years.push_back(stoi(q[i + 1]));

	ArrayList<string> details_lines = detail_file_to_array_list();
	ArrayList<string> fatality_lines = fatalities_file_to_array_list();

	int index = 0;
	int TABLE_SIZE = details_lines.size();

	int next_prime_number_table_size = 2 * TABLE_SIZE;

	bool found = false;
	while(!found)
	{
		next_prime_number_table_size += 1;
		if (TestForPrime(next_prime_number_table_size))
		{
			found = true;
			break;
		}		
	}

	HashTable table(next_prime_number_table_size, TABLE_SIZE);
	storm_event *storm_event_array = (storm_event*) malloc(next_prime_number_table_size * sizeof(storm_event));

	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		ArrayList<string> detail_line = str_to_vector_tokens(details_lines[i], ",");
		LinkedList<fatality_event> *fatality_event_linked_list = new LinkedList<fatality_event>;

		// make the hash node entry
		hash_table_entry e;
			e.event_id = stoi(detail_line[0]);
			e.event_index = index;
			e.year = stoi(detail_line[2]);

		// add the storm storm_event_array to the entry
		storm_event se;
			se.event_id = stoi(detail_line[0]);
			strcpy(se.state, detail_line[1].c_str());
			se.year = stoi(detail_line[2]);
			strcpy(se.month_name, detail_line[3].c_str());
			strcpy(se.event_type, detail_line[4].c_str());
			se.cz_type =  detail_line[5][0];
			strcpy(se.cz_name, detail_line[6].c_str());
			se.injuries_direct = stoi(detail_line[7]);
			se.injuries_indirect = stoi(detail_line[8]);
			se.deaths_direct = stoi(detail_line[9]);
			se.deaths_indirect = stoi(detail_line[10]);
			se.damage_property = convert_to_digits(detail_line[11]);
			se.damage_crops = stoi(detail_line[12]);
			strcpy(se.tor_f_scale, detail_line[13].c_str());

			
			// add the fatality storm_event_array to the entry
			fatality_event *fe = new fatality_event;
			for (int j = 0; j < fatality_lines.size(); ++j)
			{
				ArrayList<string> fatality_line = str_to_vector_tokens(fatality_lines[j] , ",");
				int f_event_id = stoi(fatality_line[1]);

				if (f_event_id == se.event_id)
				{
					fe->fatality_id = stoi(fatality_line[0]);
					fe->event_id = stoi(fatality_line[1]);
					fe->fatality_type = fatality_line[2][0];
					strcpy(fe->fatality_date, fatality_line[3].c_str());
					
					if (fatality_line[4] != "") fe->fatality_age = stoi(fatality_line[4]);
					else fe->fatality_age = -1;

					if (fatality_line[5] != "") fe->fatality_sex = stoi(fatality_line[4]);
					else fe->fatality_sex = ' ';

					if (fatality_line[6] != "") 
					{
						for (int i = 0; i < 25; ++i) fe->fatality_location[i] = fatality_line[6][i];
					}
					else fe->fatality_location[0] = ' ';
					
					fatality_event_linked_list->add(*fe);
				}
			}
			se.f = fatality_event_linked_list;

			// add the storm event to the damn storm storm_event_array array
			storm_event *ptr = storm_event_array;
			for (int i = 0; i < index; ++i)
			{
				ptr++;
			}
			*ptr = se; 

		index++; // advance the index
		table.add_to_table(e);
	}
	
	int n_queries = 0;

	cin >> n_queries;
	cin.get();

	ArrayList<string> queries;
	string query_ = "";
	
	for (int i = 0; i < n_queries; ++i)
	{
		query_ = "";
		getline(cin, query_);
		queries.push_back(query_);
	}

	for (int i = 0; i < n_queries; ++i)
	{
		ArrayList<string> query = parse_query_cin(queries[i]);
	
		// find
		if (query[0] == "find")
		{
			// find event
			if (query[1] == "event")
			{
				hash_table_entry entry_found = table.find(stoi(query[2]));
				int ei = entry_found.event_index;

				storm_event *ptr = storm_event_array;
				for (int j = 0; j < ei; ++j)
				{
					ptr++;
				}
				if (entry_found.event_id != -1)
				{
					print_storm_event(*ptr);
				}
				else
				{
					cout << "Storm Event not found." << endl;
				}

			}
			// find max
			else if (query[1] == "max")
			{
				// find max fatality
				if (query[2] == "fatality")
				{
					int max_entries = stoi(query[3]);

					if (is_number(query[4]))
					{
						int year = stoi(query[4]);
						storm_event * year_event_array = storm_event_array;

						int size = 0;
						while(year_event_array[size].event_id) size++; 
						int n_entries = 0;
						while(year_event_array[n_entries].year == year) n_entries++;
						storm_event * copy_year_event_array = (storm_event*) malloc(sizeof(storm_event) *  n_entries);
						storm_event * ptr = copy_year_event_array;

						int j = 0;
						for (int i = 0; i < size; ++i)
						{
							if (year_event_array[i].year == year)
							{	
								*ptr = year_event_array[i];
								ptr++;
							}
						}
						
						MaxHeap heap(copy_year_event_array , n_entries, "fatality");

						for (int i = 0; i < max_entries; ++i)
						{
							print_storm_event(heap.extract_max());
						}

						print_heap_information(heap); // TODO

					}
					else if (query[4] == "all")
					{
						storm_event * year_event_array = storm_event_array;
						int n_entries = 0;
						while(year_event_array[n_entries++].year);

						MaxHeap heap(year_event_array , n_entries, "fatality");

						for (int i = 0; i < max_entries; ++i)
						{
							print_storm_event(heap.extract_max());
						}
						print_heap_information(heap);
					}

				}
				// find max <number> 
				else if (is_number(query[2]))
				{
					if (is_number(query[2]) <= 50)
					{
						int max_entries = stoi(query[2]);
						int year = stoi(query[3]);

						if (query[4] == "damage_crops")
						{
							storm_event * year_event_array = storm_event_array;

							int size = 0;
							while(year_event_array[size].event_id) size++; 
							int n_entries = 0;
							while(year_event_array[n_entries].year == year) n_entries++;
							storm_event * copy_year_event_array = (storm_event*) malloc(sizeof(storm_event) *  n_entries);
							storm_event * ptr = copy_year_event_array;

							int j = 0;
							for (int i = 0; i < size; ++i)
							{
								if (year_event_array[i].year == year)
								{	
									*ptr = year_event_array[i];
									ptr++;
								}
							}
							
							MaxHeap heap(copy_year_event_array , n_entries, "damage_crops");

							for (int i = 0; i < max_entries; ++i)
							{
								print_storm_event(heap.extract_max());
							}
							print_heap_information(heap);

						}
						else if(query[4] == "damage_property")
						{
							storm_event * year_event_array = storm_event_array;

							int size = 0;
							while(year_event_array[size].event_id) size++; 
							int n_entries = 0;
							while(year_event_array[n_entries].year == year) n_entries++;
							storm_event * copy_year_event_array = (storm_event*)malloc(sizeof(storm_event) *  n_entries);
							storm_event * ptr = copy_year_event_array;

							int j = 0;
							for (int i = 0; i < size; ++i)
							{
								if (year_event_array[i].year == year)
								{	
									*ptr = year_event_array[i];
									ptr++;
								}
							}
							
							MaxHeap heap(copy_year_event_array , n_entries, "damage_property");

							for (int i = 0; i < max_entries; ++i)
							{
								print_storm_event(heap.extract_max());
							}
							print_heap_information(heap);
						}
					}

				}
				else if (query[3] == "all")
				{
					int max_entries = stoi(query[2]);
					storm_event * year_event_array = storm_event_array;
					int n_entries = 0;
					while(year_event_array[n_entries++].year);

					MaxHeap heap(year_event_array , n_entries, "damage_property");

					for (int i = 0; i < max_entries; ++i)
					{
						print_storm_event(heap.extract_max());
					}
				}
				else cout << "INVALID QUERY" << endl;
			}
			else cout << "INVALID QUERY" << endl;
		}
		// range
		else if(query[0] == "range")
		{
			// range all
		  	if (query[1] == "all")
		  	{
				storm_event * year_event_array = storm_event_array;
		  		string l = query[3];
		  		string r = query[4];

		  		char l_cstr[l.size() + 1];
				strcpy(l_cstr, l.c_str());

				char r_cstr[l.size() + 1];
				strcpy(r_cstr, r.c_str());

				int size = 0;
				while(year_event_array[size].event_id) size++;

		  		bst b(year_event_array, size, query[2], l_cstr , r_cstr, table, storm_event_array);
		  	}
		  	// range <yyyy> 
		  	else if (is_number(query[1]))
		  	{
		  		int year = stoi(query[1]);

		  		storm_event * year_event_array = storm_event_array;
		  		string l = query[3];
		  		string r = query[4];

		  		char l_cstr[l.size() + 1];
				strcpy(l_cstr, l.c_str());

				char r_cstr[l.size() + 1];
				strcpy(r_cstr, r.c_str());

				int size = 0;
				while(year_event_array[size].event_id) size++;
				int n_entries = 0;
				while(year_event_array[n_entries].year == year) n_entries++;
				storm_event * copy_year_event_array = (storm_event*) malloc(sizeof(storm_event) *  n_entries);
				storm_event * ptr = copy_year_event_array;

				int j = 0;
				for (int i = 0; i < size; ++i)
				{
					if (year_event_array[i].year == year)
					{	
						*ptr = year_event_array[i];
						ptr++;
					}
				}

		  		bst b(copy_year_event_array, n_entries, query[2], l_cstr , r_cstr, table, storm_event_array);
		  		b.print_bst_information();
		  	}
		  	else cout << "INVALID QUERY" << endl;
		}
		// storm 1 1950

		else if(is_number(query[0]))
		{
			int n_years = stoi(query[0]);
			ArrayList<int> years;
			// make a vector of years one wants to get data of.
			for (int k = 1; k <= n_years; ++k)
				{
					years.push_back(stoi(query[k]));
				}	
			
		}
		else cout << "INVALID QUERY" << endl;

		print_HashTable_information(table);
	}

	return 0;
}