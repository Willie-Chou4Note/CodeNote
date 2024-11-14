#include <stdio.h>
#include <stdlib.h>

void reverse_string(char *s)
{
    int len = 0;
    char *start = s;
    while(*start != '\0')
    {
        start++;
        len++;
    }
    for (int i=0; i < (len/2); i++)
    {
        s[i] = s[i] ^ s[len-i-1];
        s[len-i-1] = s[i] ^ s[len-i-1];
        s[i] = s[i] ^ s[len-i-1];
    } 
}

int main(){
    char s[20] = "Piyan Party !!";
    reverse_string(&s[0]);
    printf("%s", s);
    return 0;
}