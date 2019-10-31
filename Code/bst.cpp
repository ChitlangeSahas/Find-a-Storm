#include <stdio.h>
#include <iostream>

using namespace std;
template <class T>
struct node
{
	T value;
	node *left ;
	node *right;

	void print_node()
	{
		cout << value << endl;
	}
};

template <class T>
class bst
{
private:
	node<T> *root;
	
	node<T>* newNode(T value)
	{
		node<T>* temp = new node<T>;
		temp->value = value;
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}
	
	void _print_tree(node<T> *ptr)
	{
		if (ptr == NULL) return;
		else
		{
			cout << ptr->value << " ";	
			_print_tree(ptr->left);
			_print_tree(ptr->right);
		}
	}

public:

	bst()
	{
		root = NULL; // initialize with a nullptr
	};
	

	void add_to_tree(T value)
	{	
		cout << &root << endl;
		// if the root is empty.
		if (root == NULL) 
		{
			cout << "> root is null, creating a new node at head." << endl;
			node<T>* ptr =  root; 
			ptr = newNode(value);
			ptr->left = newNode(value);
			ptr->right = newNode(value);
			cout << &ptr << " " << &root << endl;
		}
		// else 
		// {
		// 	cout << "> root not null." << endl;
		// 	node<T> *ptr = root;
		// 	while(ptr != NULL)
		// 	{
		// 		if (value < ptr->value) // add to the left
		// 		{
		// 			cout << "> adding " << value << " to the left. " << endl;
		// 			ptr = ptr->left;
		// 		}
		// 		else
		// 		{
		// 			cout << "> adding " << value << " to the right. " << endl;
		// 			ptr = ptr->right;
		// 		}
		// 	}
		// 	ptr = newNode(value);
		// }

	}
	// ~bst();

	void print_tree()
	{
		_print_tree(root);
	}
	
};

int main(int argc, char const *argv[])
{
	bst<int> tree;
	tree.add_to_tree(11);
	tree.add_to_tree(2);
	tree.add_to_tree(20);
	tree.print_tree();
	cout << "Hello" << endl;
	return 0;
}