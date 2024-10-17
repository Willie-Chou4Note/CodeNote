#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define LIST_HEAD(head) struct list_head head = {&head, &head};
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

struct list_head
{
    struct list_head *prev;
    struct list_head *next;
};

typedef struct node
{
    int val;
    struct list_head list;
}node;

node *node_create(int val)
{
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->list.prev = NULL;
    newnode->list.next = NULL;
    return newnode;
}

void list_add(struct list_head *node, struct list_head *head)
{
    struct list_head *next_node = head->next;
    next_node->prev = node;
    node->next = next_node;
    node->prev = head;
    head->next = node;
}

void list_del(struct list_head *node)
{
    struct list_head *next = node->next;
    struct list_head *prev = node->prev;
    prev->next = next;
    next->prev = prev;
}

void print_list(struct list_head *head)
{
    struct list_head *iter = head->next;
    while (iter != head)
    {
        node *current_node = container_of(iter, node, list); //***return the address of struct
        printf("%d ", current_node->val);
        iter = iter->next;
    }
    printf("\n");
}

int main()
{
    int arr[5] = {2,4,6,8,9};
    LIST_HEAD(head);
    for (int i=0; i<5; i++)
    {
        node *newnode = node_create(arr[i]);
        list_add(&(newnode->list), &head);
    }
    print_list(&head);
    node *newnode = node_create(20);
    list_add(&(newnode->list), &head);
    print_list(&head);
    struct list_head *target = (&head)->next;
    list_del(target);
    print_list(&head);
    return 0;
}