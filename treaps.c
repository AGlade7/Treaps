#include <stdio.h>//all header file used in the code
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include<stdbool.h>  

#define MAL (struct treaps *)malloc(sizeof(struct treaps))        // macro is used to allocate memory using malloc function
#define MAl (struct treaps_char *)malloc(sizeof(struct treaps_int)) // macro is used to allocate memory using malloc function
#define P printf                                                // macro is used to print the value;
#define loop(i, a, n) for (int i = a; i < n; i++)//macro used for for loop
#define loop1(i, a, n) for (int i = a; i <= n; i++)
#define rloop(i, a, n) for (int i = n - 1; i >= a; i--)

struct treaps//structure variable for our b tree;
{
    int data;
    int height;
    int priority;
    struct treaps* left;
    struct treaps* right;
}*root=NULL,*top,*temp2,*jen =NULL;//root point pointing to b tree;

int size =0;
struct treaps* Treaps_create(int data)//intialising any new treaps with value of structure variables
{
    struct treaps* x = MAL;//memory allcation
    x->data = data;
    x->height = 0;
    x->priority = rand();
    x->left = NULL, x->right = NULL;
    return x;//returning after initialising;
}

int max(int a, int b)//finding maximum between left side height and right side height;
{
    if(a>b) return a;
    else return b;
}

int height(struct treaps* boot)//finding height of left side of avl tree and right side of avl tree;
{
    if(boot == NULL) return 0;
    else{
        return 1+max(height(boot->left) , height(boot->right));
    }
}

int balance(struct treaps* boot)//calculating the balancing factor of treaps 
{
    if(boot == NULL) return 0;
    else{
        int left_height = height(boot->left);
        int right_height = height(boot->right);
        return (left_height-right_height);//returnng balance factor which is the difference between left height and right height.
    }
}

struct treaps* right_rotate(struct treaps* boot )//when not balance it will rotate the treaps in right .
{
    struct treaps* temp = boot->right;
    struct treaps* temp2 = temp->left;

    temp->left = boot;
    boot->right = temp2;

    boot->height = height(boot);
    temp->height = height(temp);
    return temp;
}

struct treaps* left_rotate(struct treaps* root)//when not balance it will rotate the treaps in left;
{
    struct treaps* temp = root->left;
    struct treaps* temp2 = temp->right;

    temp->right = root;
    root->left = temp2;

    root->height = height(root);
    temp->height = height(temp);

    return temp;
}

int found= 0;//variable define to check that searching element exists or not;

struct treaps* search(struct treaps* x, int data)//functon which is using to search the user input element;
{
    if(x == NULL) {P("not present\n");}
    else
    {
        if(data == x->data) {found++; top = x;}
        else if(data < x->data) search(x->left,data);//recursive call till x becomes NULL or found element;
        else if(data > x->data) search(x->right,data);
    }
    return top;//return that treaps at which we found the data;
}

void preorder(struct treaps *boot)//print the preorder sequence of AVL tree
{
    if(boot != NULL)
    {
        printf("%d ", boot->data);
        preorder(boot->left);
        preorder(boot->right);
    }
}

void inorder(struct treaps* treaps)//print the inorder sequence of AVL tree 
{
    if(treaps == NULL) return;
    else{
        inorder(treaps->left);
        printf("%d ",treaps->data);
        inorder(treaps->right);
    }
}

struct treaps* Join(struct treaps* r1,struct treaps* r2)
{
    struct treaps* temp=NULL;
    if(r1 == NULL) {return r2 ;}
    else if(r2 == NULL) {return r1;}

    if(r1->priority < r2->priority && r1 != NULL && r2 != NULL)
    {
        temp = Treaps_create(r1->data);
        temp->priority = r1->priority;
        temp->left = r1->left;
        temp->right = Join(r1->right,r2);
    }
    else if(r1->priority > r2->priority && r1 != NULL && r2 != NULL){
        temp = Treaps_create(r2->data);
        temp->priority = r2->priority;
        temp->left = Join(r1,r2->left);
        temp->right = r2->right;
    }
    return temp;
}

struct treaps* split(struct treaps** less,struct treaps** gtr,struct treaps* r,int data)
{
    if(r == NULL){*less = *gtr = NULL; return NULL;}
    struct treaps* temp = Treaps_create(r->data);
    temp->priority = r->priority;
    if(r->data < data)
    {
        *less = temp;
        return split(&(temp->right),gtr,r->right,data);
    }
    else if(r->data > data){
        *gtr = temp;
        return split(less,&(temp->left),r->left,data);
    }
    else{
        *less = r->left;
        *gtr = r->right;
        return temp;
    }
}

struct treaps* deletion(struct treaps* boot,int data)
{
    //struct treaps* temp = root;
    if(boot == NULL) return boot;
    else if(boot->data > data) boot->left = deletion(boot->left,data);
    else if(data > boot->data) boot->right = deletion(boot->right,data);
    else{
        if (boot->left == NULL) {
            struct treaps* temp = boot->right;
            free(boot);
            return temp;
        }
        else if (boot->right == NULL) {
            struct treaps* temp = boot->left;
            free(boot);
            return temp;
        }
        else if(root->left->priority < root->right->priority)
        {
            root = right_rotate(root);
            root->left = deletion(root->left,data); 
        }
        else{
            root = left_rotate(root);
            root->left = deletion(root->left,data); 
        }
    } 

    boot->height = height(boot);
    int balance_factor = balance(boot);
    return boot;
}

struct treaps* insert_tree(struct treaps* root, int data)//inserting data and after avery insertion balacing the inserted treaps in tree and updating the height of tree.
{
    if(root == NULL ) //only if root is null ;
    {
        //struct treaps* temp = MAL;
        return Treaps_create(data);
    }
    else{
        if(data > root->data) {
        	root->right = insert_tree(root->right,data);
        	if(root->right->priority > root->priority) root=right_rotate(root);
        }//recursion function till treaps does not becomes null;
        else if(data == root->data) {P("duplicate number"); exit;}//if we insert a duplicate number.
        else {
        	root->left = insert_tree(root->left,data);
        	if(root->left->priority > root->priority) root = left_rotate(root);
        }
    }
    root->height = height(root);//maximum height of avl tree
    //P("%d\n", root->height);
    int balance_factor = balance(root);//
    //P("%d\n", balance_factor);
    return root;//returning the tree final tree after balancing .
}

struct treaps* minValueNode(struct treaps* current)
{
    while (current && current->left != NULL)  current = current->left;
    return current;
}

void calling(struct treaps* x)//switch case function to do different type of operation 
{
    struct treaps* temp=NULL;
    char c;
    while(c != 'q')//loop will execute till user does not quit the loop means does not enter the q;
    {
        P("i) insert: \n");
        P("s) search: \n");
        P("p) preorder and inorder: \n");
        P("q) quit: \n");
        P("b) split: \n");
        P("j) join: \n");
        P("enter a choice: ");
        scanf("%c",&c);
        
        switch(c)
        {
            case 'i'://i tends for insertion in out tree
            {
                P("enter a data to insert :");
                int new_data; scanf("%d",&new_data); size++;
                x = insert_tree(x,new_data);
                root = x;
                P("\n");
                break;
            }
            case 's'://s tending for searching any element such that it is in our tree or not;
            {
                P("enter data you want to search: ");
                int new_data;scanf("%d",&new_data);
                temp = search(x,new_data);//

                if(found != 0) {P("present\n");}
                if(found != 0)
                {
                    int balance_factor = balance(temp);//if we find search element then it will find the balancing factor of element 
                    P("balance factor of %d is:%d\n",new_data,balance_factor);
                    int height_f = height(temp);
                    P("height of %d in treap tree is:%d ",new_data,abs(temp->height-1));//there i will got the height of the treaps where element exists
                    found =0;
                }
                P("\n");
                break; 
            }
            case 'p'://p implies for prints the differnt sequences of tree like preorder and inorder;
            {
                preorder(x);P("\n");
                inorder(x);P("\n");
                break;
            }
            case 'd':
            {
                P("enter a number to delete: ");
                int d; scanf("%d",&d);
                temp = search(x,d);//

                if(found != 0) 
                {
                    x = deletion(x,d);
                    root =x;
                    preorder(x);
                    P("\n");
                    found = 0;
                }
                break;
            }
            case 'b':
            {
                int data;
                P("enter a number to split from : ");
                scanf("%d",&data);
                struct treaps* temp = search(x,data);
                struct treaps* less= NULL;
                struct treaps* gtr = NULL;
                split(&less,&gtr,x,data);
                preorder(less);P("\n");
                inorder(less);P("\n");
                preorder(gtr);P("\n");
                inorder(gtr);P("\n");
            }
            case 'j':
            {
                int join;
                printf("enter how many treaps tree you want to join: ");
                scanf("%d",&join);
                loop(i,0,join)
                {
                    int size_1;
                    printf("enter the size of another treap tree: ");
                    scanf("%d",&size_1);
                    for(int j =0;j<size_1 ; j++)
                    {
                        int data;
                        scanf("%d",&data);
                        temp2 = insert_tree(temp2,data);
                        //if(getchar() == '\n') break;
                    }
                    root = Join(root,temp2);
                    temp2 = NULL;
                }
                x = root;
                preorder(root);P("\n");
                inorder(root);P("\n");
            }
            case 'q': //q tends for break the loop 
            {
                P("quit ");
                break;
            } 
            default: {P("invalid input\n");break;}//if given input is differnt from which user should give from above 4 (i,s,p,q).then print invalid input;
        }
        char end;scanf("%c",&end); 
    }
}

int main()//main function which is insert the data in tree
{
    root = top=temp2= NULL;
    struct treaps* temp;
    temp = NULL;
    for(int i =0;i<=24 ; i++)
    {
        size++;
        root = insert_tree(root,i);
        //if(getchar() == '\n') break;
    }
    temp = root;
    calling(temp);//calling that function which is doing different operations.
}