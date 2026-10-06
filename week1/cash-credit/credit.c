#include <cs50.h>
#include <stdio.h>

bool checksum(long card_number);
void card_type(long card_number);

int main(void)
{
    long card_number = get_long("Number: ");

    // if checksum works, it checks the card type, or else it prints an invalid card
    if (checksum(card_number) == true)
    {
        card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}

// True or false
bool checksum(long card_number)
{
    int sum = 0;
    int position = 0;

    // unable to enter a card number less than 0
    while (card_number > 0)
    {
        // gets the digits of the card
        int digit = card_number % 10;
        card_number /= 10;

        // if the digit is every other digit we multiply by 2, and if that result is larger than 9,
        // we add the digits up
        if (position % 2 == 1)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = (digit % 10) + (digit / 10);
            }
        }

        // we add the digit, and increase the position number
        sum += digit;
        position++;
    }
    return (sum % 10 == 0);
}

// checks the card type
void card_type(long card_number)
{
    int length = 0;
    long temp = card_number;
    //  counting up number of digits
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // gets the first two digits of the card
    long first_two = card_number;
    while (first_two >= 100)
    {
        first_two /= 10;
    }

    // checks for type of card using first digits and length
    if ((first_two == 34 || first_two == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    // Else if statements because if the first if statement matches the card,
    // then the program doesn't check everything else; but if we did use only if statements,
    // the program would still check all the other if statements even if one of them already matches
    else if ((first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 ||
              first_two == 55) &&
             length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (first_two / 10 == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    // if the card fulfills checksum, but not any of these card types, it will print invalid
    else
    {
        printf("INVALID\n");
    }
}
