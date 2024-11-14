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
    int a = 10;
    int b = 0x8F;
    char c = 'a';
    char s[10] = "Hello";
    printf("DECint: %d, HEXint: 0x%x, char: %c, string: %s", a, b, c, s);
    return 0;
}
