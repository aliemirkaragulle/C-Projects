#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool key_length(string k);
bool key_alphabetic(string k);
bool key_unique(string k);
char cipher(char c, string k);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution .KEY\n");
        return 1;
    }
    else if (!key_length(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!key_alphabetic(argv[1]))
    {
        printf("Key must only contain alphabetical characters. \n");
        return 1;
    }
    else if (!key_unique(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    string key = argv[1];
    // printf("Key: %s\n", key);

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    int i = 0;
    while (plaintext[i] != '\0')
    {
        printf("%c", cipher(plaintext[i], key));
        i++;
    }
    printf("\n");

    return 0;
}

// Validate the Key

// Key Lenght Should Be Equal to 26
// If the Key Contains 26 Characters, Return True
// If the Key Does Not Contain 26 Characters, Return False
bool key_length(string k)
{
    int length = 26;

    int i = 0;
    while (k[i] != '\0')
    {
        i++;
    }

    if (length == i)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Characters of the Key Should be Alphabetical
// If the Key Does Not Contain Any Non-Alphabetical Characters (All Alphabetical Characters), Return True
// If the Key Does Containy Any Non-Alphabetical Characters (Not All Alphabetical Characters), Return False
bool key_alphabetic(string k)
{
    int i = 0;
    while (k[i] != '\0')
    {
        if (isalpha(k[i]))
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

// Characters of the Key Should be Unique (No Repeated Characters)
// Case-Insensitive (A and a are same)
// If the Key Has No Repeated Characters, Return True
// If the Key Has Repeated Characters, Return False
bool key_unique(string k)
{
    // Imagine k = ABCDEFGHA, So n = 8
    // Loop Should Run 7 Times for;
    // 7 Times
    // 6 Times
    // ...
    // 1 Time

    // This Loop Runs 7 Times
    // 0 < 7, 1 < 7, 2 < 7, 3 < 7, 4 < 7, 5 < 7, 6 < 7
    // 0, 1, 2, 3, 4, 5, 6
    for (int i = 0, n = (strlen(k) - 1); i < n; i ++)
    {
        // 1) i = 0, j = 1, m = 8
        // 1 < 8, 1 < 7, 1 < 6, 1 < 5, 1 < 4, 1 < 3, 1 < 2
        // 2) i = 1, j = 2, m = 8
        // 2 < 8, 2 < 7, 2 < 6, 2 < 5, 2 < 4, 2 < 3
        // ...
        for (int j = i + 1, m = strlen(k); j < m; j++)
        {
            // toupper() Has Been Used Since the Function Is Case-Insensitive
            if (toupper(k[i]) == toupper(k[j]))
            {
                return false;
            }
        }
    }

    return true;
}

char cipher(char c, string k)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            return toupper(k[(int) c - 65]);
        }
        else
        {
            return tolower(k[(int) c - 97]);
        }
    }
    else
    {
        return c;
    }
}