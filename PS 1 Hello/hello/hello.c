#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompts User for His/Her Name as Input
    string name = get_string("What is your name? ");

    // Prints "Hello, name", Whereas "name" Is the User Input
    printf("Hello, %s\n", name);
}