#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[3][2] = {{1,2},{3,4},{5,6}};
    int b[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};
    int c[3][5] = {0};
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<5; j++)
        {
            for (int k=0; k<2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return 0;
}

