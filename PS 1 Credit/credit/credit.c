#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long get_credit_card_number(void);
int length(long number);
int checksum(long number, int len);
int amex_check(long number, int len);
int mastercard_check(long number, int len);
int visa_check(long number, int len);


// Assume Credit Card Number = 4003600000000014 (VISA)
int main(void)
{
    // Prompt User for Input
    long number = get_credit_card_number();

    // Length of the Credit Card Number
    int len = length(number);
    // printf("Length: %i\n", len);


    long total_sum = checksum(number, len);
    // printf("Total Sum: %li\n", total_sum);

    // These Variables Will Be 1 If They Satisfy Card Specific Conditions
    int amex_checker = amex_check(number, len);
    int mastercard_checker = mastercard_check(number, len);
    int visa_checker = visa_check(number, len);

    // Validity of checksum Is Checked
    if (total_sum % 10 == 0)
    {
        // Card Specific Conditions are Checked

        // American Express
        if (len == 15 && amex_checker == 1)
        {
            printf("AMEX\n");
        }
        // Mastercard
        else if (len == 16 && mastercard_checker == 1)
        {
            printf("MASTERCARD\n");
        }
        // Visa
        else if ((len == 13 || len == 16) && visa_checker == 1)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // Invalid Card Number
    else
    {
        printf("INVALID\n");
    }
}

// User Input
long get_credit_card_number(void)
{
    long n = get_long("Credit Card Number: ");
    return n;
}

// Length of the Credit Card Number
int length(long number)
{
    int len = ((floor(log10(labs(number)))) + 1);
    return len;
}

// Assume That the Credit Card Number is = 4003600000000014 (VISA)
int checksum(long number, int len)
{
    // Sum of Every Other Digit With Step 2 (Starting from the Last Digit)
    // Corresponds to the sum of 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0
    int last_digits = 0;

    // Sum of Digits of Every Other Digit by 2 With Step 2 (Starting from the Second to Last Digit)
    // First, We Find The Sum of Every Other Digit by 2 (Starting from the Second to Last Digit)
    // 1 * 2 + 0 * 2 + 0 * 2 + 0 * 2 + 0 * 2 + 6 * 2 + 0 * 2 + 4 * 2, This Gives Us 2 + 0 + 0 + 0 + 0 + 12 + 0 + 8
    // Second, We Will Add Those Products' Digits
    // 2 + 1 + 2 + 8 = 13
    int sec_last_digits = 0;

    // Last Digit Multiplied By 2
    int sec_last_digits_mul_2 = 0;

    // Sum of last_digits & sec_last_digits
    int total_sum;

    // Iteration Equal to the Length of the Number
    for (int i = 0; i < len; i ++)
    {
        // Last Digit of the Number by Reverse Iteration
        int last_digit = number % 10;
        number = number / 10;

        // Sum of Last Digit and Every Other Digit With Step 2
        if (i % 2 == 0)
        {
            last_digits += last_digit;
        }

        // Sum of Digits of Second to Last Digit & Its Multiples of 2 With Step 2
        else
        {
            // Multiply the Last Digit By 2
            sec_last_digits_mul_2 = 2 * last_digit;

            // If the Multiplied Number Has More Than 2 Digits, We Need to Sum Each of Its Digits
            // If sec_last_digits_mul_2 == 12, We Need to sec_last_digits +=1; and sec_last_digits += 2;
            if (sec_last_digits_mul_2 >= 10)
            {
                int x = 0;
                x = sec_last_digits_mul_2 % 10;
                sec_last_digits = sec_last_digits + x;
                sec_last_digits_mul_2 = sec_last_digits_mul_2 / 10;
                sec_last_digits = sec_last_digits + sec_last_digits_mul_2;
            }
            else
            {
                sec_last_digits = sec_last_digits + sec_last_digits_mul_2;
            }
        }
    }

    total_sum = sec_last_digits + last_digits;

    return total_sum;
}

// We Need to Check Whether Each Credit Card Satisfies Specific Conditions

// American Express Cards Should Start w/ Either 34 or 37 and Has a Length of 15
int amex_check(long number, int len)
{
    const int FIRST_AMEX = 3;
    const int SEC_AMEX_1 = 4;
    const int SEC_AMEX_2 = 7;

    const int LEN_1 = 14;
    const int LEN_2 = 13;

    // Becomes 1 If Verified
    int digit_1_verified = 0;
    int digit_2_verified = 0;

    // Returns passed if the Credit Card Verifies Conditions, Else, returns not_passed
    int passed = 1;
    int not_passed = 0;

    for (int i = 0; i < len; i ++)
    {
        int last_digit = number % 10;
        number = number / 10;

        if (i == LEN_2 && (last_digit == SEC_AMEX_1 || last_digit == SEC_AMEX_2))
        {
            digit_2_verified = digit_2_verified + 1;
        }

        if (i == LEN_1 && (last_digit == FIRST_AMEX))
        {
            digit_1_verified = digit_1_verified + 1;
        }
    }

    if (digit_1_verified == 1 && digit_2_verified == 1)
    {
        return passed;
    }
    else
    {
        return not_passed;
    }
}

// Mastercard Cards Should Start w/ 51, 52, 53, 54 or 55 and Has a Length of 16
int mastercard_check(long number, int len)
{
    const int FIRST_MC = 5;
    const int SEC_MC_1 = 1;
    const int SEC_MC_2 = 2;
    const int SEC_MC_3 = 3;
    const int SEC_MC_4 = 4;
    const int SEC_MC_5 = 5;

    const int LEN_1 = 15;
    const int LEN_2 = 14;

    int digit_1_verified = 0;
    int digit_2_verified = 0;

    int passed = 1;
    int not_passed = 0;

    for (int i = 0; i < len; i ++)
    {
        int last_digit = number % 10;
        number = number / 10;

        if (i == LEN_2 && (last_digit == SEC_MC_1 || last_digit == SEC_MC_2 || last_digit == SEC_MC_3 || last_digit == SEC_MC_4
                           || last_digit == SEC_MC_5))
        {
            digit_2_verified = digit_2_verified + 1;
        }

        if (i == LEN_1 && last_digit == FIRST_MC)
        {
            digit_1_verified = digit_1_verified + 1;
        }
    }

    if (digit_1_verified == 1 && digit_2_verified == 1)
    {
        return passed;
    }
    else
    {
        return not_passed;
    }
}

// Visa Cards Should Start w/ 4, However, Their Length Can Be Both 13 or 16
int visa_check(long number, int len)
{
    const int FIRST_VISA = 4;

    const int LEN_1 = 15;
    const int LEN_2 = 12;

    int len_16_verified = 0;
    int len_13_verified = 0;

    int passed = 1;
    int not_passed = 0;

    // If the Visa Card Has a Length of 16
    if (len == 16)
    {
        for (int i = 0; i < len; i ++)
        {
            int last_digit = number % 10;
            number = number / 10;

            if (i == LEN_1 && last_digit == FIRST_VISA)
            {
                len_16_verified = len_16_verified + 1;
            }
        }
    }

    // If the Visa Card Has a Length of 16
    if (len == 13)
    {
        for (int i = 0; i < len; i ++)
        {
            int last_digit = number % 10;
            number = number / 10;

            if (i == LEN_2 && last_digit == FIRST_VISA)
            {
                len_13_verified = len_13_verified + 1;
            }
        }
    }

    if (len == 16)
    {
        if (len_16_verified == 1)
        {
            return passed;
        }
        else
        {
            return not_passed;
        }
    }
    else if (len == 13)
    {
        if (len_13_verified == 1)
        {
            return passed;
        }
        else
        {
            return not_passed;
        }
    }
    else
    {
        return not_passed;
    }
}