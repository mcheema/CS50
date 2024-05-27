/*
build: make tideman
debug:  lldb -- ./tideman munawar saima kiran rehaan saamin < votes.txt

./tideman munawar saima << EOF
2
munawar
saima
saima
munawar
EOF

style50 tideman.c
check50 cs50/problems/2024/x/tideman
submit50 cs50/problems/2024/x/tideman
https://submit.cs50.io/users/mcheema/cs50/problems/2024/x/tideman
 */

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

/* Max number of candidates */
#define MAX 9

/* preferences[i][j] is number of voters who prefer i over j */
int preferences[MAX][MAX];

/* locked[i][j] means i is locked in over j */
bool locked[MAX][MAX];

/* Each pair has a winner, loser */
typedef struct
{
    int winner;
    int loser;
} pair;

#define STRENGTH(p) (preferences[(p).winner][(p).loser])

/* Array of candidates */
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

/* Function prototypes */
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    /* Check for invalid usage */
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    /* Populate array of candidates */
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    /* Clear graph of locked in pairs */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    /* Query for votes */
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        /* Query for each rank */
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

/* Update ranks given a new vote */
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcasecmp(candidates[i], name))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

/* Update preferences given one voter's ranks */
void record_preferences(int ranks[])
{
    int c1, c2;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        c1 = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            c2 = ranks[j];
            preferences[c1][c2]++;
        }
    }
    return;
}

/* Record pairs of candidates where one is preferred over the other */
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count++].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count++].loser = i;
            }
        }
    }
    return;
}

/* Sort pairs in decreasing order by strength of victory */
void sort_pairs(void)
{
    bool swap = true;
    pair store;
    while (swap)
    {
        swap = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (STRENGTH(pairs[i]) < STRENGTH(pairs[i+1]))
            {
                store = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = store;
                swap = true;
            }
        }
    }
    return;
}

/*
  Lock pairs into the candidate graph in order, without creating cycles.
  creates_cycle is a boolean helper function that determines if a cycle is present
  Note: the adjacency matrix does not have a cycle by construction and one can only be created
  if adding the edge represented by pair creates a cycle. This in turn can only happen if
  the loser of pair in turn beats a candidate that directly or indirectly beats the winner of pair.
  This is no allowed to happen.
  candidate_beats is a recursive function that tests if there is sequence of edges from a candidate1 to
  candidate2.

  Original winner is W, Original Loser is L; go through remaining candidates to see if
  L beats them, lets call them l1…ln; use a recursive function on each of the li to
  see if they ultimately beat W creating a cycle.
 */
bool candidate_beats(int candidate1, int candidate2)
{
    if (locked[candidate1][candidate2])
    {
        return true;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (i == candidate1 || i == candidate2) /* ignore */
            {
                continue;
            }
            else if (locked[candidate1][i])
            {
                if (candidate_beats(i, candidate2))
                {
                    return true;
                }
            }
        }        
    }
    return false;
}

/*
  Adding a winner loser pair creates a cycle if someone that the loser beats head to head in turn either directly or indirectly
  (recrusively) beats the winner
 */
bool creates_cycle(pair p)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == p.winner || i == p.loser) /* ignore */
        {
            continue;
        }
        else if (locked[p.loser][i]) /* loser beats candidate i */
        {
            if (candidate_beats(i, p.winner))
            {
                return true;
            }
        }
    }
    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i]))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

/* Print the winner of the election */
void print_winner(void)
{
    bool beaten = false;
    for (int i = 0; i < candidate_count; i++)
    {
        beaten = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                beaten = true;
            }
        }
        if (!beaten)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
