#include <stdio.h>

void str_cpy(char *s, char *t)
{
    while(*s != '\0')
    {
        *t = *s;
        t++;
        s++;
    }
}

int main()
{
    char *s = "ABCDEF";
    char res[10];
    str_cpy(s, res);
    for (int i=0; res[i] != '\0'; i++)
    {
        printf("%c", res[i]);
    }
    return 0;
}

