// Conforms to C99
// CFLAGS=-lcs50 make prime
// check50 cs50/labs/2023/x/prime


#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    } 
    while (min >= max);
    
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    /* one factor must be less than or equal to sqrt(prime) */
    bool is_prime = true;
    int loop_max = round(sqrt((double) number));
    /* printf("Loop max for %i is %i\n", number, loop_max); */
    for (int i = loop_max; i >= 2; i--)
    {
        if ((number % i) == 0) /* Is i a factor? */
        {
            /* printf("%i is a factor of %i", i, number); */
            is_prime = false;
        }
    }

    return is_prime;
}
