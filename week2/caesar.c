#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string rotate(string word, int num);

int main(int argc, string argv[])
{
    // If your program is executed with not 1 command-line argument, your program should print
    // ./caesar key and return from main a value of 1 If any of the characters of the command-line
    // argument is not a decimal digit, your program should print the same thing
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int len = strlen(argv[1]);

    for (int i = 0; i < len; i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // prompt the user for a string of plaintext (using get_string).
    int key = atoi(argv[1]);
    string text = get_string("plaintext:  ");

    // After outputting ciphertext, you should print a newline. Your program should then exit by
    // returning 0 from main.
    printf("ciphertext: %s\n", rotate(text, key));
    return 0;
}

// Do not assume that k will be less than or equal to 26. Your program should work for all
// non-negative integral values of k less than 2^31 - 26 . Your program must preserve case:
// capitalized letters as capitalized, lowercase letters as lowercase
string rotate(string word, int num)
{
    num = num % 26;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        if (islower(word[i]))
        {
            // increment by key
            word[i] = (word[i] - 'a' + num) % 26 + 'a';
        }
        else if (isupper(word[i]))
        {
            word[i] = (word[i] - 'A' + num) % 26 + 'A';
        }
    }
    return word;
}
