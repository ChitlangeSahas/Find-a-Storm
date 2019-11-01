#include <iostream>
// #include "ArrayList.cpp"
// #include "defn.h"

using namespace std;
class MaxHeap
{
private:
	ArrayList<storm_event> arr;
public:
	MaxHeap(ArrayList<storm_event> array_list)
	{
		arr = array_list;
		convertMaxHeap(arr.size());
	};
	// ~MaxHeap();
	  
	// to heapify a subtree with root at given index 
	void MaxHeapify(int i, int n) 
	{ 
	    int l = 2*i + 1; 
	    int r = 2*i + 2; 
	    int largest = i; 
	    if (l < n && ((arr[l]).damage_crops) > (arr[i]).damage_crops) 
	        largest = l; 
	    if (r < n && arr[r].damage_crops > arr[largest].damage_crops) 
	        largest = r; 
	    if (largest != i) 
	    { 
	        swap(arr[i], arr[largest]); 
	        MaxHeapify(largest, n); 
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
	    for (int i = 0; i < arr.size(); ++i) 
	        cout << arr[i].event_id << " "; 
	    cout << endl;
	}

  	storm_event 	extract_max()
  	{
  		storm_event max = arr.pop();
  		convertMaxHeap(arr.size());
  		return max;
  	}
};
