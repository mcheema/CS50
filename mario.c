#include <cs50.h>
#include <stdio.h>

#define MAXHEIGHT 8
#define MINHEIGHT 1
#define PYRAMID_CHAR '#'

void print_row(int row, int height);
int main(void)
{
    int height = get_int("How tall is the pyramid? (please enter a number between 1 and 8): ");
    while (height > MAXHEIGHT || height < MINHEIGHT)
    {
        height = get_int("How tall is the pyramid? (please enter a number between 1 and 8): ");
    }

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
