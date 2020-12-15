#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1

#define ERROR_TOO_DEEP 1

#define PREORDER 1
#define INORDER 2
#define POSTORDER 3
#define LEVELORDER 4

struct node
{
    int key;
    struct node *left;
    struct node *right;
} *root = NULL;

int avgcount = 0, avgsum = 0;

struct node* create(int key)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void destroy(struct node *p)
{
    if(p == NULL) return;
   
    destroy(p->left);
    destroy(p->right);
    free(p);
}

int append(int key, struct node *p, int depth)
{
    struct node **t = NULL;
   
    if(key < p->key)
    {
        t = &p->left;
    }
    else
    {
        t = &p->right;
    }
   
    if(*t == NULL)
    {
        *t = create(key);
    }
    else
    {
        int error = append(key, *t, depth+1);
       
        if(error != 0)
        {
            return error;
        }
    }
   
    return 0;
}

int insert(int key)
{
    if(root == NULL)
    {
        root = create(key);
    }
    else
    {
        int error = append(key, root, 0);
       
        if(error != 0)
        {
            return error;
        }
    }
}

void print(struct node *p)
{
    if(p == NULL)
    {
        printf("*");
        return;
    }

    printf("%d", p->key);
   
    if(p->left != NULL || p->right != NULL)
    {
        printf(" (");
        print(p->left);
        printf(", ");
        print(p->right);
        printf(")");
    }
}

int traverse(struct node *p, int order, int depth, int level, void (*f)(int))
{
    if(p == NULL) return FALSE;
   
    switch(order)
    {
        case PREORDER:
            f(p->key);
            traverse(p->left, order, 0, 0, f);
            traverse(p->right, order, 0, 0, f);
            return TRUE;

        case INORDER:
            traverse(p->left, order, 0, 0, f);
            f(p->key);
            traverse(p->right, order, 0, 0, f);
            return TRUE;

        case POSTORDER:
            traverse(p->left, order, 0, 0, f);
            traverse(p->right, order, 0, 0, f);
            f(p->key);
            return TRUE;
           
        case LEVELORDER:
            if(level == 0)
            {
                f(p->key);
               
                for(int l=1, somethingprinted; somethingprinted; l++)
                {
                    somethingprinted = FALSE;
                    somethingprinted |= traverse(p->left, order, 1, l, f);
                    somethingprinted |= traverse(p->right, order, 1, l, f);
                }
            }
            else
            {
                if(depth == level)
                {
                    f(p->key);
                    return TRUE;
                }
                else if(depth < level)
                {
                    int somethingprinted = FALSE;
                    somethingprinted |= traverse(p->left, order, depth+1, level, f);
                    somethingprinted |= traverse(p->right, order, depth+1, level, f);
                    return somethingprinted;
                }
            }
           
        default:
            return FALSE;
    }
}

void sum(int key)
{
    avgsum+=key;
    avgcount++;
}

void out(int key)
{
    printf("%d ", key);
}

void traverseprint(int order)
{
    traverse(root, order, 0, 0, &out);
    printf("\n");
}

float traverseavg(struct node *p)
{
    avgsum = 0;
    avgcount = 0;
    traverse(p, LEVELORDER, 0, 0, &sum);
    return (float)avgsum/avgcount;
}

void readinput(const char *filename)
{
    FILE *file = fopen(filename, "r");
    int n = 0;
   
    while(!feof(file))
    {  
        fscanf (file, "%d", &n);      
        insert(n);
    }

    fclose(file);        
}

int main()
{
    readinput("input.txt");
   
    printf("Tree:\n");
    print(root);
    printf("\n");
   
    printf("Preorder:\n");
    traverseprint(PREORDER);

    printf("Inorder:\n");
    traverseprint(INORDER);

    printf("Postorder:\n");
    traverseprint(POSTORDER);

    printf("Levelorder:\n");
    traverseprint(LEVELORDER);
   
    printf("AVG left subtree:\n%f\n", traverseavg(root->left));

    destroy(root);
    return 0;
}