#include <stdio.h>
#include <cs50.h>

int get_cents(void);
int get_quarters(int cents);
int get_dimes(int cents);
int get_nickles(int cents);
int get_pennies(int cents);

int main(void)
{
    // Amount of Cents That The Customer Is Owed
    int cents = get_cents();
    // printf("Number of Cents: %i\n", cents);

    // Number of Quarters Given as a Change
    int quarters = get_quarters(cents);
    // printf("Quarters: %i\n", quarters);
    // Reducing The Amount We Paid
    cents = cents - (quarters * 25);

    // Number of Dimes Given as a Change
    int dimes = get_dimes(cents);
    // printf("Dimes: %i\n", dimes);
    cents = cents - (dimes * 10);

    // Number of Nickles Given As a Change
    int nickles = get_nickles(cents);
    // printf("Nickles: %i\n", nickles);
    cents = cents - (nickles * 5);

    // Number of Pennies Given As a Change
    int pennies = get_pennies(cents);
    // printf("Pennies: %i\n", pennies);
    cents = cents - (pennies * 1);

    // Sum of Coins
    int coins = quarters + dimes + nickles + pennies;
    printf("Number of Coins Given: %i\n", coins);
}

// User Input (Positive Numbers)
int get_cents(void)
{
    int n;
    do
    {
        n = get_int("Cents: ");
    }
    while (n < 0);

    return n;
}

// Number of Quarters in a Given Amount of Cents
int get_quarters(int cents)
{
    // Initialization of a Quarter
    int quarter = 25;

    if (cents < quarter)
    {
        return 0;
    }
    else
    {
        int nr_quarters = (cents / quarter);
        return nr_quarters;
    }
}

// Number of Dimes in a Given Amount of Cents
int get_dimes(int cents)
{
    int dime = 10;

    if (cents < dime)
    {
        return 0;
    }
    else
    {
        int nr_dimes = (cents / dime);
        return nr_dimes;
    }
}

// Number of Nickles in a Given Amount of Cents
int get_nickles(int cents)
{
    int nickle = 5;

    if (cents < nickle)
    {
        return 0;
    }
    else
    {
        int nr_nickles = (cents / nickle);
        return nr_nickles;
    }
}

// Number of Pennies in a Given Amount of Cents
int get_pennies(int cents)
{
    int penny = 1;

    if (cents < penny)
    {
        return 0;
    }
    else
    {
        int nr_pennies = (cents / penny);
        return nr_pennies;
    }
}