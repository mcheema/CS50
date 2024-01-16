/*  -*- mode: C -*- */
/* This file conforms to C99 */

/*
  Build Instructions: 
  clang -std=c99 -Wall -Wextra  -lcs50 credit.c -g -o credit -O3
 */


#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 19 /* get_long ensures that we have a valid long  */

int main(void)
{
    long card_number = get_long("Please Enter the Credit Card number: ");
    /* Implement Luhn's Algorithm */
    char digits[MAX_DIGITS + 1];
    sprintf(digits, "%li", card_number);
    int n = strlen(digits);
    int cumsum = 0;
    for (int i = n - 1; i > 0; i -= 2)
    {
        int prod = 2 * (digits[i - 1] - '0');
        char prodstr[3];
        sprintf(prodstr, "%i", prod);
        int len = strlen(prodstr);
        for (int j = 0; j < len; j++)
            cumsum += (prodstr[j] - '0');
    }

    for (int i = n; i > 0; i -= 2)
    {
        cumsum += (digits[i - 1] - '0');
    }

    char sumstr[4];
    sprintf(sumstr, "%i", cumsum);
    int len = strlen(sumstr);
    char output[11]; /* big enough for MASTERCARD */
    /* Conditional which tests whether Luhn's Algorithm Passed */
    if (sumstr[len - 1] == '0')
    { /* Branch corresponding to VALID from Luhn's Algorithm */
        /* Switch on the first digit to partially disambiguate potential Card issuers */
        switch (digits[0])
        {
            case '4':

                if (n == 13 || n == 16)
                    strcpy(output, "VISA");
                else
                    strcpy(output, "INVALID");
                break;
            case '3':
                /* switch to filter valid AMEX numbers */
                switch (digits[1])
                {
                    case '4':
                    case '7':
                        if (n == 15)
                            strcpy(output, "AMEX");
                        else
                            strcpy(output, "INVALID");
                        break;
                    default:
                        strcpy(output, "INVALID");
                        break;
                }
                break;
            case '5':
                /* switch to filter valid Mastercard numbers */
                switch (digits[1])
                {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                        if (n == 16)
                            strcpy(output, "MASTERCARD");
                        else
                            strcpy(output, "INVALID");
                        break;
                    default:
                        strcpy(output, "INVALID");
                        break;
                }
                break;
            default:
                strcpy(output, "INVALID");
                break;
        }
    }
    else /* Branch Corresponding to Invalid from Luhn's Algorithm*/
    {
        strcpy(output, "INVALID");
    }

    printf("%s\n", output);

    return 0;
}
