/*  -*- mode: C -*- */

/*
  Conforms to C99
  Build Instructions: 
  CFLAGS=-lcs50  make population
  submit50 cs50/labs/2023/x/population
  
*/

#include <cs50.h>
#include <stdio.h>
#define MIN_POP 9 /* Per spefifications */

int main(void)
{
    
    long start_size;
    do
    {
        start_size = get_long("Please enter the starting population size (minimum: %i)?: ", MIN_POP);
    }
    while (start_size < MIN_POP);

    long end_size;
    do
    {
        end_size = get_long("Please enter the starting population size (minimum: %li)?: ", start_size);
    }
    while (end_size < start_size); /* Must handle populations of same or larger size per spec */

    long cur_size = start_size;
    int no_of_years = 0;
    while(cur_size < end_size)
    {
        cur_size += (cur_size / 3 - cur_size / 4);        
        no_of_years++;
    }    

    printf("Years: %i\n", no_of_years);
    
    return 0;
}
