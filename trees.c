#include <stdio.h>
#include <math.h>

struct node 
{
    int key;
    struct node *left;
    struct node *right;
} *root = NULL;

void insert(int key, struct node *)
{
    if(root == NULL)
    {
        struct node n = { key, NULL, NULL};
        root = &n;
    }
    else
    {
        struct node *p = start;
        
    }
}

void print()
{
    if(root == NULL)
    {
        printf("EMPTY");
        return;
    }

    printf("%d\n", root->key);
}

int main()
{
    insert(1);
    print();
    return 0;
}

