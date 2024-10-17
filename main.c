#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
} SS;

int ASCII_trans(char s);
void q_sort(int* arr, int start, int end);
void swap(int* s1, int* s2);
SS* insert(int data, SS* head);
SS* delete(int data, SS* head);

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr_for_sort[10] = {4,1,1,2,10,6,0,2,3,9};
    /*******link list begin***** */
    SS* head = malloc(sizeof(SS));
    head->next = NULL;
    for (int i=0; i<10; i++)
    {
        head = insert(arr_for_sort[i], head);
    }
    delete(1, head);
    SS* ptr = head->next;
    while(ptr != NULL)
    {
        printf("[%d] ", ptr->val);
        ptr = ptr->next;
    }
    /*******link list end ****** */
    //int res = binary_search(arr, 0, 9, 4);
    //int res = ASCII_trans('9');
    return 0;
}

int binary_search(int* arr, int start, int end, int target)
{
    int middle;
    while (start < end)
    {
        middle = (start + end)/2;
        if (arr[middle] < target) start = middle;
        else if (arr[middle] > target) end = middle;
        else return middle;
    }
    return 0;
}

int ASCII_trans(char s)
{
    return (int)(s - '0');
}

void q_sort(int* arr, int start, int end)
{
    if (start >= end) return;
    int key = arr[start];
    int i = start, j = end;
    while(i<j)
    {
        while(arr[i] <= key && i < end) i++;
        while(arr[j] > key && j > start) j--;
        if (i<j) swap(&arr[i], &arr[j]);
    }
    if (j != start) swap(&arr[j], &arr[start]);
    q_sort(arr, start, j-1);
    q_sort(arr, j+1, end);
}

void swap(int* s1, int* s2)
{
    *s1 = *s1 ^ *s2;
    *s2 = *s1 ^ *s2;
    *s1 = *s1 ^ *s2;
}

SS* insert(int data, SS* head)
{
    SS* newnode = malloc(sizeof(SS));
    newnode->val = data;
    newnode->next = NULL;
    if (head->next == NULL || head->next->val > data)
    {
        newnode->next = head->next;
        head->next = newnode;
    }
    else
    {
        SS* cur = head->next;
        while(cur->next != NULL)
        {
            if (cur->val <= data && cur->next->val > data) break;
            cur = cur->next;
        }
        newnode->next = cur->next;
        cur->next = newnode;
    }
    return head;
}

SS* delete(int data, SS* head)
{
    SS* cur = head->next;
    SS* pre;
    while(cur->next != NULL)
    {
        if (cur->val == data) break;
        pre = cur;
        cur = cur->next;
    }
    // dont match
    if (cur->val != data) return head;
    // first element
    if (cur->val == head->next->val)
    {
        head->next = cur->next;
        free(cur);
        return head;
    }
    // middle element | last element
    else
    {
        pre->next = cur->next;
        free(cur);
        return head;
    }
}