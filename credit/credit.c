/*  -*- mode: C -*- */
/* This file conforms to C99 */

/*
  Build Instructions: 
  CFLAGS=-lcs50  make credit
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 19 /* get_long ensures that we have a valid long  */
#define VALUE(digit) ((digit) - '0') /* Convert the digit ascii code to the digit's value  */
#define ZERO '0'

int main(void)
{
    /*
      get card number from the user using get_long.
      Pros of using get_long:
      most bad inputs from the user are automatically handled
      Cons:
      leading zeros are ignored. In this case if card numbers could begin with zero this would be an issue.
     */
    long card_number = get_long("Please Enter the Credit Card number: ");

    /* Implement Luhn's Algorithm */
    /* covert number to a string of digits */
    char digits[MAX_DIGITS + 1];
    sprintf(digits, "%li", card_number);
    int n = strlen(digits);
    int cumsum = 0;

    /* For every other digit beginning with the second last */
    for (int i = n - 1; i > 0; i -= 2)
    {
        int prod = 2 * VALUE(digits[i - 1]);
        char prodstr[3];
        sprintf(prodstr, "%i", prod);
        int len = strlen(prodstr);
        for (int j = 0; j < len; j++)
        cumsum += VALUE(prodstr[j]);
    }

    /* for every other digit beginning with the last */
    for (int i = n; i > 0; i -= 2)
    {
        cumsum += VALUE(digits[i - 1]);
    }

    char sumstr[4];
    sprintf(sumstr, "%i", cumsum);
    int len = strlen(sumstr);
    char output[11]; /* big enough for "MASTERCARD" */
    /* Conditional which tests whether Luhn's Algorithm Passed */
    if (sumstr[len - 1] == ZERO)
    { /* Branch corresponding to VALID from Luhn's Algorithm */
        /* Switch on the first digit to partially disambiguate potential Card issuers */
        switch (digits[0])
        {
            case '4':
            /* switch to filter valid VISA numbers */
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
