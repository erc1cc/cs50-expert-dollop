#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string substitution(string a, string keys);

int main(int argc, string argv[])
{

    // validates the key
    // only allows 1 command line arg, and makes sure the inputted string is 26 chars
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else if (strlen(argv[1]) == 26)
    {
        int len = strlen(argv[1]);
        for (int i = 0; i < len; i++)
        {
            // checks for non-alphabetic chars in the cipher
            if (!isalpha(argv[1][i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
                break;
            }

            // checks for repeated chars
            // for every i, j is iterated through the key again to check if there are any chars that are the same as i
            for (int j = 0; j < len; j++)
            {
                if (i != j && tolower(argv[1][i]) == tolower(argv[1][j]))
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                    break;
                }
            }
        }
    }

    // gets the plaintext
    string text = get_string("plaintext: ");
    // gets key
    string key = argv[1];

    // print ciphertext
    printf("ciphertext: %s\n", substitution(text, key));
    return 0;
}

// encipher
string substitution(string a, string keys)
{
    string b = a;
    string key2 = keys;
    int len1 = strlen(b);

    for (int i = 0; i < len1; i++)
    {
        // lowercase/uppercase of key should not matter
        if (isupper(a[i]))
        {
            b[i] = toupper(key2[a[i] - 'A']);
        }
        else if (islower(a[i]))
        {
            b[i] = tolower(key2[a[i] - 'a']);
        }
        else
        {
            b[i] = a[i];
        }
    }
    return b;
}
