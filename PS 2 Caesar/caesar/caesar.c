#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string input);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Program Accepts a Non-Negative Integer From the User, k
    // If Not 2 Arguments are Given OR the Arguments Given are Not Decimals;
    // Print an Error and Exit
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the String to an Integer
    int key = atoi(argv[1]);
    // printf("Key: %i\n", key);

    // Example:
    // char rotate_letters = rotate('A', key);
    // printf("Rotated Letter: %c\n", rotate_letters);

    string plaintext = get_string("Plaintext:  ");
    printf("Ciphertext: ");

    int count = 0;
    while (plaintext[count] != '\0')
    {
        printf("%c", rotate(plaintext[count], key));
        count++;
    }
    printf("\n");
}

// Returns True If the Input Is a Digit
// Returns False If the Input Is Not a Digit
bool only_digits(string input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        if (isdigit(input[i]))
        {
            i++;
        }
        else
        {
            return false;
        }
    }

    return true;
}

char rotate(char c, int n)
{
    int cypher_char;

    // Rotate c by n Positions If c Is Alphabetical
    // Wrapping Around Z to A (and From z to a) as Needed
    if (isalpha(c))
    {
        // Uppercase Characters
        if (isupper(c))
        {
            // Treat A as 0 and B as 1 Instead of 65 and 66, Then Add It Back
            cypher_char = (((((int) c - 65) + n) % 26) + 65);
            return (char) cypher_char;
        }
        // Lowercase Characters
        else
        {
            // Treat a as 0 and b as 1 Instead of 97 and 98, Then Add It Back
            cypher_char = (((((int) c - 97) + n) % 26) + 97);
            return (char) cypher_char;
        }
    }
    // Return c If It Is Not Alphabetical
    else
    {
        return c;
    }
}