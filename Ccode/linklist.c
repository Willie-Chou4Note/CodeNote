#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
}node_t;

void append_node(node_t *head, int val);
void delete_node(node_t *head, int val);

int main()
{
    node_t *head = malloc(sizeof(node_t));
    head->val = 0xFFFF;
    head->next = NULL;
    append_node(head, 40);
    append_node(head, 25);
    append_node(head, 4);
    append_node(head, 15);
    append_node(head, 32);
    append_node(head, 7);
    delete_node(head, 4);
    node_t *ptr = head->next;
    while(ptr != NULL)
    {
        printf("%d->", ptr->val);
        ptr = ptr->next;
    }
    return 0;
}

void append_node(node_t *head, int val)
{
    node_t *newnode = malloc(sizeof(node_t));
    newnode->val = val;
    newnode->next = NULL;
    if (head->next == NULL || head->next->val > val)
    {
        newnode->next = head->next;
        head->next = newnode;
    }
    else
    {
        node_t *ptr = head->next;
        while(ptr->next != NULL)
        {
            if (ptr->val < val && ptr->next->val >= val) break;
            ptr = ptr->next;
        }
        newnode->next = ptr->next;
        ptr->next = newnode;
    }
};

void delete_node(node_t *head, int val)
{
    node_t *ptr = head->next;
    if (ptr->val == val)
    {
        head->next = ptr->next;
        free(ptr);
        return;
    }
    else
    {
        node_t *prev = head;
        while(ptr != NULL)
        {
            if (ptr->val == val)
            {
                prev->next = ptr->next;
                free(ptr);
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }
    }
}