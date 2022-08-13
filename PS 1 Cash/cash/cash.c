#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

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

int calculate_quarters(int cents)
{
    // Initialization of a Quarter
    const int QUARTER = 25;

    int nr_quarters = (cents / QUARTER);
    return nr_quarters;
}

int calculate_dimes(int cents)
{
    // Initialization of a Dime
    const int DIME = 10;

    int nr_dimes = (cents / DIME);
    return nr_dimes;
}

int calculate_nickels(int cents)
{
    // Initialization of a Nickle
    const int NICKLE = 5;

    int nr_nickles = (cents / NICKLE);
    return nr_nickles;
}

int calculate_pennies(int cents)
{
    return cents;
}