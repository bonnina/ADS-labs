#include <stdio.h>
#include <math.h>

struct point 
{
    float x;
    float y;
    struct point *next;
} *start = NULL;

float weight(struct point *item)
{
    return -(fabs(item->x) + fabs(item->y));
}

void printall()
{
    if(start == NULL)
    {
        printf("EMPTY\n");
        return;
    }

    struct point *p = start;
    
    while(p != NULL)
    {
        printf("Point(%f, %f)\n", p->x, p->y);
        p = p->next;
    }
}

void printmiddle()
{
    if(start == NULL)
    {
        printf("EMPTY\n");
        return;
    }

    struct point *p = start;
    int count = 0;

    while(p != NULL)
    {
        count++;
        p = p->next;
    }
    
    p = start;
    
    for(int i=0; i < count/2; i++)
    {
        p = p->next;
    }
    
    printf("Point(%f, %f)\n", p->x, p->y);
}

void insert(struct point *item)
{
    if(start == NULL)
    {
        start = item;
        item->next = NULL;
    }
    else
    {
        struct point *p = start;
        float w = weight(item);
        
        if(w < weight(start))
        {
            item -> next = start;
            start = item;
        }
        else
        {
            while(p->next != NULL && w > weight(p->next))
            {
                p = p->next;
            }

            item->next = p->next;
            p->next = item;
        }
    }
}

void deletelast()
{
    if(start == NULL)
    {
        // do nothing
    }
    else if(start->next == NULL)
    {
        start = NULL;
    }
    else
    {
        struct point *p = start;

        while(p->next != NULL && p->next->next != NULL)
        {
            p = p->next;
        }
        
        p->next = NULL;
    }
}

void deleteall()
{
    // No need to delete list items as structs are on stack
    // and will be freed when get out of scope.
    start = NULL;
}

int main()
{
    struct point a = {1, 1, NULL}, b = {3, 3, NULL}, c = {2, 2, NULL};
    
    printf("Initial list:\n");
    printall();
    
    printf("Insert:\n");
    // Pass items by pointer to be able to change fields in the function.
    insert(&a);
    insert(&b);
    insert(&c);
    printall();
    
    printf("Middle element:\n");
    printmiddle();
    
    printf("Delete last:\n");
    deletelast();
    printall();

    printf("Delete all:\n");
    deleteall();
    printall();

    return 0;
}

