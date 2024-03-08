/*
  make readability
  
check50 cs50/problems/2024/x/readability
submit50 cs50/problems/2024/x/readability
style50 readability.c

*/

#include "cs50.h"
#include "ctype.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int is_sentence_delimiter(char const c);

// average letters per hundred words: L
// average number of sentences per hundred words: S
double coleman_liau_index(double const L, double const S);

int main(void)
{
    string text;
    // get text
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) == 0);
    int len = strlen(text);
    int words = 1;
    int sentences = 0;
    int letters = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
            words++;
        if (is_sentence_delimiter(text[i]))
            sentences++;
        if (isalpha(text[i]))
            letters++;
    }
    double L = (double) 100.0 * letters / words;
    double S = (double) 100.0 * sentences / words;
    
    int level = round(coleman_liau_index(L, S));
    if (level > 0 && level < 17)
        printf("Grade %i\n", level);
    else if (level < 1)
        printf("Before Grade 1\n");
    else
        printf("Grade 16+\n");

    return EXIT_SUCCESS;
}

double coleman_liau_index(double const L, double const S)
{
    return 0.0588 * L - 0.296 * S - 15.8;
}

// assume sentence delimiter in {'.', '!', '?'}
int is_sentence_delimiter(char const c)
{
    if (c == '.' || c == '!' || c == '?')
    {
        return 1;
    }
    return 0;
}
