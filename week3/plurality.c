#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    if(candidate_count > 0)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (strcmp(name,candidates[i].name) == 0)
            {
                candidates[i].votes++;
                return true;
            }
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //size of matrix in winners
    int size = 0;
    //temporal var with higher score
    int higher_score = 0;
    //array of winner (index of original struct)
    int *winner = NULL;

    //Iterate through the candidates to get higher score
    for (int i = 0; i < candidate_count; i++)
    {
        //if there is a winner remove all and keep only this one
        if (candidates[i].votes > higher_score)
        {
            //reset the size of the array of winners
            size = 1;
            higher_score = candidates[i].votes;
            winner = NULL;
            winner = malloc(size * sizeof(int));
            winner[0] = i;
        }
        else if (candidates[i].votes == higher_score)
        {
            //there is a tie so keep all that have the same number of votes
            size++;
            winner = realloc(winner, size * sizeof(int));
            winner[size - 1] = i;
        }
    }
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", candidates[winner[i]].name);
    }
    return;
}