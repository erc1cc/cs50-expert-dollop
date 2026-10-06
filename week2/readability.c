#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string a);
int count_words(string a);
int count_sentences(string a);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // compute L (avg letters per hundred words) and compute S (avg sentences per 100 words)
    float L;
    float S;
    if (words == 0)
    {
        L = 0;
        S = 0;
    }
    else
    {
        L = 100 * (letters / words);
        S = 100 * (sentences / words);
    }

    // Compute the Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8
    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Counts the number of letters, words, and sentences in the text
int count_letters(string a)
{
    int letters = 0;
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(a[i]))
        {
            letters++;
        }
    }
    return letters;
}

// counts number of words
// Words are counted when they start, not every time you encounter a letter or space.
int count_words(string a)
{
    int words = 1;
    // Currently, strlen(a) is called on every iteration.
    // This can be inefficient for long strings.
    // Instead, store the length in a variable before the loop
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        // if ((i == 0 || a[i - 1] == ' ')) && isalpha(a[i]))
        // a[i - 1] == ' ' does not work because if a part of the text starts with ", then the 'isalpha' condition is not fultilled and the word is not counted
        if (a[i] == ' ') // usually wouldn't work because if someone entered, say, "hello   world", then wordswould be counted an extra 2 times, but in the case where it's a text from a book, then there would be no typos, so this would be the best in that scenario

        {
            words++;
        }
    }
    return words;
}

int count_sentences(string a)
{
    int sentences = 0;
    int len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        if ((i == 0 || a[i - 2] == '.' || a[i - 2] == '!' || a[i - 2] == '?') &&
        (isalpha(a[i]) || isdigit(a[i])))
        {
            sentences++;
        }
    }
    return sentences;
}
