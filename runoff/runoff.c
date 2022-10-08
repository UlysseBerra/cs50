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
} candidate;

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
    // If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i].name, name))
        {
            preferences[voter][rank] = i;
            // If the preference is successfully recorded, the function should return true
            return true;
        }
        // The function returns false otherwise (if, for instance, name is not the name of one of the candidates)
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // The function should update the number of votes each candidate has at this stage in the runoff
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        // Search for remaining candidates
        while (candidates[preferences[i][j]].eliminated)
        {
            j++;
        }
        // Update their votes
        candidates[preferences[i][j]].votes++;
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // If any candidate has more than half of the vote, their name should be printed and the function should return true.
    int winner_exists = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes > (voter_count / 2))
        {
            winner_exists++;
            printf("%s\n", candidates[i].name);
        }
    }
    if (winner_exists)
    {
        return true;
    }
    else
    {
        // If nobody has won the election yet
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // The function should return the minimum vote total for any candidate who is still in the election.
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes <= min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int remaining = 0;
    int having_min = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            remaining++;
            if (candidates[i].votes == min)
            {
                having_min++;
            }
        }
    }
    if (remaining == having_min)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
// The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // The function should eliminate the candidate (or candidates) who have min number of votes.
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}