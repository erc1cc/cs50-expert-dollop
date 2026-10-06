#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    string name = get_string("Name: ");
    int length = strlen(name);
    printf("%i\n", length);
}


// strlen function

// int string_length(string n);

// int main(void)
// {
//     string name = get_string("Name: ");
//     int length = string_length(name);
//     printf("%i\n", length);
// }

// int string_length(string n)
// {
//     int a = 0;
//     while (n[a] != 0)
//     {
//         a++;
//     }
//     return a;
// }
