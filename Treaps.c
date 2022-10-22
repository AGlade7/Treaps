/* This code implements treaps(Trees + Heaps) and support following functionns(n is the number of elements in the treap) ->
1. search - Expected Time complexity O(log n).
2. insert - Expected Time complexity O(log n).
3. delete - Expected Time complexity O(log n).
4. Join two treaps.
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct TNODE{                   // Structures is basically each node of the treap
    int key;                           // This component will the store the values of each node and follows binary tree property on minimum and maximum.
    int priority;                      /*This component will store the priority of each node and the treaps are rotated with respect to the max. heap 
                                        property for the priority*/   
    struct TNODE* left;                // left and right are the pointers pointing to the children of the node.
    struct TNODE* right;
}tnode;
tnode* create_node(){
    tnode* ptr = (tnode*)malloc(sizeof(tnode));             //creates a node and give initialises it's pointers to NULL
    ptr->left = ptr->right = NULL;
    ptr->key = ptr -> priority = 0;
    return ptr;
}
tnode* search(tnode*root, int value){                      //similar to the binary tree search w.r.t key.
    if(root == NULL)
        return root;
    if(root->key == value)
    return root;
    else if(root->key <value)
    return search(root->left, value); 
    else 
    return search(root->right, value);
}
tnode* insert(tnode*root, int value, int prior){            // It's incomplete. In the repository they have made priorities as random numbers. so we might need to edit it regarding it like if want given priorities or random ones
    if(root == NULL){                                       
        root = create_node();
        root->key = value;
        root->priority = prior;
         return root;
    }
    else if(root->key == value){
    printf("The key already exist");
    return root;
    }
    else if(root->key >value){
    root->right = insert(root->right, value, prior);
    if(root->priority > root->right->priority)
    root = leftrotate(root);
    }
    else{
    root->left = insert(root->left, value, prior);
    if(root->priority > root->left->priority)
    root = rightrotate(root);
    }
}
tnode* leftrotate(tnode*root){               // rotating the tree in different manners to make sure that the treap follows the max. heap property
    tnode* y = root->right;
    root->right = y->left;
    y->left = root;
    return y;
}
tnode* rightrotate(tnode*root){
    tnode* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}
int main(){
    return 0;
}
