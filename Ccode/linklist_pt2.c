#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_entry
{
    int val;
    struct list_entry *next;
} list_entry_t;

list_entry_t* partition(list_entry_t* head, int x);

int main() {
    list_entry_t* head;
    list_entry_t* ptr;
    int arr[6] = {1,4,3,2,5,2};
    for (int i=0; i<6; i++)
    {
        list_entry_t* newnode = malloc(sizeof(list_entry_t));
        newnode->val = arr[i];
        newnode->next = NULL;
        if (i == 0)
        {
            head = newnode;
            ptr = newnode;
        }
        else
        {
            ptr->next = newnode;
            ptr = ptr->next;
        }
    }
    ptr = partition(head, 3);
    while(ptr != NULL)
    {
        printf("%d ", ptr->val);
        ptr = ptr->next;
    }
    return 0;
}

list_entry_t* partition(list_entry_t* head, int x)
{
    list_entry_t* l2;
    list_entry_t** p1 = &head, ** p2 = &l2;
    for (list_entry_t* node = head; node; node = node->next)
    {
        if (node->val < x)
        {
            *p1 = node;
            p1 = &((*p1)->next);
        }
        else
        {
            *p2 = node;
            p2 = &((*p2)->next);
        }
    }
    *p1 = l2;
    *p2 = NULL;
    return head;
}