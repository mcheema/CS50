/*  -*- mode: C -*- */
/* This file conforms to C99 */

/*
  check50 cs50/problems/2024/x/mario/more
  Build Instructions: 
  clang -std=c99 -Wall -Wextra  -lcs50 mario.c -g -o mario -O3
 */

#include <cs50.h>
#include <stdio.h>

#define MAXHEIGHT 8
#define MINHEIGHT 1
#define PYRAMID_CHAR '#'

void print_row(int row, int height);
int main(void)
{
    int height;
    do
    {
        height = get_int("How tall is the pyramid? (please enter a number between %i and %i): ", MINHEIGHT, MAXHEIGHT);
    }
    while (height > MAXHEIGHT || height < MINHEIGHT);

    for (int i = 0; i < height; i++)
    {
        print_row(i, height);
    }
}

void print_row(int row, int height)
{
    for (int i = 1; i <= height; i++)
    {
        printf("%c", (i > height - row - 1) ? PYRAMID_CHAR : ' ');
    }
    printf("  ");
    for (int i = 0; i <= row; i++)
    {
        printf("%c", PYRAMID_CHAR);
    }
    printf("\n");
}
