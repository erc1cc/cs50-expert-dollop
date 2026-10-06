#include <stdio.h>
#include <cs50.h>

void print_row(int bricks, int spaces);

int main(void)
{
    // prompts the user for the height of the triangle and reprompts the user if n < 1
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // makes the triangle
    // prints pyramid's height
    for (int i = 0; i < n; i++)
    {
        print_row(i + 1, n - i - 1);
    }
}

// prints pyramid's rows
void print_row(int bricks, int spaces)
{
    for (int k = 0; k < spaces; k++)
    {
        printf(" ");
    }
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }
    printf("  ");
    for (int m = 0; m < bricks; m++)
    {
        printf("#");
    }
    printf("\n");
}
