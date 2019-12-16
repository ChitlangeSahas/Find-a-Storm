#include <stdio.h>
#include <iostream>

using namespace std;

struct bst_node
{ // A binary search tree
    char *s; // String corresponding to either a state or a month_name
    int event_id ; // Identifier of storm event
    bst_node *left;  // Pointer to the left subtree
    bst_node *right;  // Pointer to the right subtree
};

class bst
{
private:
    string bst_by;
    bst_node * root ;
    int size;
    HashTable *lookup_table;
    storm_event * lookup_array;

    // A utility function to create a new BST bst_node 
    bst_node *newNode(char* str, int _event_id ) 
    { 
        bst_node *temp =  (bst_node *) malloc(sizeof(bst_node));
        temp->s = str;
        temp->right = temp ->left = NULL;
        temp->event_id = _event_id; 
        return temp; 
    } 

public:
    bst(storm_event * arr , int s, string _bst_by, char* l, char* r, HashTable h, storm_event* array)
    {
        size = s;
        bst_by = _bst_by;
        lookup_table = &h;
        lookup_array = array;

        if (bst_by == "state")root = newNode(arr[0].state, arr[0].event_id);
        if (bst_by == "month_name")root = newNode(arr[0].month_name, arr[0].event_id);

        for (int i = 1 ; i < s; ++i)
        {
            if (bst_by == "state")
            {
                insert(root, arr[i].state, arr[i].event_id);              
            }
            else if (bst_by == "month_name")
            {
                insert(root, arr[i].month_name, arr[i].event_id);
            }
        }

        if (bst_by == "state")print_within_range_states(root, l, r);
        if (bst_by == "month_name")print_within_range_months(root, l, r);
        
    };
    // ~bst();
           
    // A utility function to do inorder traversal of BST 
    void inorder(struct bst_node *r) 
    { 
        if (r != NULL) 
        { 
            inorder(r->left); 
            cout << r->event_id << endl; 
            inorder(r->right); 
        } 
    } 

    void print_bst()
    {
        inorder(root);
    }

    struct bst_node* insert(struct bst_node* node, char* month, int event_id) 
    { 
        /* If the tree is empty, return a new node */
        if (node == NULL) return newNode(month, event_id); 

        int v = strcmp(month, node->s);      
        /* Otherwise, recur down the tree */
        if (v <= 0) 
        {
            node->left  = insert(node->left, month, event_id); 
        }
        else if (v > 0) 
        {
            node->right = insert(node->right, month, event_id);  
        }  
      
        /* return the (unchanged) node pointer */
        return node; 
    } 

    void print_month_node(hash_table_entry e)
    {
        cout << "========= By Month Information =========" << endl;
        cout << "MONTH NAME\t" << lookup_array[e.event_index].month_name << endl; 
        cout << "EVENT ID\t" << lookup_array[e.event_index].event_id << endl;
        cout << "YEAR\t\t"     << lookup_array[e.event_index].year << endl;
        cout << "EVENT TYPE\t" << lookup_array[e.event_index].event_type << endl;
        cout << "CZ TYPE\t\t" << lookup_array[e.event_index].cz_type << endl;
        cout << "CZ NAME\t\t" << lookup_array[e.event_index].cz_name << endl;
        cout << "========================================" << endl;
        
    }

    void print_state_node(hash_table_entry e)
    {
        cout << "========= By State Information =========" << endl;
        cout << "STATE \t\t" << lookup_array[e.event_index].state << endl; 
        cout << "EVENT ID\t" << lookup_array[e.event_index].event_id << endl;
        cout << "YEAR\t\t"     << lookup_array[e.event_index].year << endl;
        cout << "EVENT TYPE\t" << lookup_array[e.event_index].event_type << endl;
        cout << "CZ TYPE\t\t" << lookup_array[e.event_index].cz_type << endl;
        cout << "CZ NAME\t\t" << lookup_array[e.event_index].cz_name << endl;
        cout << "========================================" << endl;
        
    }

    void print_within_range_months(bst_node *root, char* k1, char* k2)  
    {  
        /* base case */
        if ( NULL == root )  
            return;  

        int v1 = strcmp(k1, root->s); 
        int v2 = strcmp(k2 , root->s);
        
        /* Since the desired o/p is sorted,  
        recurse for left subtree first  
        If root->data is greater than k1,  
        then only we can get o/p keys  
        in left subtree */
        
        if ( v1 <= 0 )  
        {
            print_within_range_months(root->left, k1, k2);  
        }
          
        /* if root's data lies in range,  
        then prints root's data */
        if ( v1 <= 0 && v2 >= 0 )  
        {  
            print_month_node(lookup_table->find(root->event_id)); 
        }
          
        /* If root->data is smaller than k2, 
            then only we can get o/p keys  
            in right subtree */
        if ( v2 >= 0 )  
        {
            print_within_range_months(root->right, k1, k2);  
        }
    } 

    void print_within_range_states(bst_node *root, char* k1, char* k2)  
    {  
        /* base case */
        if ( NULL == root )  
            return;  
        
        /* Since the desired o/p is sorted,  
        recurse for left subtree first  
        If root->data is greater than k1,  
        then only we can get o/p keys  
        in left subtree */
        int v1 = strcmp(k1, root->s); 
        int v2 = strcmp(k2 , root->s);
        
        if ( v1 <= 0 )  
        {
            // cout << root->s  << " " << k1 << endl;
            print_within_range_states(root->left, k1, k2);  
        }
          
        /* if root's data lies in range,  
        then prints root's data */
        if (  v1 <= 0 && v2 >= 0 )  
        {
            // cout << " ** " << endl;
            // cout << k1 << " <= " << root->s << endl;
            // cout << k2 << " >= " << root->s << endl;
            // cout << " ** " << endl;
            cout << root->s << "\t" << root->event_id << endl;   
            print_state_node(lookup_table->find(root->event_id));
        }
          
        /* If root->data is smaller than k2, 
            then only we can get o/p keys  
            in right subtree */
        if (  v2 > 0 )  
        {
            // cout << root->s  << " " << k2 << endl;
            print_within_range_states(root->right, k1, k2);  
        }
    }   

    unsigned int binarytree_count_recursive(const bst_node *rt)
    {
        unsigned int count = 1;
        if (rt->left != NULL) {
           count += binarytree_count_recursive(rt->left);
        }
        if (rt->right != NULL) {
            count += binarytree_count_recursive(rt->right);
        }
        return count;
    }
     
    unsigned int binarytree_count(bst_node *r)
    {
        unsigned int count = 0;
        if (r != NULL) {
            count = binarytree_count_recursive(r);
        }
        return count;
    }

    int hieght(bst_node *root)
    {
        return ceil(log2(binarytree_count(root) + 1)) - 1;
    }
    void print_bst_information()
    {
        cout << "******************** BST INFORMATION ********************" << endl;
        cout << "Number of nodes in the BST : " <<  binarytree_count(root) << endl;
        cout << "Hieght of the BST : " << hieght(root) << endl;
        cout << "Hieght of the left BST-subtree : " << hieght(root->left) << endl;
        cout << "Hieght of the right BST-subtree : " << hieght(root->right) << endl;        
        cout << "*********************************************************" << endl;


    }
};
