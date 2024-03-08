/*
  build: cc  -g -O0 -std=c17 -Wall -Werror -Wextra -L/usr/local/opt -lcs50 substitution.c -o substitution
  check50 cs50/problems/2024/x/substitution
  submit50 cs50/problems/2024/x/substitution https://submit.cs50.io/users/mcheema/cs50/problems/2024/x/substitution
  style50 substitution.c

*/

#include "cs50.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define KEYLEN 26U
#define LETTER(c) toupper(c) - 'A' /* 0..25 */

static char cipher_encipher_char(char const *const key, char c)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            return key[LETTER(c)];            
        }
        else
        {
            return tolower(key[LETTER(c)]);
        }
    }
    return c;
}

static int cipher_encipher(char const *const key, char const *const plaintext, char *ciphertext)
{
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        ciphertext[i] = cipher_encipher_char(key, plaintext[i]);
    }
    ciphertext[strlen(plaintext)] = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("One and Only one argument should be supplied\n");
        exit(EXIT_FAILURE);
    }

    char *const key = argv[1];
    int found[KEYLEN] = {0}; /* no letter initially found in key */
    for (unsigned i = 0; i < KEYLEN; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key is invalid: contains non alpha characters\n");
            exit(EXIT_FAILURE);            
        }
        else if (!found[LETTER(key[i])])
        {
            found[LETTER(key[i])] = 1;
            key[i] = toupper(key[i]);            
        }
        else
        {
            printf("Duplicate Letter Used in the key");
            exit(EXIT_FAILURE);
        }
    }
    if (key[KEYLEN] != '\0')
    {
        printf("Key is invalid: needs to be exactly %u characters\n", KEYLEN);
        exit(EXIT_FAILURE);                    
    }
    char *plaintext;
    do
    {
        plaintext = get_string("plaintext: ");
    }
    while (strlen(plaintext) == 0);
    
    char ciphertext[strlen(plaintext) + 1];
    cipher_encipher(key, plaintext, ciphertext);

    printf("ciphertext: %s\n", ciphertext);
    return EXIT_SUCCESS;
}
