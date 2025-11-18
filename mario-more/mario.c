#include <cs50.h>
#include <stdio.h>

int height(void);
void stairs(int h);

int main(void)
{
    // prompt user for height
    int h = height();

    // pound-sign loop
    stairs(h);
}

// height function
int height(void)
{
    int n;
    do
    {
        n = get_int("height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

// pound-sign function
void stairs(int h)
{
    for (int i = 1; i <= h; i++)
    {
        int j, k, l, m;
        for (j = 0; j < h - i; j++)
        {
            printf(" ");
        }
        for (k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("  ");

        for (l = 0; l < k; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}