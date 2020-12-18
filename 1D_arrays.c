#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void deleteAndShift(int arr[], int length, int index)
{
    for(int i = index; i < length - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
}

int main() {
    //struct timeval start, end;
    //gettimeofday(&start, NULL);

    int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = sizeof(arr) / sizeof(int);
   
    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
   
    printf("\n");    
   
    deleteAndShift(arr, size, 2);
   
    printf("Shifted array: ");
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d ", arr[i]);
    }
    
    //printf("\n"); 
    //printf("Time consumed: %lu msec.\n", (end.tv_sec - start.tv_sec ) * 1000000 + end.tv_usec - start.tv_usec);
    
    return 0;
}