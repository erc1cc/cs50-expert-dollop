#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // prompt the user how much change owed in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int quarters = calculate_quarters(cents);
    cents = cents - 25 * quarters;

    int dimes = calculate_dimes(cents);
    cents = cents - 10 * dimes;

    int nickels = calculate_nickels(cents);
    cents = cents - 5 * nickels;

    int pennies = calculate_pennies(cents);
    cents = cents - pennies;

    // sum number of quarters, dimes, nickels, pennies used
    // return that value
    int sum = quarters + dimes + nickels + pennies;
    printf("%i\n", sum);
}

// calculate the amount of quarters needed
// subtract the value of quarters from cents
int calculate_quarters(int cents)
{
    int quarters = 0;
    while (cents >= 25)
    {
        quarters++;
        cents = cents - 25;
    }
    return quarters;
}

// calculate the amount of dimes needed
// subtract the value of dimes from cents
int calculate_dimes(int cents)
{
    int dimes = 0;
    while (cents >= 10)
    {
        dimes++;
        cents = cents - 10;
    }
    return dimes;
}

// calculate the amount of nickels needed
// subtract the value of nickels from cents
int calculate_nickels(int cents)
{
    int nickels = 0;
    while (cents >= 5)
    {
        nickels++;
        cents = cents - 5;
    }
    return nickels;
}

// calculate the amount of pennies needed
// subtract the value of pennies from cents
int calculate_pennies(int cents)
{
    int pennies = 0;
    while (cents >= 1)
    {
        pennies++;
        cents = cents - 1;
    }
    return pennies;
}
