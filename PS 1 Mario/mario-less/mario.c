#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get User Input Between 1-8 (Inclusive)
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Rows
    for (int i = 0; i < n; i ++)
    {
        // Columns

        // White Spaces
        for (int j = n - 1; i < j; j--)
        {
            printf(" ");
        }

        // First #'s
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // White Space
        printf("  ");

        // Second #'s
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }

        // New Line
        printf("\n");
    }
}