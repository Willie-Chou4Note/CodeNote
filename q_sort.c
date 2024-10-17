#include <stdio.h>
#include <stdlib.h>

void q_sort(int* arr, int start, int end);
void swap(int* s1, int* s2);

int main()
{
    int arr[4] = {4,5,8,2};
    q_sort(arr, 0, 3);
    for (int i=0; i<4; i++)
    {
        printf("[%d]" , arr[i]);
    }
    return 0;
}

void q_sort(int* arr, int start, int end)
{   
    if (start >= end) return;
    int key = arr[start], i = start, j = end;
    while(i < j)
    {
        while(i < end && arr[i] <= key)
        {
            i++;
            printf("i = %d", i);
        }
        printf("\n");
        while(j > start && arr[j] > key)
        {
            j--;
            printf("j = %d", j);
        }
        printf("\n");
        if (i < j) swap(&arr[i], &arr[j]);
    }
    if (j != start) swap(&arr[j], &arr[start]);
    printf("start = [%d] j = [%d]", start, j);
    printf("\n");
    q_sort(arr, start, j-1);
    q_sort(arr, j+1, end);
}

void swap(int* s1, int* s2)
{
    *s1 ^= *s2;
    *s2 ^= *s1;
    *s1 ^= *s2;
}
