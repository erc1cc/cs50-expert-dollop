#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates is 9
#define MAX 9

// New candidate type and Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates up to 9
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// main
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2){
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // candidate_count does not include the './plurality' arg
    candidate_count = argc - 1;
    // checks if the number of candidates entered is larger than max
    if (candidate_count > MAX){
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++){
        // not including the './' arg and only takes the names
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++){
        string name = get_string("Vote: ");

        // Check for invalid vote, if the inputted name does not match one of the candidates
        if (!vote(name)){
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    // iterate over every candidate
    for (int i = 0; i < candidate_count; i++){
        // check if a candidate name matches given name
        if (strcmp(candidates[i].name, name) == 0){
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // // Find the maximum number of votes, sort candidates by max number of votes
    // // bubble sort
    // for (int i = 0; i < (candidate_count - 1); i++)
    // {
    //     for (int j = 0; j < (candidate_count - 2); j++)
    //     {
    //         if (candidates[i].votes > candidates[i + 1].votes)
    //         {
    //             int temp = candidates[i + 1].votes;
    //             candidates[i + 1].votes = candidates[i].votes;
    //             candidates[i].votes = temp;
    //         }
    //     }
    // }

    // int maxvotes = candidates[candidate_count].votes;
    // for
    // // Print the candidate (or candidates) with maximum votes
    // if (candidates[candidate_count - 1].votes > candidates[candidate_count - 2].votes)
    // {
    //     printf("%s\n", candidates[candidate_count - 1].name);
    //     return;
    // }

    int maxvotes = 0;
    // as you go through the candidates list, you search for the largest number of votes, by setting
    // the value of the largest seen number to maxvotes run time is O(n)
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes > maxvotes){
            maxvotes = candidates[i].votes;
        }
    }

    // you go through all the candidates and check if their votes are equal to maxvotes
    // run time is O(n)
    for (int j = 0; j < candidate_count; j++){
        if (candidates[j].votes == maxvotes){
            printf("%s\n", candidates[j].name);
        }
    }
}
