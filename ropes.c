#include <stdio.h>//all header file used in the code
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

#define MAL (struct ropes *)malloc(sizeof(struct ropes))        // macro is used to allocate memory using malloc function
#define MAl (struct node_char *)malloc(sizeof(struct node_int)) // macro is used to allocate memory using malloc function
#define F printf                                                // macro is used to print the value;
#define loop(i, a, n) for (int i = a; i < n; i++)//macro used for for loop
#define loop1(i, a, n) for (int i = a; i <= n; i++)
#define rloop(i, a, n) for (int i = n - 1; i >= a; i--)

const int maxleaf;//how many elements you want to put in leaf nodes

struct ropes//struct variable which is cotaining our tree nodes and connectors
{
    struct ropes *left;
    struct ropes *right;
    int data;
    char *str;
} *root1, *root2, *root;

void printstring(struct ropes *root1)//fuction to print final string after concatenating
{
    if (root1 == NULL){ return; }

    if (root1->left == NULL && root1->right == NULL)
    {
        int sie = sizeof(root1->str)/sizeof(root1->str[0]);
        loop(i,0,sie) 
        {
            if(root1->str[i]>='a' && root1->str[i] <= 'z') printf("%c",root1->str[i]);
        }
    }
    printstring(root1->left);//print is same as the binary search tree
    printstring(root1->right);
}

void create_rope(struct ropes **boot1,char *arr, int left, int right)//creating tree of chareacters and giving the max priority property 
{
    struct ropes *temp = MAL;//creating temperary struct variable 
    temp->left = temp->right = NULL;//intialising it by NULL

    if (right - left > maxleaf)//when difference is greater than maxleaf
    {
        temp->str = NULL;
        temp->data = (right - left) / 2;
        // printf("%d ",maxleaf);
        *boot1 = temp;
        create_rope(&(*boot1)->left, arr, left, (left + right) / 2);//recursion
        create_rope(&(*boot1)->right, arr, (left + right) / 2 + 1, right);
    }

    else
    {
        temp->data = right - left;
        int j = 0;
        // printf("%d - %d ",left,right);
        temp->str = (char *)malloc((maxleaf)*sizeof(char));
        loop1(i, left, right) { temp->str[j++] = arr[i]; } // printf("%c",temp->str[j-1]);}
        *boot1 = temp;
    }
    
}

struct ropes* concatenate(struct ropes* root,struct ropes* root1,int size)
{
    root2 =NULL;
    struct ropes* temp=MAL;
    temp->left =root;//adding one string with other ;
    temp->right = root1;
    temp->data = size;
    temp->str = NULL;
    root2 = temp;
    return root2;//returning final concatinated string 
}

int main()
{
    root1 = root2 = root = NULL;
    int n;
    printf("enter how many elements you want to put in leaf nodes: ");
    scanf("%d", &maxleaf);
    printf("number of strings you want to add: ");
    scanf("%d", &n);

    for (int j = 0; j < n; j++)
    {
        int size; 
        printf("given size of string: ");
        scanf("%d", &size);
        char arr[size];
        printf("enter the string here : ");
        scanf("%s", arr);
        create_rope(&root1, arr, 0, size - 1);
        root = concatenate(root,root1,size);//concetenating two string with each other
        root1 = NULL;//after concatenating making it again NULL to take again new string
    }
    printstring(root);//printing whole string after concatenating;
}