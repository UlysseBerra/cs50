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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair swap[0]; // helper

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool lock_check(int k, int m); // helper function

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
    // Check whether name exists in candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // No two candidates have the same name
        if (strcmp(name, candidates[i]) == 0)
        {
            // Set rank, looping over candidates array
            ranks[rank] = i;
            return true;
        }
    }
    // No candidate with that name
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Each voter ranks all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop over preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // winner for preferences[i][j];
                pairs[pair_count].winner = i;
                // winner for preferences[j][i];
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // winner for preferences[j][i];
                pairs[pair_count].winner = j;
                // winner for preferences[i][j];
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Using bubble sort algorithm
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int i1 = pairs[j].winner;
            int j1 = pairs[j].loser;

            // Get strength of first pair
            int strength_pair1 = preferences[i1][j1] - preferences[j1][i1];

            int i2 = pairs[j + 1].winner;
            int j2 = pairs[j + 1].loser;

            // Get strength of second pair
            int strength_pair2 = preferences[i2][j2] - preferences[j2][i2];

            // Compare strengths of victory
            if (strength_pair1 < strength_pair2)
            {
                swap[0] = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = swap[0];
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int k = pairs[i].winner;
        int m = pairs[i].loser;
        locked[k][m] = true;

        // Check whether there is a lock
        if (lock_check(k, m))
        {
            locked[k][m] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        // Create counter to detect winners
        int counter1 = 0;

        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                counter1++;
                // Print the name of the winners
                if (counter1 == candidate_count)
                {
                    printf("%s\n", candidates[j]);
                }
            }
        }
    }
    return;
}

bool lock_check(int k, int m)
{
    // Avoid running if there is only one candidate
    if (candidate_count == 1)
    {
        return false;
    }

    // Check for lock
    if (k == m)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // If there is already a pair
        if (locked[m][i] == true)
        {
            // Check where loser points to
            if (lock_check(k, i))
            {
                return true;
            }
        }
    }

    return false;
}