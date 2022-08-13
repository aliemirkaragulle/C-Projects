#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Variable That Will Store the Score of the Words
    int score = 0;

    // Iterate Through the Word Until the Null Character (NULL)
    int i = 0;
    while (word[i] != '\0')
    {
        // If The Indexed Char Is a Letter
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
        {
            // If char is Uppercase
            if (isupper(word[i]))
            {
                // Add the Corresponding Value of the Letter to score
                score += POINTS[word[i] - 65];
                // Iterate
                i ++;
            }
            // If char is Lowercase
            else
            {
                // Add the Corresponding Value of the Letter to score
                score += POINTS[word[i] - 97];
                // Iterate
                i ++;
            }
        }
        // If the Indexed Char Is Not a Letter
        // Iterate & Do Nothing
        else
        {
            i ++;
        }
    }

    return score;
}