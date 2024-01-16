/*  -*- mode: C -*- */

/*

This File Conforms to C99
Become familiar wih C syntax
Learn to debug buggy code

 check50 cs50/labs/2023/x/debug 
My build instructions:
CFLAGS=-lcs50  make debug

 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask for your name and where live
    string name = get_string("What is your name? ");
    string location = get_string("Where do you live? ");

    // Say hello
    printf("Hello, %s, from %s!", name, location);
}
