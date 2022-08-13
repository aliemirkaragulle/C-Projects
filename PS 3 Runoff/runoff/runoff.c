#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i ++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // An int Which Will Store the Index of the First Choice Candidate of a Voter
    int first_choice;

    // Loop Through the Voters
    for (int i = 0; i < voter_count; i ++)
    {
        // Voters First Choices
        first_choice = preferences[i][0];

        // If the Person Voted For Has Not Been Eliminated
        if (candidates[first_choice].eliminated == false)
        {
            // Increment His/Her Vote Count
            candidates[first_choice].votes ++;
        }
        // If the Person Voted For Has Beeen Eliminated
        else
        {
            int j = 1;
            while (true)
            {
                // Check for That Voters Other Preferred Candidates Iteratively
                first_choice = preferences[i][j];

                // Check If That Voter Has Been Eliminated
                if (candidates[first_choice].eliminated == false)
                {
                    // If Not, Increment That Candidates Vote
                    candidates[first_choice].votes ++;
                    // Break Out of The Loop
                    break;
                }
                else
                {
                    // If Eliminated, Try Other Candidates
                    j ++;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // An int Representing The Number of Votes a Candidate Should Have to Win the Election
    int majority = ((voter_count / 2) + 1);

    for (int i = 0; i < voter_count; i ++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // An int Representing the Minimum Number of Votes Given to a Voter(s)
    int min = candidates[0].votes;

    for (int i = 0; i < candidate_count; i ++)
    {
        // If the Candidate Has Not Been Eliminated AND Its Votes is Lower Than min
        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {
            // Set min To The New Minimum Number Of Votes Found
            min = candidates[i].votes;
        }
    }
    return min;
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // An int Representing The Count of Candidates Who Have The Same Number Of Votes As min
    int tied_candidates = 0;

    // An int Representing The Count of Candidates Who Have Been Eliminated
    int eliminated_candidates = 0;

    for (int i = 0; i < candidate_count; i ++)
    {
        // If a Candidate Has Been Eliminated
        if (candidates[i].eliminated)
        {
            // Increment eliminated_candidates
            eliminated_candidates ++;
        }
        // If a Candidate Has Not Been Eliminated
        else
        {
            // And Has The Same Number of Votes as min
            if (candidates[i].votes == min)
            {
                // Increment tied_candidates
                tied_candidates ++;
            }
        }
    }

    // If All The Candidates That Have Not Been Eliminated Has the Same Number of Votes
    if (tied_candidates == candidate_count - eliminated_candidates)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}