/* This code implements treaps and support following functionns(n is the number of elements in the treap) ->
1. search - Time complexity O(log n)
2. insert - Time complexity O(log n)
3. delete - Time complexity O(log n)
4. Join two treaps
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct TNODE{
    int key;
    int priority;
    struct TNODE* left;
    struct TNODE* right;
}tnode;
tnode* create_node(){
    tnode* ptr = (tnode*)malloc(sizeof(tnode));
    ptr->left = ptr->right = NULL;
    ptr->key = ptr -> priority = 0;
    return ptr;
}
tnode* search(tnode*root, int value){
    if(root == NULL)
        return root;
    if(root->key == value)
    return root;
    else if(root->key <value)
    return search(root->left, value); 
    else 
    return search(root->right, value);
}
tnode* insert(tnode*root, int value, int prior){
    if(root == NULL){
        root = create_node();
        root->key = value;
        root->priority = prior;
        return root;
    }
    if(root->key >value)
    root->right = insert(root->right, value, prior);
    
    else
    return root->left = insert(root->left, value, prior);
}
void priority_rotation(tnode*root, int value, int prior){

}
int main(){
    return 0;
}