#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int v[N];
int m[N][N];

void init()
{
    srand(time(NULL));
   
    for (int i = 0; i < N; i++)
    {
        v[i] = 1 + rand() % 9;    
    }
   
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            m[i][j] = 1 + rand() % 9;    
        }
    }
}

void print_v()
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void print_m()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int nullable(int i, int j)
{
    if((i+1 + j+1) % 2 == 0)
    {
        for (int k = 0; k < N; k++)
        {
            if(m[i][j] == v[k])
            {
                return 1;
            }
        }
    }

    return 0;    
}

void process()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(nullable(i, j))
            {
                m[i][j] = 0;
            }
        }
    }
}

int main()
{
    init();
    printf("Vector:\n");
    print_v();
    printf("Initial matrix:\n");
    print_m();
   
    process();
   
    printf("Processed matrix:\n");
    print_m();
    return 0;
}