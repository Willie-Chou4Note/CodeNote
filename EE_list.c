#include <stdio.h>
#include <stdlib.h>
struct node
{
    int val;
    struct p* arr;
};

struct p
{
    int data;
};

int main()
{
    struct node *head = malloc(sizeof(struct node));
    head->arr = malloc(sizeof(struct p)*5);
    head->arr[2].data = 10;
    return 0;
}
