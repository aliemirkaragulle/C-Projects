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
        // When i = 0, j = 0 So Prints #
        // When i = 1, j = 0, j = 1, So Prints ##
        // When i = 2, j = 0, j = 1, j = 2 So Prints ###
        // When i = 3, j = 0, j = 1, j = 2, j = 3 So Prints ####
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
