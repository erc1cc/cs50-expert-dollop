#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// create point system
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_points(string a);

int main(void)
{
    // prompt user for words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // assign values of letters to their respective point value
    int points1 = calculate_points(word1);
    int points2 = calculate_points(word2);

    // compare scores
    // return the winner, consider ties
    if (points1 > points2)
    {
        printf("Player 1 wins!\n");
    }
    else if (points2 > points1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// add up the letter point values for the input word of each player
int calculate_points(string a)
{
    // turn all the letters of the word to lowercase
    // add the values of each letter
    // add up score
    int score = 0;

    for (int i = 0; i < strlen(a); i++)
    {
        if (isupper(a[i]))
        {
            score += points[a[i] - 'A'];
        }
        else if (islower(a[i]))
        {
            score += points[a[i] - 'a'];
        }
    }
    return score;
}
