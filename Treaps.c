/* This code implements treaps(Trees + Heaps) and support following functions (n is the number of elements in the treap) ->
1. insert - Expected Time complexity O(log n).
2. search - Expected Time complexity O(log n).
3. delete - Expected Time complexity O(log n).
4. Split a treap in two .
5. Inorder Traversal - which returns all the keys in a sorted arrangement, i.e., in increasing order
6. Merging the two treaps split earlier
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

typedef struct TNODE{                   // Structures is basically each node of the treap
    int key;                           // This component will the store the values of each node and follows binary tree property on minimum and maximum.
    int priority;                      //This component will store the priority of each node and the treaps are rotated with respect to the max. heap property for the priority   
    struct TNODE* left;                // left and right are the pointers pointing to the children of the node.
    struct TNODE* right;
}tnode;

tnode *l_root=NULL, *r_root=NULL, *temp=NULL;

tnode* leftrotate(tnode *root){               // rotating the treap in different manners to make sure that the treap follows the max. heap property
    tnode* y = root->right;                   
    root->right = y->left;
    y->left = root;
    return y;
}

tnode* rightrotate(tnode *root){
    tnode* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

tnode* create_node(){
    tnode* ptr = (tnode *)malloc(sizeof(tnode));             //creates a node and give initialises it's pointers to NULL
    ptr->left = ptr->right = NULL;
    ptr->key = ptr -> priority = 0;
    return ptr;
}

tnode* search(tnode *root, int value){                      //similar to the binary tree search w.r.t key.
    if(root == NULL){
        return NULL;
    }
    
    if(root->key == value){
        return root;
    }
    else if(root->key > value){
        return search(root->left, value);
    }
    else if (root->key < value){
        return search(root->right, value);
    }
}

tnode* insert(tnode *top, int key, int prior) {        //Insertion of a key
    if(top==NULL) {                                    
        tnode *temp1 = create_node();
        temp1->key = key;
        
        if(prior==0){                                   //prior = 0 means the new node has to be on root always
            temp1->priority = RAND_MAX;
        }
        else{                                          //Else random priority, as per the theory of treap which follows max heap property
            temp1->priority = rand();
        }
        return temp1;
    }

    else if(top->key < key) {             //If new key is more than the node we are currently on while recursion, we go to right child as per BST
        top->right = insert(top->right, key, prior);      
        if(top->right->priority > top->priority){         
            top=leftrotate(top);   
        }
    }

    else{                                //If new key is less than the node we are currently on while recursion, we go to left child as per BST
        top->left=insert(top->left, key, prior);     
        if(top->left->priority>top->priority){       
            top=rightrotate(top);
        }
    }

    return top;                                 //returning the top node
}

tnode* delete(tnode *root,int key) {   //function to delete a node
    if (search(root,key)==NULL) {                    //Check if element to be deleted is present or not
        printf("Element not present.\n\n");
        return root;
    }
    
    if(root==NULL)                                     //if treap is empty
        return root;


    if(key < root->key)                               //if key is in left sub-treap
        root->left = delete(root->left,key);
    
    else if(key > root->key)                          //if key is in right sub-treap
        root->right = delete(root->right, key);
    
    else if(root->left == NULL) {                     //Key found and right child replaces current node
        tnode* temp = root->right;
        free(root);
        root=temp;
    }
    
    else if(root->right == NULL) {                   //Key found and left child replaces current node
        tnode* temp = root->left;
        free(root);
        root=temp;
    }
    
    else if(root->left->priority < root->right->priority) {  //Key found and rotations used as per priority
        root = leftrotate(root);                     
        root->left = delete(root->left, key);
    }
    
    else { 
        root = rightrotate(root);
        root->right = delete(root->right, key);
    }
    
    return root;        
}

void split(tnode *root, int pivot) { //splitting a treap
    if(search(root,pivot)!=NULL){   
        root=delete(root,pivot);      //If pivot element is present, remove it and then proceed 
        root=insert(root,pivot,0);  
        l_root = root;             //left sub-treap including the node across which split was performed
        r_root = root->right;      //right sub-treap
        root->right = NULL;            
        root = NULL;

        if(l_root->left!=NULL && l_root->right!=NULL){   //THe four cases for splitting such that pivot element always has max priority 
            if(l_root->left->priority>l_root->right->priority){
                l_root->priority = l_root->left->priority + 1;
            }
            else{
                l_root->priority = l_root->right->priority+1;
            }
        }

        else if(l_root->left==NULL && l_root->right!=NULL){
            l_root->priority = l_root->right->priority+1;
        }

        else if(l_root->left!=NULL && l_root->right==NULL){
            l_root->priority = l_root->left->priority+1;
        }

        else{
            l_root->priority = 1;
        }
    }
    else{                       //Directly splitted as pivot element was not there in the treap
        root=insert(root,pivot,0);
        l_root = root->left;   //left sub-treap
        r_root = root->right;  //right sub-treap
        root->left = NULL;
        root->right = NULL;
    }
}

tnode* merge(tnode *T1, tnode *T2){  //function to merge two trees splitted initially
    tnode* root;
    if(T1==NULL){                  //If one of the treaps is NULL, return the other
        return T2;
    }

    if(T2==NULL){
        return T1;
    }

    root = create_node();       //New root 
    if (T1->priority < T2->priority) { //The treaps merged as per priority
        root->key = T1->key;
        root->priority = T1->priority;
        root->left = T1->left;
        root->right=merge(T1->right,T2);
    }
    else {
        root->key = T2->key;
        root->priority = T2->priority;
        root->left = merge(T1,T2->left);
        root->right=T2->right;
    }

    return root;
}

void inorder(tnode *top){    //Inorder traversal
    if (top==NULL) return;
    inorder(top->left);          //Checks left                      
    printf("Key : %d, Priority : %d\n", top->key,top->priority); //Prints the value    
    inorder(top->right);         //Checks right
}

void main(){
    srand(time(0));
    tnode *root=NULL;
    printf("Enter at least 1 value to form a treap: ");
    int a;
    scanf("%d", &a); //Root formed
    int choice;
    root = insert(root, a, 1);
    while (1){
        printf("Enter 1 for insert,\n2 for search,\n3 for delete,\n4 for split (note that you can use split only once, you have to merge back before using it again),\n5 for inorder traversal,\n6 for merging the 2 split trees (for that you have had to call the split function)\n7 for quit: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:{    //Insertion of key
                int key;
                printf("Enter the key you want to insert: ");
                scanf("%d", &key);
                root = insert(root, key, 1);
                printf("\n\n");
                break;
            }
            case 2:{ //Searching the key
                int key;
                printf("Enter the key you want to search: ");
                scanf("%d", &key);
                temp = search(root, key);
                if (temp==NULL) printf("Key is absent from the treap.\n\n");
                else printf("The key is present.\n\n");
                break;
            }
            case 3:{ //Deletion of Key
                int key;
                printf("Enter the key you want to delete: ");
                scanf("%d", &key);
                if (search(root,key)==NULL) {                    //Check if element to be deleted is present or not
                    printf("Element not present.\n\n");
                }
                else {
                    root = delete(root, key);                   //Deletes the node
                    printf("Element successfully deleted.\n\n");
                }
                break;
            }
            case 4:{ //Splitting the treap
                int pivot;
                printf("Enter the pivot: ");
                scanf("%d", &pivot);
                split(root, pivot);
                printf("\n");
                inorder(l_root); //Printing the first subtree
                printf("\n");
                inorder(r_root); //Printing the second subtree
                printf("\n\n");
                break;
            }
            case 5:{
                inorder(root); //Inorder traversal printing
                printf("\n\n");
                break;
            }
            case 6:{
                root = merge(l_root, r_root); //Merging the two splitted treaps
                inorder(root); //Displaying the merged treap
                printf("\n\n");
                break;
            }
            case 7:{ //To quit
                return;
            }
            default:{ //Incase of typo :)
                printf("Wrong Input. Retry.\n");
                break;
            }
        }
    }
    return;
}
