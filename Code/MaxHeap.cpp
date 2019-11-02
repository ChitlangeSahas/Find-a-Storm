#include <iostream>

using namespace std;
class MaxHeap
{
private:
	int size = 0;
	storm_event *arr;
	string sort_by;
public:

	MaxHeap(storm_event* array_list, int s , string _sort_by)
	{
		arr = array_list;
		size = s;
		sort_by = _sort_by;
		convertMaxHeap(size);
	};
	// ~MaxHeap();
	  
	// to heapify a subtree with root at given index 
	void MaxHeapify(int i, int n) 
	{ 
	    int l = 2*i + 1; 
	    int r = 2*i + 2; 
	    int largest = i;

	    if (sort_by == "damage_crops")
	    {    	
		    if (l < n && ( (arr[l]).damage_crops) > (arr[i]).damage_crops ) 
		        largest = l; 
		    if (r < n && arr[r].damage_crops > arr[largest].damage_crops) 
		        largest = r; 
		    if (largest != i) 
		    { 
		        swap(arr[i], arr[largest]); 
		        MaxHeapify(largest, n); 
		    } 
	    }
	    else if(sort_by == "damage_property")
	    {
	        if (l < n && ((arr[l]).damage_property) > (arr[i]).damage_property) 
		        largest = l; 
		    if (r < n && arr[r].damage_property > arr[largest].damage_property) 
		        largest = r; 
		    if (largest != i) 
		    { 
		        swap(arr[i], arr[largest]); 
		        MaxHeapify(largest, n); 
		    } 
	    }

	} 
	  
	// This function basically builds max heap 
	void convertMaxHeap(int n) 
	{ 
	    // Start from bottommost and rightmost 
	    // internal mode and heapify all internal 
	    // modes in bottom up way 
	    for (int i = (n-2)/2; i >= 0; --i) 
	        MaxHeapify(i, n); 
	} 
	  
	// A utility function to print a given array 
	// of given size 
	void printHeap() 
	{ 
	    for (int i = 0; i < size; ++i) 
	        cout << arr[i].event_id << " "; 
	    cout << endl;
	}

  	storm_event 	extract_max()
  	{
  		storm_event max = arr[0];
  		arr++;
  		size--;
  		convertMaxHeap(size);
  		return max;
  	}
};
