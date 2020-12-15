#include <stdio.h>

int findIndex(char arr[], int size)
{
    // Returns index of searched pattern, otherwise returns -1
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == 'a' && arr[i+1] == 'a') {
            return i;
        }
    }
   
    return -1;
}

int main() {
    int size = 8;
    char arr[size] = { 'b', 'c', 'a', 'x', 'd', 'a', 'a', 'z'};
   
    int index = findIndex(arr, size);
   
    if (index != -1) {
        printf("Index: %d", index);
    }
    else {
        printf("Not found");
    }

    return 0;
}