#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get User Input Between 1 & 8 (Inclusive)
    // Declaration
    int n;
    do
    {
        n = get_int("n: ");
    }
    // If the expression inside the parantheses evaluates to true;
    // Code inside the curly braces repeates itself.
    while (n < 1 || n > 8);

    // Rows
    // Assume n = 4
    // i = 0, 1, 2, 3
    for (int i = 0; i < n; i ++)
    {
        // Columns

        // White Spaces
        // Need j = 3, 2, 1, 0
        // i = 0, j = 3, j = 2, j= 1, So Prints _ _ _ (3 Spaces)
        // i = 1, j = 3, j = 2, So Prints _ _ (2 Spaces)
        // i = 2, j = 3, So Prints _ (1 Space)
        // i = 3, j = 3, So Prints No Spaces
        for (int j = n - 1; i < j; j--)
        {
            printf(" ");
        }

        // Bricks
        // When i = 0, k = 0 So Prints #
        // When i = 1, k = 0, k = 1, So Prints ##
        // When i = 2, k = 0, k = 1, k = 2 So Prints ###
        // When i = 3, k = 0, k = 1, k = 2, k = 3 So Prints ####
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}