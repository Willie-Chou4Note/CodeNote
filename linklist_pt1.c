#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_entry
{
    int value;
    struct list_entry *next;
} list_entry_t;

void remove_node(list_entry_t* head, int value)
{
    list_entry_t** indirect = &head;
    while((*indirect)->value != value) indirect = &((*indirect)->next);
    *indirect = (*indirect)->next;
}

void append_node(list_entry_t* head, int value)
{
    list_entry_t* newnode = malloc(sizeof(list_entry_t));
    newnode->value = value;
    newnode->next = NULL;
    list_entry_t** indirect = &head;
    while((*indirect) != NULL) indirect = &((*indirect)->next);
    (*indirect) = newnode;
}

int main() {
    list_entry_t* head;
    list_entry_t* ptr;
    for (int i=0; i<5; i++)
    {
        list_entry_t* newnode = malloc(sizeof(list_entry_t));
        newnode->value = i;
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
    remove_node(head, 3);
    append_node(head, 7);
    ptr = head;
    while(ptr != NULL)
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    return 0;
}