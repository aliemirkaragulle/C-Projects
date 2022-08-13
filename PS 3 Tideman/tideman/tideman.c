#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate Through the Candidates
    for (int i = 0; i < candidate_count; i ++)
    {
        // If the Candidate Name Has Been Found
        if (strcmp(candidates[i], name) == 0)
        {
            // Update Voters Rank For a Candidate
            // ranks[i] = Index Of the Candidate Who Is the i-th Preference For the Voter
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Assume That:
    // ranks = [3, 0, 4, 1, 2]
    // i = 0, i = 1, i = 2, i = 3
    for (int i = 0; i < candidate_count - 1 ; i ++)
    {
        // j = 1, j = 2, j = 3, j = 4
        for (int j = 1; j < candidate_count; j ++)
        {
            if (i != j)
            {
                preferences[ranks[i]][ranks[j]] ++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Make pair_count = 0, Since There Are No Pairs Yet
    pair_count = 0;

    // Assume That There Are 3 Candidates, So an Adjacency Matrix Of 3x3
    // We Need To Compare C(n,2) = C(3,2) = 3 Candidates

    // candidate_count = 3, candidate_count - 1 = 2
    // Iterations: i = 0, i = 1
    for (int i = 0; i < candidate_count - 1; i ++)
    {
        // candidate_count = 3
        // Iterations: j = 1, j = 2
        for (int j = 1; j < candidate_count; j ++)
        {
            // Start Comparing Candidates Preferences (If They Are Equal Do Nothing)

            // If a Candidate X Is Preferred To Another One (Y);
            if (preferences[i][j] > preferences[j][i])
            {
                // Add Each Pair Of Candidates To pairs Array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                // Increment pair_count
                pair_count ++;
            }
            // If a Candidate Y Is Preferred To Another One (X);
            else if (preferences [j][i] > preferences[i][j])
            {
                // Add To The pair_count Array
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                // Increment pair_count
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble Sort (O(n^2) Omega(n))

    // Pseudocode:
    // Repeat n-1 times
    // ----For i from 0 to n-2
    // --------If numbers[i] and numbers[i+1] out of order
    // ------------Swap them
    // ----If no swaps
    // --------Quit

    // If We Have Only a Single Pair, Do Nothing
    if (pair_count <= 1)
    {
        return;
    }

    // Assume That Our pairs Array Is = [1, 3, 5, 6]

    // pairs_count = 4; pairs_count - 1 = 3; pairs_count - 2 = 2
    // k = 0, k = 1, k = 2
    int k = 0;
    while (k < pair_count - 1)
    {
        int swap_count = 0;

        // i = 0, i = 1, i = 2
        for (int i = 0; i <= pair_count - 2; i ++)
        {
            // Strength Of the First Pair
            int pair_str_0 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            // Strength Of the Second Pair
            int pair_str_1 = preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            // If the Second Pair Is Stronger Than the First Pair
            if (pair_str_0 < pair_str_1)
            {
                // Take the Stronger Pair To the Left
                int x = pairs[i].winner;
                int y = pairs[i].loser;

                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = x;
                pairs[i + 1].loser = y;
            }

            // Optimize Our Algorithm
            if (swap_count == 0)
            {
                return;
            }
        }
        // Iterate the While Loop
        k ++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i ++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Returns True If There Is a Cycle
        if (!cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Returns;
// True If Cycle
// False If No Cycle
bool cycle(int winner, int loser)
{
    // Assume There Are 3 Candidates = [a, b, c]
    // And Locked Pairs Are a -> b & b -> c
    // We Are Checking Whether To Lock c -> a (Winner = c, Loser = a)

    // Base Case
    // 1) If a -> c Is Previously Locked, We Return True. It Is Not.

    // 2) If a -> b Is Previously Locked, We Return True. It Indeed Is, So Return True.
    // We Found That b -> c, And Then a -> b, So Our Initial Output c -> a Will Create a Cycle. a -> b -> c -> c
    if (locked[loser][winner])
    {
        return true;
    }

    // Recursive Case
    // For All The Candidates
    for (int i = 0; i < candidate_count; i ++)
    {
        // 1)
        // Check a -> c, False
        // Check b -> c, True
        if (locked[i][winner])
        {
            // Return cycle(b, a)
            return cycle(i, loser);
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Assume candidate_count = 3

    // 1) j = 0
    // 2) j = 1
    // 3) j = 2
    int j = 0;
    while (j < candidate_count)
    {
        int source = 0;
        // 1) j = 0 | i = 0, i = 1, i = 2 => 0-0, 1-0, 2-0
        // 2) j = 1 | i = 0, i = 1, i = 2 => 0-1, 1-1, 2-1
        // 3) j = 2 | i = 0, i = 1, i = 2 => 0-2, 1-2, 2-2
        for (int i = 0; i < candidate_count; i ++)
        {
            if (locked[i][j] == false)
            {
                source ++;
            }
        }

        if (source == candidate_count)
        {
            printf("%s\n", candidates[j]);
            return;
        }
        j ++;
    }
    return;
}