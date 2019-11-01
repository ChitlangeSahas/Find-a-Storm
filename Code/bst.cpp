class bst
{
public:
    bst();
    ~bst();
    struct bst_node
    { // A binary search tree
        char *s; // String corresponding to either a state or a month_name
        int event_id; // Identifier of storm event
        struct bst_node *left;  // Pointer to the left subtree
        struct bst_node *right;  // Pointer to the right subtree
    };
       
    // A utility function to create a new BST bst_node 
    struct bst_node *newNode(int item) 
    { 
        struct bst_node *temp =  (struct bst_node *)malloc(sizeof(struct bst_node)); 
        temp->event_id = item; 
        temp->left = temp->right = NULL; 
        return temp; 
    } 
       
    // A utility function to do inorder traversal of BST 
    void inorder(struct bst_node *root) 
    { 
        if (root != NULL) 
        { 
            inorder(root->left); 
            printf("%d \n", root->event_id); 
            inorder(root->right); 
        } 
    } 
       
    /* A utility function to insert a new bst_node with given event_id in BST */
    struct bst_node* insert(struct bst_node* bst_node, int event_id) 
    { 
        /* If the tree is empty, return a new bst_node */
        if (bst_node == NULL) return newNode(event_id); 
      
        /* Otherwise, recur down the tree */
        if (event_id < bst_node->event_id) 
            bst_node->left  = insert(bst_node->left, event_id); 
        else if (event_id > bst_node->event_id) 
            bst_node->right = insert(bst_node->right, event_id);    
      
        /* return the (unchanged) bst_node pointer */
        return bst_node; 
    } 
};
